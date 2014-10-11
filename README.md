Particle-Filter
===============

C Implementations of Particle Filter 

Done:

1. a basic framework of C implementations of Particle filter;
2. Support multi dimension state;

How to use it:

1. Define your process function and measure function in the corresponding files;
    1.1 process function describes how the state you want to estimate evolves;
    1.2 measure function describes how your measured variable is related to the state; The measured value can also be obtained from real measurements (e.g. in my case, from some sensor nodes). This can be achieved by changing a little bit in the measure function.
    
2. Define the time duration, number of particles in the macro in the main.c, as well as the noise covariance;

3. Define the dimension of the state in the particle.h

To-do:

1. The current implementation of the particle filter is a bit simplified. It conducts resampling every time which may not conform to the standard particle filter. But in general, it works well for my test functions. In the future I will add some more variants of the algorithms.

2. Modified for the future use in a microcontroller.



