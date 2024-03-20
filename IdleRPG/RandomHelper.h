#pragma once
#include <cstdlib>

namespace RandomHelper
{
  inline int RandomInRange(int minInclusive, int maxInclusive)
  {
    int randomValue = rand();
    int valueInRange = randomValue % (maxInclusive - minInclusive + 1);
    return minInclusive + valueInRange;
  }

  inline float RandomInRange(float minInclusive, float maxInclusive)
  {
    int randomValue = rand();
    float normalisedValue = static_cast<float>(randomValue) / RAND_MAX;
    return minInclusive + (normalisedValue * (maxInclusive - minInclusive));
  }
}
