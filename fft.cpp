#include "signal.h"
#include <iostream>
#include <fftw3.h>

const float pi = 3.14159265358979323846;



void Signal::DFT(){
	fftw_complex* temp = new fftw_complex[numElements];
	fftw_complex* temp2 = new fftw_complex[numElements];	

	for(int i=0; i<numElements; i++){
		temp[i][0] = signal[i];
		temp[i][1] = 0;
	
		temp2[i][0] = fourier[i].real();
		temp2[i][0] = fourier[i].imag();
	}

	// to trzeba ogarnąć tak żeby nie tworzyć zmiennej temp
	fftw_plan fftPlan = fftw_plan_dft_1d(numElements, temp, temp2, FFTW_FORWARD, FFTW_ESTIMATE);
	// FFTW_FORWARD  = wskazuje że używana będzie FFT nie iFFT

	fftw_execute(fftPlan);

	for( int i=0; i<numElements; i++)
		fourier[i] = Complex(temp2[i][0], temp2[i][1]);

	std::cout << "Jeszcze żyje" << std::flush;
	
	fftw_destroy_plan(fftPlan);


	delete [] temp2;
	delete [] temp;
}

void Signal::iDFT(){
   	fftw_complex* temp = new fftw_complex[numElements];
	fftw_complex* temp2 = new fftw_complex[numElements];	

	for(int i=0; i<numElements; i++){
		temp[i][0] = signal[i];
		temp[i][1] = 0;
	
		temp2[i][0] = fourier[i].real();
		temp2[i][0] = fourier[i].imag();
	}

	std::cout << "Tu jestem" << std::flush;	

	fftw_plan ifftPlan = fftw_plan_dft_1d(numElements, temp2, temp, FFTW_BACKWARD, FFTW_MEASURE);

	std::cout << "Tu jestem" << std::flush;

	fftw_execute(ifftPlan);

	fftw_destroy_plan(ifftPlan);

	for( int i=0; i< numElements; i++)
		signal[i] = short(temp2[i][0]);

    delete [] temp;
	delete [] temp2;
}
