#ifndef Signal_H
#define Signal_H

#include <iostream>
#include <complex>
#include <fftw3.h>

class Signal{
	std::string title;
	short *signal, bits; // signal - sygnał zapisany w formacie PCM.
	fftw_complex* fourier; // fourier - Liczby zespolone po transformacie fouriera, fftw_complex traktować jak double* o 2 elementach tj. fourier[n][0] -> liczba rzeczywista n-tego elementu tablicy, fourier[n][1] -> liczba urojona
	int encoding, channels, numElements; // jeśli dobrze rozumiem, to encoding var zawiera liczbę bitów oraz zmienną w jakiej zapisane są próbki (Szczególnie wygodne w przypadku plików .WAV). numElements - liczba elementów w tablicy. numElements*sizeof(short) daje liczbe bajtów obv
	long frequency;
	size_t bufsize;    // bufsize = ilość bajtów jednego w jednym buforze.


	public:
		Signal(const char*); // konstruktor, który wczytuje sygnał, argument to ścieżka do .mp3
		~Signal();
    	void saveSignal(int[]);
		void saveFourier(int[]);
		void playSound();
		void volume(double); // zmiana "głośności" (amplitudy dźwięku).
		void iDFT();
		void DFT();
		int size(){ return numElements;}
};

#endif
