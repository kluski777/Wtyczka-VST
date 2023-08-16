#ifndef Signal_H
#define Signal_H

class Signal{
        short *signal, *fourier, bits; // sygnał zazwyczaj zapisany w shorcie | bits potrzebny do odtwarzania.
        int encoding, channels;
        long rate;
        size_t totSize, bufsize;    // totSize = ilość bajtów którą zjada signal podzielona przez sizeof(short) daje liczbe elementów, bufsize = ilość elementów jednego bufora.

    public:
        Signal(const char*); // konstruktor wczytuje sygnał
        ~Signal();
        void playSound();   // zagranie sygnału (wygląda na to że działa)
        void fft(bool, size_t size);
};

#endif
