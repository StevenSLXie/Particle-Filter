//
//  euclid_dist.c
//  Particle Filter
//
//  Created by Steven S. L. Xie on 10/10/14.
//  Copyright (c) 2014 XIE Shuanglong. All rights reserved.
//

#include <math.h>

double
euclid_dist(double *x, double *y){
    
    return sqrt(pow(x[0]-y[0],2)+pow(x[1]-y[1],2));
}
