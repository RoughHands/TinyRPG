//
//  RandomNumberGenerator.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RandomNumberGenerator__
#define __TinyRPG__RandomNumberGenerator__

#include <random>
#include <chrono>

typedef std::chrono::system_clock           SystemClock;

typedef std::uniform_real_distribution<double> RandomNumberGeneratorDouble;
typedef std::uniform_real_distribution<float> RandomNumberGeneratorFloat;

class RandomNumberGenerator
{
private:
    static std::mt19937_64*     generatorEngine;
    static std::uniform_int_distribution<int>* intDistribution;
    static std::uniform_int_distribution<int64_t>* int64Distribution;
    static RandomNumberGeneratorDouble* doubleDistribution;
    static RandomNumberGeneratorFloat*  floatDistribution;

public:
    RandomNumberGenerator()
    {
    }
    
    ~RandomNumberGenerator()
    {
    }
    
    static std::mt19937_64& GetGeneratorEngine();

    static void Initialize();
    static const float Float(); // range : 0 to 1
    static const double Double(); // range : 0 to 1
    static const int Int(const int min, const int max);
    static const int64_t Int64(const int64_t min, const int64_t max);
};



#endif /* defined(__TinyRPG__RandomNumberGenerator__) */
