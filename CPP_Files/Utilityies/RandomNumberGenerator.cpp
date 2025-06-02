//
// Created by fanel012 on 5/31/25.
//

#include "RandomNumberGenerator.h"
std::random_device RandomNumberGenerator::m_randomDevice;
std::mt19937_64 RandomNumberGenerator::m_randomGenerator;

float RandomNumberGenerator::GetRandomNumber(float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(m_randomGenerator);
}