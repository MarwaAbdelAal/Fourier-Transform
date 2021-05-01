#include <math.h>
#include <complex>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

double x;

ifstream inFile;

// samples is of type vector of complex the same as the output
vector<complex<double>> dft(vector<complex<double>> data)
{
    int N = data.size();
    int K = N;

    // we will restore each value of X[k] into newData to then append it into the vector fftOutput
    complex<double> newData;
    vector<complex<double>> fftOutput;

    // make the size of fftOutput the same as K (input size)
    fftOutput.reserve(K);

    // loop through each K
    for (int k = 0; k < K; k++)
    {
        // loop through each n
        newData = complex<double>(0, 0);
        for (int n = 0; n < N; n++)
        {
            double realPart = cos(((2 * M_PI) / N) * k * n);
            double imagPart = sin(((2 * M_PI) / N) * k * n);
            complex<double> w(realPart, -imagPart);
            newData += data[n] * w;
        }
        fftOutput.push_back(newData);
    }
    return fftOutput;
}

vector<complex<double>> fft(vector<complex<double>> data)
{
    int N = data.size();
    if (N == 1) {return data;}

    int M = N/2;
    vector<complex<double>> Xeven(M,0);
    vector<complex<double>> Xodd(M,0);

    for (int i = 0; i != M; i++)
    {
        Xeven[i] = data[2*i];
        Xodd[i] = data[2*i + 1];
    }
    vector<complex<double>> Feven(M,0);
    Feven = fft(Xeven);
    vector<complex<double>> Fodd(M,0);
    Fodd = fft(Xodd);

    // Declare vector of frequency bins
    vector<complex<double>> freqbins(N,0);

    for (int k = 0; k != N/2; k++)
    {
        complex<double> cmplxexponential = polar(1.0, -2*M_PI*k/N) * Fodd[k];
        freqbins[k] = Feven[k] + cmplxexponential;
        freqbins[k+N/2] = Feven[k] - cmplxexponential;
    }
    return freqbins;
}


int main()
{

    // Create a test signal
    int N = 1000;
    vector<complex<double>> signal;
    signal.reserve(N);

    double sigK = 3.0;
    double sigPhase = 0.0;

    for (int x=0; x<N; ++x)
    {
        auto currentSample = complex<double>(cos((2*M_PI / static_cast<double>(N)) * sigK * static_cast<double>(x) + sigPhase), 0.0);
        signal.push_back(currentSample);
    }

    // Compute the DFT
    vector<complex<double>> Fx = dft(signal);
    
    // Compute the FFT
    vector<complex<double>> FFx = fft(signal);


    // vector<complex<double>> data, dft_data;

    // inFile.open("data.txt");
    // while (inFile >> x)
    // {
    //     data.push_back(complex<double>(x));
    // }

    // inFile.clear();
    // inFile.seekg(0, ios::beg);

    // dft_data = dft(data);

    cout << '\n' << "DFT" << '\n';
    for (int i = 0; i < 6 ; i++)
    {
        // cout << "DFT " << dft_data[i] << '\n';
        cout << Fx[i].real()/static_cast<double>(N) << '\t' << Fx[i].imag()/static_cast<double>(N) << '\n';
    }

    cout << '\n' << "FFT" << '\n';

    for (int z = 0; z < 6; z++)
    {
        cout << "FFT: " << FFx[z] <<'\n' ;
        cout <<'\n' ;
        // cout<<TransformedData[i].real()+TransformedData[i].imag()*1i;
    }

    for (int i = 0; i < 6 ; i++)
    {
        cout << FFx[i].real()/static_cast<double>(N) << '\t' << FFx[i].imag()/static_cast<double>(N) << '\n';
    }
}