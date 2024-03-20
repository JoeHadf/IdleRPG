#pragma once

namespace ClampHelper
{
  template <typename T>
  T Clamp(T valueToClamp, T lower, T upper)
  {
    if(lower > upper)
    {
      const T temp = lower;
      lower = upper;
      upper = temp;
    }

    if(valueToClamp < lower) valueToClamp = lower;
    if(valueToClamp > upper) valueToClamp = upper;
    return valueToClamp;
  }
}