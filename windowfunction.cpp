#include "windowfunction.h"

WindowFunction::WindowFunction() {}

std::vector<float> WindowFunction::hanning(int size)
{
    std::vector<float> window(size);
    constexpr float PI = 3.14159265358979323846f;

    for(int i = 0; i<size; ++i){
        window[i] = 0.5 * (1-cos((2*PI * i)/(size - 1)));
    }

    return window;
}
