//
//  measure_function.c
//  Particle Filter
//
//  Created by Steven S. L. Xie on 9/10/14.
//  Copyright (c) 2014 XIE Shuanglong. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "random_number_gen.h"

double *measure_function(double *x, double n, char dim)
{
    //define your measure function z=f(x) here
    // x is the state
    // n is the noise covariance
    // dim is the dimension of the state. Here assume dim=2
    if(3 == dim){
        // define your function
        static double r[3];
        r[0] = (pow(x[0],2)/20+randn(0,n));
        r[1] = (10*x[1] + randn(0,n));
        r[2] = (x[2]*x[1])+randn(0,2*n);
        return r;
    }
    else if(1 == dim){
        //case when dim = 1
        static double r[1];
        r[0] = (pow(x[0], 2)/20 + randn(0,n));
        return r;
    }
    else
        exit(0);
    
    // case when dim = 1
    //return pow(x, 2)/20 + randn(0,n);
    
}
