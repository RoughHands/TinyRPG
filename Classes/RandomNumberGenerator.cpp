//
//  RandomNumberGenerator.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RandomNumberGenerator.h"

std::mt19937_64*                    RandomNumberGenerator::generatorEngine = nullptr;
std::uniform_int_distribution<int>* RandomNumberGenerator::intDistribution = nullptr;
std::uniform_int_distribution<int64_t>* RandomNumberGenerator::int64Distribution = nullptr;
std::uniform_real_distribution<double>* RandomNumberGenerator::doubleDistribution = nullptr;
std::uniform_real_distribution<float>* RandomNumberGenerator::floatDistribution = nullptr;

void RandomNumberGenerator::Initialize()
{
    if( generatorEngine == nullptr )
    {
        generatorEngine = new std::mt19937_64(static_cast<uint64_t>( SystemClock::to_time_t(SystemClock::now()) ));
    }
    if( intDistribution == nullptr )
    {
        intDistribution = new std::uniform_int_distribution<int>;
    }
    if( int64Distribution == nullptr )
    {
        int64Distribution= new std::uniform_int_distribution<int64_t>;
    }
    
    if( doubleDistribution == nullptr )
    {
        doubleDistribution = new std::uniform_real_distribution<double>;
    }
    if( floatDistribution == nullptr )
    {
        floatDistribution = new std::uniform_real_distribution<float>;
    }

    
}


std::mt19937_64& RandomNumberGenerator::GetGeneratorEngine()
{
    if( generatorEngine == nullptr )
    {
        generatorEngine = new std::mt19937_64(static_cast<uint64_t>( SystemClock::to_time_t(SystemClock::now()) ));
    }
    return *generatorEngine;
}

const float RandomNumberGenerator::Float()
{
    Initialize();
    return floatDistribution->operator()(*generatorEngine);
}

const double RandomNumberGenerator::Double()
{
    Initialize();
    return (*doubleDistribution)(*generatorEngine);
}

const int RandomNumberGenerator::Int(const int min, const int max)
{
    Initialize();
    const int range = max-min;
    return (*intDistribution)(*generatorEngine)%range + min ;
    
}

const int64_t RandomNumberGenerator::Int64(const int64_t min, const int64_t max)
{
    Initialize();
    const int64_t range = max - min;
    return (*int64Distribution)(*generatorEngine)%range+min;
}
