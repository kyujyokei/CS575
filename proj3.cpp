#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define NUMT 1
#define NUM foo

struct s {
    float value;
    int pad[NUM];
} Array[4];

int foo = 0;


int main(){

    for (foo = 0 ; foo < 16 ; foo++){
        run();
    }

    return 0;
}



void run (){
    
    omp_set_num_threads( NUMT );

    int someBigNumber = 1000000000;

    double time0 = omp_get_wtime( );
    #pragma omp parallel for default(none),shared(Array),
    for( int i = 0; i < 4; i++ ){

        for( int j = 0; j < someBigNumber; j++ ){

            Array[ i ].value = Array[ i ].value + 2.;

        }

    }
    double time0 = omp_get_wtime( );

    printf("Mega Operations completed per second: %8.2lf",someBigNumber*4 / time1-time0 / 1000000.);

}


