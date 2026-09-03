#ifndef FFT_H
#define FFT_H

#include <vector>
#include <complex>

class FFT
{
public:
    FFT();

    static std::vector<float> calculate(const std::vector<float>& samples, const std::vector<float>* window = nullptr);
};

#endif // FFT_H
