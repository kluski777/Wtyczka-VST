#ifndef Signal_H
#define Signal_H

#include <iostream>
#include <complex>

using Complex = std::complex<float>;

class Signal{
	public:
	short *signal, bits; // sygnał zazwyczaj zapisany w shorcie | bits potrzebny do odtwarzania.
	Complex* fourier; // po analizie fouriera
	int encoding, channels, numElements; // numElements - liczba elementów w tablicy. numElements*sizeof(short) daje liczbe bajtów obv
	long rate;
	size_t bufsize;    // bufsize = ilość bajtów jednego w jednym buforze.

	Signal(const char*); // konstruktor wczytuje sygnał
    ~Signal();
    void showSignal();
	void playSound();   // zagranie sygnału (wygląda na to że działa)
	void DFT();
	void iDFT();
	void showFourier();
};

#endif
