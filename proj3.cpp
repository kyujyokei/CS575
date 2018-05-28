#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define NUMT 1
#define NUM 1

void run ();



struct s {
    float value;
    int pad[NUM];
} Array[4];




int main(){

    // for (foo = 0 ; foo < 16 ; foo++){
    run();
    // }

    return 0;
}



void run (){
    
    omp_set_num_threads( NUMT );

    int someBigNumber = 1000000000;

    double time0 = omp_get_wtime( );
    #pragma omp parallel for default(none),shared(Array,someBigNumber)
    for( int i = 0; i < 4; i++ ){

        for( int j = 0; j < someBigNumber; j++ ){

            Array[ i ].value = Array[ i ].value + 2.;

        }

    }
    double time1 = omp_get_wtime( );

    printf("%d threads NUM: %d Mega Operations: %8.2lf",NUMT, NUM, someBigNumber*4 / time1-time0 / 1000000.);

}


