//
// Created by fanel012 on 5/31/25.
//

#pragma once
#include <random>


class RandomNumberGenerator {

   static std::random_device randomDevice;
   static std::mt19937_64 randomGenerator;
public:
   static float GetRandomNumber(float min,float max);
};


