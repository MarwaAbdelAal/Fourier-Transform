// #include <math.h>
#include <complex>
#include <vector>
#include <iostream>
#include <fstream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
using namespace std;

// double x;
// ifstream inFile;
// // Reading file
// int line = 0;

// samples is of type vector of complex the same as the output
vector<complex<double>> dft(vector<complex<double>> data)
{
    int N = data.size();
    int K = N;

    // we will restore each value of X[k] into newData to then append it into the vector dftoutput
    complex<double> newData;
    vector<complex<double>> dftoutput;

    // make the size of dftoutput the same as K (input size)
    dftoutput.reserve(K);

    // loop through each K
    for (int k = 0; k < K; k++)
    {
        // loop through each n
        newData = (0, 0);
        for (int n = 0; n < N; n++)
        {
            double realPart = cos(((2 * M_PI) / N) * k * n);
            double imagPart = sin(((2 * M_PI) / N) * k * n);
            complex<double> w(realPart, -imagPart);
            newData += data[n] * w;
        }
        dftoutput.push_back(newData);
    }
    return dftoutput;
}

vector<complex<double>> fft(vector<complex<double>> &data)
{
    // find the number of data we have
    int N = data.size();
    // Execute the end of the recursive even/odd splits once we only have one sample
    if (N == 1) {return data;}

    /* Split the sampels into even and odd subsums */
    // Find half the total number of data
    int M = N/2;
    // Declare an even and odd complex vector
    vector<complex<double>> Xeven(M,0);
    vector<complex<double>> Xodd(M,0);

    // Input the even and odd sampels into recursive vectors
    for (int i = 0; i != M; i++)
    {
        Xeven[i] = data[2*i];
        Xodd[i] = data[2*i + 1];
    }
    // Perform the recursive FFT operation on the odd and even sides
    vector<complex<double>> Feven(M,0);
    Feven = fft(Xeven);
    vector<complex<double>> Fodd(M,0);
    Fodd = fft(Xodd);
    /*------ END RECURSION ______ */

    // Declare vector of frequency bins
    vector<complex<double>> freqbins(N,0);
    // Combine the values found
    for (int k = 0; k != N/2; k++)
    {
        // For each split set, we need to multiply a k-dependent comlpex number by the odd sunsum
        complex<double> cmplxexponential = polar(1.0, -2*M_PI*k/N) * Fodd[k];
        freqbins[k] = Feven[k] + cmplxexponential;
        // Everytime you add pi, exponential changes sign
        freqbins[k+N/2] = Feven[k] - cmplxexponential;
    }
    return freqbins;
}

// Connection between python and c++
PYBIND11_MODULE(module_name ,handle){
    handle.def("dft", &dft, "A function returns dft");
    handle.def("fft", &fft, "A function returns fft");
}


// int main()
// {

//     inFile.open("data1.txt");

//     vector<complex<double>> Data, dft_output, fft_output; // Create vectors of complex numbers

//     while (inFile >> x)
//     {
//         Data.push_back(complex<double>(x));
//         cout << "x is "<< x<< " complex format is " << complex<double>(x) << endl;
//     }

//     inFile.clear();
//     inFile.seekg(0, std::ios::beg);

//     dft_output = dft(Data);
//     fft_output = fft(Data);

//     for (int z = 0; z < 10; z++)
//     {
//         cout << "input: " << Data[z] << endl;
//         cout << "DFT: " << dft_output[z] <<'\n' ;
//         cout << "FFT: " << fft_output[z] <<'\n' ;
//         cout << fft_output[z].real() << " + " << fft_output[z].imag() << 'i' << '\n';
//         cout <<'\n' ;
//     }

//     while (inFile >> x)
//     {
//         line++;
//     }

//     cout<< "Number of lines = " << line <<'\n';
// }
