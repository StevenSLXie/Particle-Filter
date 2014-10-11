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
#include "particle.h"

#define N 30    // number of particles
#define T 100   // tracking time duration
//#define DIM 2   // dimension of the variable
#define SYS_COV 0.2  // noise covariance in the system
#define MEA_COV 0.2  // noise covariance in the measurement
#define V 400 // variance of the particles



int main(int argc, const char * argv[])
{
    // Initialize the state
    
    struct particle state;
    
    state.x[0] = 10;
    state.x[1] = 20;
    state.x[2] = 30;

    double *p;
    p = measure_function(state.x, MEA_COV,DIM);
    
    for(int i = 0;i<DIM;i++)
        state.z[i] = *(p+i);
    
    // initialize the particles
    
    struct particle particles[N];
    
    for(int i=0;i<N;i++){
        for(int k=0;k<DIM;k++){
            particles[i].x[k] = randn(0,sqrt(V));
        }
        //particles[i].x[1] = randn(0,sqrt(V));
        particles[i].weight = 1;
    }
    
    double sum = 0;
    double temp[N][DIM];  // a copy of the particle
    
    double x_est[DIM] = {0,0,0};
    
    // The estimation process
    for(int t = 1;t <= T; t++){
        p = process_function(state.x, t, SYS_COV,DIM);
        for(int k = 0;k < DIM;k++)
            state.x[k] = *(p+k);
        p = measure_function(state.x, MEA_COV,DIM);
        for(int k = 0;k<DIM;k++)
            state.z[k] = *(p+k);
        
        for(int i = 0;i < N;i++){
            p = process_function(particles[i].x, t, SYS_COV,DIM);
            for(int k = 0;k<DIM;k++)
                particles[i].x[k] = *(p+k);
            
            p = measure_function(particles[i].x, MEA_COV,DIM);
            for(int k = 0;k<DIM;k++)
                particles[i].z[k] = *(p+k);

            //weight[i] = exp(-pow(z[0]-z_p[i][0],2)*0.5*MEA_COV);
            particles[i].weight = exp(-euclid_dist(state.z, particles[i].z));
            //printf("%f\n",weight[i]);
        }
        
        for(int i = 0;i < N; i++)
            sum += particles[i].weight;
        for(int i = 0;i < N; i++)
            particles[i].weight /= sum;
        
        sum = 0;
        
        // Resampling
        
        
        for(int i=0;i<N;i++)
        {
            for(int k = 0;k<DIM;k++){
                temp[i][k] = particles[i].x[k];
            }
        }
        
        int sample = 0;
        for(int i=0;i<N;i++){
            sample = sample_by_weight(particles, N);
            for(int k = 0;k<DIM;k++){
                particles[i].x[k] = temp[sample][k];
                x_est[k] += particles[i].x[k];
            }
        }
        
        for(int k=0;k<DIM;k++)
            x_est[k] = x_est[k] / N;
        
        for(int k=0;k<DIM;k++)
            printf("\t%f\t%f",state.x[k],x_est[k]);
        
        printf("\n");
    }
    return 0;
}

