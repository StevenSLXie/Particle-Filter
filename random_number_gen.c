//
//  random_number_gen.c
//  Particle Filter
//
//  Created by Steven S. L. Xie on 9/10/14.
//  Copyright (c) 2014 XIE Shuanglong. All rights reserved.
//

#include <math.h>
#include <stdlib.h>

// generate a random number following normal distribution

double
randn (double mu, double sigma)
{
    double U1, U2, W, mult;
    static double X1, X2;
    static int call = 0;
    
    if (call == 1)
    {
        call = !call;
        return (mu + sigma * (double) X2);
    }
    
    do
    {
        U1 = -1 + ((double) rand () / RAND_MAX) * 2;
        U2 = -1 + ((double) rand () / RAND_MAX) * 2;
        W = pow (U1, 2) + pow (U2, 2);
    }
    while (W >= 1 || W == 0);
    
    mult = sqrt ((-2 * log (W)) / W);
    X1 = U1 * mult;
    X2 = U2 * mult;
    
    call = !call;
    
    return (mu + sigma * (double) X1);
}

// generate a random number following uniform distribution from [a,b]
double
randu(int a, int b)
{
    double u = (((double) rand() / RAND_MAX) + 1)/2;
    return a+(b-a)*u;
}

int
sample_by_weight(double weight[], int N)
{
    //double *sum;
    //sum = (double*)calloc(N,sizeof(double));
    double sum[N];
    
    for(int i =0;i<N;i++)
        sum[i] = 0;
    
    for(int i=0;i< N;i++){
        for(int j=0;j<= i;j++)
        {
            sum[i] += weight[j];
        }
    }
    
    double x = randu(0,1);
    for(int i = 0;i<N;i++){
        if(sum[i]>x){
            //free(sum);
            return i;
        }
    }
    return -1; //error
}
