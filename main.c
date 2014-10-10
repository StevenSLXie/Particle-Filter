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
    const char dim = 2;
    

    double x[dim] = {10,20}; //initial actual state
    float n_sys_cov = 0.25; // noise covariance in the system
    float n_mea_cov = 0.02; // noise covariance in the measurement
    const int T = 100; // tracking times
    const int N = 30; // number of particles
    double z[dim];
    double *p;
    p = measure_function(x, n_mea_cov,dim);
    for(int i = 0;i<dim;i++)
        z[i] = *(p+i);
    
    double x_p[N][dim];  // particles
    double z_p[N][dim];  // outputs of the particles
    double weight[N]; // weights for resampling
    
    int V = 10; // variance of the initial state
    
    // Initialize the particles
    
    for(int i=0;i< N;i++)
    {
        for(int k=0;k<dim;k++){
            x_p[i][k] = randn(x[k],sqrt(V));
        }
    }
    
    double sum = 0;
    double temp[N][dim];  // a copy of the particle
    //temp = (double**)calloc(N*dim,sizeof(double));
    
    double x_est[2] = {0,0};
    
    // The estimation process
    for(int t = 1;t <= T; t++){
        p = process_function(x, t, n_sys_cov,dim);
        for(int k = 0;k < dim;k++)
            x[k] = *(p+k);
        p = measure_function(x, n_mea_cov,dim);
        for(int k = 0;k<dim;k++)
            z[k] = *(p+k);
        
        for(int i = 0;i < N;i++){
            p = process_function(x_p[i], t, n_sys_cov,dim);
            for(int k = 0;k<dim;k++)
                x_p[i][k] = *(p+k);
            
            p = measure_function(x_p[i], n_mea_cov,dim);
            for(int k = 0;k<dim;k++)
                z_p[i][k] = *(p+k);

            weight[i] = exp(-pow(z[0]-z_p[i][0],2)*0.5*n_mea_cov);
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
            for(int k = 0;k<dim;k++){
                temp[i][k] = x_p[i][k];
            }
        }
        
        int sample = 0;
        for(int i=0;i<N;i++){
            sample = sample_by_weight(weight, N);
            for(int k = 0;k<dim;k++){
                x_p[i][k] = temp[sample][k];
                x_est[k] += x_p[i][k];
            }
        }
        
        for(int k=0;k<dim;k++)
            x_est[k] = x_est[k] / N;
        
        for(int k=0;k<dim;k++)
            printf("%f\t%f\n",x[k],x_est[k]);
    }
    
    //free(temp);
    
    
        
    
    return 0;
}

