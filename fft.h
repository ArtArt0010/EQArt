#ifndef FFT_H
#define FFT_H

#include <vector>
#include <complex>

class FFT
{
public:
    FFT();

    static std::vector<float> calculate(const std::vector<float>& samples);
};

#endif // FFT_H
