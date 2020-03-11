/* exp-random.c */

/* Instead of using a uniform distribution, we'll use
 * an exponential distribution, which should better model
 * the real-world system
 *
 * Poisson process
 *
 * Randomly generated values are the times between
 * process arrivals
 *
 * Events occur continuously and independently, but we
 *  have arrivals occurring at a constant average rate
 *
 * Memoryless or Markov    (M/M/1 queues)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

int main()
{
    srand48( 2 );

    /* uniform to exponential distribution: */
    /*                                      */
    double min = 0;     /*       -ln(1-r)                       */
    double max = 0;     /*  x = ----------                      */
    double sum = 0;     /*        lambda                        */

    int iterations = 1000000;     /* <== make this number very large */

    for ( int i = 0 ; i < iterations ; i++ )
    {
        double lambda = 0.001;  /* average should be 1/lambda ==> 1000 */

        double r = drand48();   /* uniform dist [0.00,1.00) -- also check out random() */
        double x = -log( r ) / lambda;  /* log() is natural log */

        /* avoid values that are far down the "long tail" of the distribution */
        if ( x > 8000 ) { i--; continue; }

        if ( i < 30){

            printf( "r is %lf\n", r );
            printf( "x is %lf\n", x );
        }
        sum += x;
        if ( i == 0 || x < min ) { min = x; }
        if ( i == 0 || x > max ) { max = x; }
    }

    double avg = sum / iterations;

    printf( "minimum value: %lf\n", min );
    printf( "maximum value: %lf\n", max );
    printf( "average value: %lf\n", avg );
}