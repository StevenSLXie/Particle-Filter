//
//  euclid_dist.c
//  Particle Filter
//
//  Created by Steven S. L. Xie on 10/10/14.
//  Copyright (c) 2014 XIE Shuanglong. All rights reserved.
//

#include <math.h>

double
euclid_dist(double *x, double *y, int dim){
    
    double temp = 0;
    for(int i=0;i<dim;i++)
        temp += pow(x[i]-y[i],2);
    
    temp = sqrt(temp);
    return temp;
}
