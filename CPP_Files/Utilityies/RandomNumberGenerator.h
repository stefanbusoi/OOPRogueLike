//
// Created by fanel012 on 5/31/25.
//

#pragma once
#include <random>


class RandomNumberGenerator {

   static std::random_device m_randomDevice;
   static std::mt19937_64 m_randomGenerator;
public:
   static float GetRandomNumber(float min,float max);
};


