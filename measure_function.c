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

double measure_function(double x, double n)
{
    //define your measure function z=f(x) here
    // x is the state
    // n is the noise covariance
    return pow(x, 2)/20 + randn(0,n);
    
}
