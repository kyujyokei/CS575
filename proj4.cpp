#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include <cstdlib>

int  NowYear;           // 2014 - 2019
int  NowMonth;          // 0 - 11

int MonthCount = 0;
// unsigned int seed = (time(NULL));

float NowPrecip;        // inches of rain per month
float NowTemp;          // temperature this month
float NowHeight;        // grain height in inches
int  NowNumDeer;        // current deer population
int TyphoonStruck;

const float GRAIN_GROWS_PER_MONTH =             8.0;
const float ONE_DEER_EATS_PER_MONTH =           0.5;

const float AVG_PRECIP_PER_MONTH =              6.0;
const float AMP_PRECIP_PER_MONTH =              6.0;
const float RANDOM_PRECIP =                     2.0;

const float AVG_TEMP =                          50.0;
const float AMP_TEMP =                          20.0;
const float RANDOM_TEMP =                       10.0;

const float MIDTEMP =                           40.0;
const float MIDPRECIP =                         10.0;

void GrainDeer();
void Grain();
void Typhoon();
void Watcher();

float
Ranf( float low, float high, unsigned int* seed )
{
    float r = (float) rand_r(seed);      // 0 - RAND_MAX
    return( low + r * ( high - low ) / (float)RAND_MAX );
}

int main(){
    omp_set_num_threads(4);

    unsigned int seed = 2;

    float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );
    float temp = AVG_TEMP - AMP_TEMP * cos( ang );
    NowTemp = temp + Ranf( -RANDOM_TEMP, RANDOM_TEMP, &seed );
    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
    NowPrecip = precip + Ranf( -RANDOM_PRECIP, RANDOM_PRECIP, &seed );

    NowHeight = 5;
    NowNumDeer = 5;

    while (MonthCount < 73){

        

        if( NowPrecip < 0. ) NowPrecip = 0.;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                GrainDeer();

            }
            #pragma omp section
            {
                Grain();
            }
            #pragma omp section
            {
                Typhoon();
            }

            #pragma omp section
            {
                Watcher();
            }

        }

    }
    return 0;
}

void Grain(){
    // printf("Grain A\n");

    float tempHeight = NowHeight;

    float tempFactor = NowTemp - 50. ;
    float precipFactor = NowPrecip - 3.;

    tempHeight += tempFactor*0.3 + precipFactor*0.3 + GRAIN_GROWS_PER_MONTH;
    // printf("TempF:%d, PrecF:%d\n", tempFactor, precipFactor);
    tempHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;

    if (TyphoonStruck == true){
        tempHeight /= 2;
    }

    if (tempHeight < 0) tempHeight = 0;

    #pragma omp barrier // Done computing

    NowHeight = tempHeight;

    // printf("Grain B\n");
    #pragma omp barrier // Done write back to globals
    // printf("Grain C\n");
    #pragma omp barrier // Done Printing

};

void GrainDeer(){
    // printf("Deer A\n");
    int tempNum = NowNumDeer;
    // printf("Now num deer:%d\n", NowNumDeer);
    if (NowHeight > NowNumDeer){
        tempNum += 1;
    } else {
        tempNum -= 1;
    }
    // printf("Temp:%d\n", tempNum);
    
    #pragma omp barrier // Done computing
    // printf("Deer B\n");
    NowNumDeer = tempNum;
    // printf("NowNumDeer:%d\n", NowNumDeer);

    #pragma omp barrier // Done write back to globals
    // printf("Deer C\n");
    #pragma omp barrier // Done Printing

};

void Typhoon(){

    unsigned int seed = omp_get_thread_num();
    TyphoonStruck = 0;
    float chance = 0;
    if (NowMonth > 5 && NowMonth < 9){
        float chance = Ranf( 0., 1., &seed );
    }

    #pragma omp barrier // Done computing

    if (chance > 0.5){
            TyphoonStruck = 1;
    } 

    #pragma omp barrier // Done write back to globals
    #pragma omp barrier // Done Printing

};

void Watcher(){
    // printf("%d \t %d \n ", NowMonth, NowYear);
    
    // printf("Watcher A");
    #pragma omp barrier // Done computing
    // printf("Watcher B");
    #pragma omp barrier // Done write back to globals

    NowMonth = (MonthCount % 12) +1 ;
    NowYear = MonthCount / 12 +1 ;

    unsigned int seed = omp_get_thread_num()*1234567;

    float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );
    float temp = AVG_TEMP - AMP_TEMP * cos( ang );
    NowTemp = temp + Ranf( -RANDOM_TEMP, RANDOM_TEMP, &seed );
    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
    float tempPrecip = precip + Ranf( -RANDOM_PRECIP, RANDOM_PRECIP, &seed );
    if (tempPrecip < 0){
        NowPrecip = 0;
    } else {
        NowPrecip = tempPrecip;
    }
    // printf("Month:%d  Year:%d  ", NowMonth, NowYear);
    // printf("Now Temp:%f   , Now Precip: %f   ", NowTemp, NowPrecip);
    // printf("Grains: %f   GrainDeers: %d  ", NowHeight, NowNumDeer);
    // printf("Typhoon Struck?: %d\n", TyphoonStruck);

    printf("%d\t%d\t%f\t%f\t%f\t%d\t%d\t\n",NowMonth, NowYear, NowTemp, NowPrecip, NowHeight, NowNumDeer, TyphoonStruck);

    MonthCount ++;

    #pragma omp barrier // Done Printing
};