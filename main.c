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


int main(int argc, const char * argv[])
{
    // Initialize variables
    
    double x = 0.1; //initial actual state
    float n_sys_cov = 0.05; // noise covariance in the system
    float n_mea_cov = 0.02; // noise covariance in the measurement
    const int T = 100; // tracking times
    const int N = 30; // number of particles
    double z = pow(x, 2)/20 + randn(0,n_mea_cov);
    
    double x_p[N];
    double z_p[N];
    double weight[N];
    
    int V = 1; // variance of the initial state
    
    // Initialize the particles
    
    for(int i=0;i< N;i++)
        x_p[i] = randn(x,sqrt(V));
    
    double sum = 0;
    double *temp;  // a copy of the particle
    temp = (double*)calloc(N,sizeof(double));
    double x_est = 0;
    
    // The estimation process
    for(int t = 1;t <= T; t++){        
        x = process_function(x, t, n_sys_cov);
        z = measure_function(x, n_mea_cov);
        
        for(int i = 0;i < N;i++){
            
            x_p[i] = process_function(x_p[i], t, n_sys_cov);
            z = measure_function(x, n_mea_cov);
            weight[i] = exp(-pow(z-z_p[i],2)*0.5*n_mea_cov);
            //printf("%f\n",weight[i]);
        }
        
        for(int i = 0;i < N; i++)
            sum += weight[i];
        for(int i = 0;i < N; i++)
            weight[i] /= sum;
        
        sum = 0;
        
        // Resampling
        
        
        for(int i=0;i<N;i++)
            temp[i] = x_p[i];
        for(int i=0;i<N;i++){
            x_p[i] = temp[sample_by_weight(weight, N)];
            sum += x_p[i];
        }
        x_est = sum / N;
        sum = 0;
        
        printf("%f\t%f\n",x,x_est);
    }
    
    free(temp);
    
    
        
    
    return 0;
}

