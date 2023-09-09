#include "signal.h"
#include <iostream>
//#include <iomanip> // chyba cie nie potrzebuje
#include <fftw3.h>

const float pi = 3.14159265358979323846;

using Complex = std::complex<float>;


void Signal::DFT(){
	std::cout << "Jeszcze żyje";
	Complex* temp = new Complex[numElements];
	
	for(int i=0; i<numElements; i++)
		temp[i] = Complex(signal[i],0);

	// to trzeba ogarnąć tak żeby nie tworzyć zmiennej temp
	fftw_plan fftPlan = fftw_plan_dft_1d(numElements, reinterpret_cast<fftw_complex*>(temp), reinterpret_cast<fftw_complex*>(fourier), FFTW_FORWARD, FFTW_ESTIMATE);
	// FFTW_FORWARD  = wskazuje że używana będzie FFT nie iFFT

	fftw_execute(fftPlan);

	fftw_destroy_plan(fftPlan);

	delete [] temp;
}

void Signal::iDFT(){
    Complex* temp = new Complex[numElements]; // może trzeba jeszcze zerować idk 

	fftw_plan ifftPlan = fftw_plan_dft_1d(numElements, reinterpret_cast<fftw_complex*>(fourier), reinterpret_cast<fftw_complex*>(temp), FFTW_BACKWARD, FFTW_MEASURE);

	fftw_execute(ifftPlan);

	fftw_destroy_plan(ifftPlan);

	for( int i=0; i< numElements; i++){
		if( fabs(temp[i].imag()) > 0.01)
			std::cout << "fabs(temp[i]) >> 0, niedokładna ta transformata" << std::endl;
		signal[i] = temp[i].real();
	}

    delete [] temp;
}
/*


int main(){ // zamiast main'a będzie szło DFT lub IDFT.
	Complex test[] = { 1.0, 2.0, 2.5, 3.7, 5.1, 12415, 346346, 23536, 20314 };
	int N = sizeof test / sizeof test[0];
	Complex * ft = new Complex[N];
	
	// Forward transform
	FFT(test, ft, N);

	// Invert transform
	iFFT(ft, test, N);

	delete[] ft;
}*/


//======================================================================

// f = Signal
// ftilde = fourier
// N = numElements
// step = 
/*
void FFT(Complex* f, Complex* ftilde, int N, int step){	// Fast Fourier Transform
	if (N > 2 && N % 2 == 0){	// Recursion if a multiple of 2
		int N2 = N >> 1;
		Complex* g = new Complex[N];

		int step2 = step << 1;
		FFT(f, g, N2, step2);
		FFT(f + step, g + N2, N2, step2);

		Complex w = std::polar(1.0F, -2 * pi / N);
		Complex wn = 1.0F;
		for (int n = 0; n < N2; n++){
			if (n > 0)
				wn *= w;
			ftilde[n] = g[n] + wn * g[n + N2];
			ftilde[n + N2] = g[n] - wn * g[n + N2];
		}

		delete[] g;
	}
	else{	// Otherwise just do a DFT
		DFT(f, ftilde, N, step);
	}
}*/

//======================================================================
/*
void DFT(Complex* f, Complex* ftilde, int N, int step){// Basic Discrete Fourier Transform
	Complex w = std::polar(1.0F, -2 * pi / N); 
	Complex wn = 1.0;
	for (int n = 0; n < N; n++)
	{
		if (n > 0) 
			wn *= w;
		Complex wm = 1.0;
		ftilde[n] = 0.0;
		for (int m = 0, mpos = 0; m < N; m++, mpos += step)
		{
			if (m > 0)
				wm *= wn;
			ftilde[n] += f[mpos] * wm;
		}
	}
}*/

//======================================================================

/*
void iFFT(Complex* ftilde, Complex* f, int N){ // Inverse Fast Fourier Transform
	Complex* ftildeConjugate = new Complex[N];
	for (int m = 0; m < N; m++)
		ftildeConjugate[m] = conj(ftilde[m]);

	FFT(ftildeConjugate, f, N);

	float factor = 1.0 / N;
	for (int m = 0; m < N; m++)
		f[m] = conj(f[m]) * factor;

	delete[] ftildeConjugate;
}*/
