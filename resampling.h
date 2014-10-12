//
//  resampling.h
//  Particle Filter
//
//  Created by Steven S. L. Xie on 12/10/14.
//  Copyright (c) 2014 XIE Shuanglong. All rights reserved.
//

#ifndef Particle_Filter_resampling_h
#define Particle_Filter_resampling_h

#include "particle.h"

int multimodal_resampling(struct particle p[], int N);

int stratified_resampling(struct particle p[], int N);


#endif
