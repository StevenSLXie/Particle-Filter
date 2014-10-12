//
//  resampling.c
//  Particle Filter
//
//  Created by Steven S. L. Xie on 12/10/14.
//  Copyright (c) 2014 XIE Shuanglong. All rights reserved.
//

#include <stdio.h>
#include "random_number_gen.h"
#include "particle.h"
#include <stdlib.h>


void cum_sum(struct particle p[], double *sum, int N){
    
    for(int i =0;i<N;i++)
        sum[i] = 0;
    
    for(int i=0;i< N;i++){
        for(int j=0;j<= i;j++)
        {
            sum[i] +=  p[j].weight;
        }
        //printf("%f\t", sum[i]);
    }

}

int
multimodal_resampling(struct particle p[], int N)
{
    //double *sum;
    //sum = (double*)calloc(N,sizeof(double));
    double sum[N];
    
    
    //cum_sum(p,sum,N);
    
    for(int i =0;i<N;i++)
        sum[i] = 0;
    
    for(int i=0;i< N;i++){
        for(int j=0;j<= i;j++)
        {
            sum[i] += p[j].weight;
        }
        //printf("%f\t", sum[i]);
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

int stratified_resampling(struct particle p[], int N){
    static double s;

    double sum[N];
    
    //cum_sum(p,sum,N);
    
    
    for(int i =0;i<N;i++)
        sum[i] = 0;
    
    for(int i=0;i< N;i++){
        for(int j=0;j<= i;j++)
        {
            sum[i] += p[j].weight;
        }
        //printf("%f\t", sum[i]);
    }
    
    
    //for(int i = 0;i<N;i++)
    //    printf("%f\t",sum[i]);
    //printf("\n");
    
    double x = s + (1.0/N)*randu(0,1);
    int index;
    
    for(int i = 0;i<N;i++){
        if(sum[i]>x){
            //free(sum);
            index = i;
            break;
        }
    }
    
    s += (float)(1.0/N);
    
    if((1-s)<0.1/N)
        s = 0;
    
    //printf("%f\n",s);
    
    return index;
    
    
}


