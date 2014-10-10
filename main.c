//
//  main.c
//  Particle Filter
//  This program implements a particle filter
//
//  Created by Steven S. L. Xie on 9/10/14.
//  Copyright (c) 2014 XIE Shuanglong. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "random_number_gen.h"
#include "process_function.h"
#include "measure_function.h"
#include "euclid_dist.h"

#define N 30    // number of particles
#define T 100   // tracking time duration
#define DIM 2   // dimension of the variable


int main(int argc, const char * argv[])
{
    // Initialize variables
    //const char DIM = 2;
    

    double x[DIM] = {10,20}; //initial actual state
    float n_sys_cov = 0.2; // noise covariance in the system
    float n_mea_cov = 0.2; // noise covariance in the measurement
    double z[DIM];
    double *p;
    p = measure_function(x, n_mea_cov,DIM);
    for(int i = 0;i<DIM;i++)
        z[i] = *(p+i);
    
    double x_p[N][DIM];  // particles
    double z_p[N][DIM];  // outputs of the particles
    double weight[N]; // weights for resampling
    
    int V = 10; // variance of the initial state
    
    // Initialize the particles
    
    for(int i=0;i< N;i++)
    {
        for(int k=0;k<DIM;k++){
            x_p[i][k] = randn(x[k],sqrt(V));
        }
    }
    
    double sum = 0;
    double temp[N][DIM];  // a copy of the particle
    //temp = (double**)calloc(N*DIM,sizeof(double));
    
    double x_est[2] = {0,0};
    
    // The estimation process
    for(int t = 1;t <= T; t++){
        p = process_function(x, t, n_sys_cov,DIM);
        for(int k = 0;k < DIM;k++)
            x[k] = *(p+k);
        p = measure_function(x, n_mea_cov,DIM);
        for(int k = 0;k<DIM;k++)
            z[k] = *(p+k);
        
        for(int i = 0;i < N;i++){
            p = process_function(x_p[i], t, n_sys_cov,DIM);
            for(int k = 0;k<DIM;k++)
                x_p[i][k] = *(p+k);
            
            p = measure_function(x_p[i], n_mea_cov,DIM);
            for(int k = 0;k<DIM;k++)
                z_p[i][k] = *(p+k);

            //weight[i] = exp(-pow(z[0]-z_p[i][0],2)*0.5*n_mea_cov);
            weight[i] = exp(-euclid_dist(z, z_p[i]));
            //printf("%f\n",weight[i]);
        }
        
        for(int i = 0;i < N; i++)
            sum += weight[i];
        for(int i = 0;i < N; i++)
            weight[i] /= sum;
        
        sum = 0;
        
        // Resampling
        
        
        for(int i=0;i<N;i++)
        {
            for(int k = 0;k<DIM;k++){
                temp[i][k] = x_p[i][k];
            }
        }
        
        int sample = 0;
        for(int i=0;i<N;i++){
            sample = sample_by_weight(weight, N);
            for(int k = 0;k<DIM;k++){
                x_p[i][k] = temp[sample][k];
                x_est[k] += x_p[i][k];
            }
        }
        
        for(int k=0;k<DIM;k++)
            x_est[k] = x_est[k] / N;
        
        for(int k=0;k<DIM;k++)
            printf("\t%f\t%f",x[k],x_est[k]);
        
        printf("\n");
    }
    
    //free(temp);
    
    
        
    
    return 0;
}

