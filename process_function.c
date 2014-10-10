//
//  process_function.c
//  Particle Filter
//
//  Created by Steven S. L. Xie on 9/10/14.
//  Copyright (c) 2014 XIE Shuanglong. All rights reserved.
//

#include <stdio.h>
#include "random_number_gen.h"
#include <math.h>

double
*process_function(double *x, int t, double n, char dim){
    // define your process function x(t+1) = f(x(t),t) here
    // x is the state
    // t is the discrete time
    // n is the noise covariance
    // dim is the dimension of the state
    
    if (2 == dim){
        static double r[2];
        r[0] = (0.5*x[0] + 25*x[0]/(1+pow(x[0], 2))+8*cos(1.2*(t-1)) + randn(0,n));
        r[1] = (x[1]+randn(0,n));
        return r;
    }
    else if(1 == dim){
        static double r[1];
        r[0] = (0.5*x[0] + 25*x[0]/(1+pow(x[0], 2))+8*cos(1.2*(t-1)) + randn(0,n));
        return r;
    }
    else
        exit(0);
}
