#include "fft.h"
#include <cmath>

FFT::FFT() {}

std::vector<float> FFT::calculate(const std::vector<float> &samples, const std::vector<float>* window)
{
    const int N = samples.size();

    if(N == 0){
        return {};
    }

    if((N & (N-1)) != 0){
        return {};
    }

    using Complex = std::complex<float>;

    std::vector<Complex> data(N);

    if (window && window->size() == N){
        for(int i = 0; i< N; i++){
            data[i] = Complex(samples[i] * (*window)[i], 0.0f);
        }
    }
    else{
        for (int i = 0; i < N; i++)
        {
            data[i] = Complex(samples[i], 0.0f); //перевод семплов в комплексные числа
        }

    }


    for (int i = 1, j = 0; i < N; i++)
    {
        int bit = N >> 1;

        while (j & bit)
        {
            j ^= bit;
            bit >>= 1;
        }

        j ^= bit;

        if (i < j)
            std::swap(data[i], data[j]);
    }

    //FFT

    constexpr float PI = 3.14159265358979323846f;

    for (int len = 2; len <= N; len *= 2)
    {
        float angle = -2.0f * PI / len;

        Complex wlen(std::cos(angle),std::sin(angle));

        for (int i = 0; i < N; i += len)
        {
            Complex w(1.0f, 0.0f);

            for (int j = 0; j < len / 2; j++)
            {
                Complex u = data[i + j];

                Complex v = data[i + j + len / 2] * w;

                data[i + j] = u + v;

                data[i + j + len / 2] = u - v;

                w *= wlen;
            }
        }
    }

    // Получаем амплитуды

    std::vector<float> spectrum(N / 2);

    for (int i = 0; i < N / 2; i++)
    {
        spectrum[i] = std::abs(data[i]) / N * 2.0f;
    }

    return spectrum;
}
