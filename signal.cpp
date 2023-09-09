#include <mpg123.h>
#include <ao/ao.h>
#include "signal.h"

/////////////////////////////////////////// WCZYTANIE SYGNAŁU Z MP3
Signal::Signal(const char* path){
    mpg123_init();  // otwarcie biblioteki
	
    // inicjalizacje zmiennych mpg
    mpg123_handle *handler = mpg123_new(NULL, NULL);
    size_t done;
    bufsize = mpg123_outblock(handler);
    char* buffer = (char*) malloc(bufsize);

    mpg123_open(handler, path); // otwarcie pliku przypisanie wartości do handlera
    mpg123_getformat(handler, &rate, &channels, &encoding); // do odtwarzania

    bits = mpg123_encsize(encoding) * 8; // musi być 8 dla 16 bitów nie działa
    size_t totSize = 0; // w bajtach

    while(mpg123_read(handler, buffer, bufsize, &done) == MPG123_OK){
    	totSize += done; // długość sygnału w bajtach.
	}

	mpg123_seek(handler, 0, SEEK_SET); // ustawia handler na 0 elemencie od początku pliku .mp3
	numElements = totSize/sizeof(short);
    signal = new short[numElements];       // totSize to wielokrotność bufsize (tak wychodzi z eriki)
    
	int elemPerSmp = bufsize/sizeof(short);
    for(int i=0;mpg123_read(handler, buffer, bufsize, &done) == MPG123_OK; i++){
        short* temp = reinterpret_cast<short*> (buffer);        // nie wiem jak to bez tej linijki zrobić, możnaby to poprawić
        for(int j=0; j<elemPerSmp; j++)
    		signal[i*elemPerSmp + j] = temp[j];
    }
    std::cout << "Wczytałem próbki dźwięku w formacie PCM." << std::endl;
	fourier = new Complex[numElements];

    free(buffer);
    mpg123_close(handler);
    mpg123_delete(handler);
    mpg123_exit();
}

void Signal::showSignal(){
	std::cout << "liczba elementów zmiennej signal = " << numElements << ". Ale wyświetlam tylko 2000 żeby nie zajebać ekrau." << std::endl;
	for(int i=1000000; i<1002000; i++){
			std::cout << "Element: " << i+1 <<  ". " << signal[i] << std::endl;
	}
}

void Signal::showFourier(){
	std::cout << "liczba elementów zmiennej fourier = " << numElements << ". Ale wyświetlam tylko 2000 żeby nie zajebać ekranu." << std::endl;
	for(int i=0; i<numElements; i++){
		if( i < 2000 )
			std::cout << "m = " << i+1 <<  ". " << fourier[i].real() << " + j" << fourier[i].imag() << std::endl;
	}
}


////////////////////////////// ODTWARZANIE SYGNAŁU
void Signal::playSound(){
        ao_initialize();
        int driver = ao_default_driver_id();
        ao_sample_format format;

        format.bits = bits;
        format.rate = rate;
        format.channels = channels;
        format.byte_format = AO_FMT_NATIVE;
        format.matrix = 0;

        ao_device* device = ao_open_live(driver, &format, NULL);
        std::cout << "Leci piosenka." << std::endl;

        for(int j=0; j<int(numElements*sizeof(short)/bufsize); j++){								// jeszcze dodać stop, start
                char* temp = (char*) malloc(bufsize);
                temp = reinterpret_cast<char*> (&signal[j*bufsize/sizeof(short)]); 	// tylko dla char* działa ao_play
                ao_play(device, temp, bufsize);
		}

        ao_close(device);
        ao_shutdown();
}

Signal::~Signal(){
	delete [] signal;
	delete [] fourier;
}
