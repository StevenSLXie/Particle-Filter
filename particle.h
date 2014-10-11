//
//  particle.h
//  Particle Filter
//
//  Created by Steven S. L. Xie on 11/10/14.
//  Copyright (c) 2014 XIE Shuanglong. All rights reserved.
//

#ifndef Particle_Filter_particle_h
#define Particle_Filter_particle_h

#define DIM 2

struct particle{
    double x[DIM];
    double z[DIM];
    double weight;
};

#endif
