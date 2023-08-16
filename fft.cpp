#include <iostream>
#include <fstream>
//#include <complex>
#include <cmath>
//#include <iterator>
//#include <bitset>
#include <mpg123.h>
#include <ao/ao.h>		// chyba nie potrzebne 
// tą bibliotęke przedostatnią chyba trzeba instalować ręcznie (sudo apt install libmpg123-dev lub libmpg123-0) podobnie z tą ostatnią

//const char* path = "/home/stud/Music/ERIKA.mp3"; // można dać jako argument do czegoś w rodzaju loop'a
const char* path = "/home/stud/Music/02 - Ice Cube - Check Yo Self (feat. Das Efx)(Remix).mp3"; 
short reverse(short,short);

class signalClass{
		short *signal, *fourier, bits; // sygnał zazwyczaj zapisany w shorcie | bits potrzebny do odtwarzania.
		int encoding, channels;
		long rate;
		size_t totSize, bufsize;	// totSize = ilość bajtów którą zjada signal podzielona przez sizeof(short) daje liczbe elementów, bufsize = ilość elementów jednego bufora.

	public:
		signalClass(const char*); // konstruktor wczytuje sygnał
		~signalClass();
		void saveToFile(std::string); // zapisanie do pliku w danym formacie (bez sensu, teraz raczej dodać zapisywanie w .mp3 / .wav)
		void printSize();
		void playSound();	// zagranie sygnału (wygląda na to że działa)
		void fft(bool, size_t size = totSize);
};

int main(){
	signalClass erika(path);
	erika.playSound();
	return 0;
}

void signalClass::fft(){
	
}

void signalClass::printSize(){
	std::cout << "The full size of the file file: " << totSize << std::endl; 
}

signalClass::~signalClass(){
	delete [] signal;
}

/////////////////////////////////////////// WCZYTANIE SYGNAŁU Z MP3
signalClass::signalClass(const char* path){
	mpg123_init();	// otwarcie biblioteki
	
	// inicjalizacje zmiennych mpg
	mpg123_handle *handler = mpg123_new(NULL, NULL);
	size_t done;
	bufsize = mpg123_outblock(handler);
	char* buffer = (char*) malloc(bufsize);

	mpg123_open(handler, path); // otwarcie pliku przypisanie wartości do handlera
	mpg123_getformat(handler, &rate, &channels, &encoding); // do odtwarzania 

	bits = mpg123_encsize(encoding) * 8; // musi być 8 dla 16 bitów nie działa	
	totSize = 0; // w bajtach
	
	while(mpg123_read(handler, buffer, bufsize, &done) == MPG123_OK)
		totSize += done; // długość sygnału w bajtach.
	
	mpg123_seek(handler, 0, SEEK_SET); // ustawia handler na 0 elemencie od początku pliku .mp3

	signal = (short*)malloc(totSize);	// totSize to wielokrotność bufsize (tak wychodzi z eriki)
	int elemPerSmp = bufsize/sizeof(short);
	for(int i=0;mpg123_read(handler, buffer, bufsize, &done) == MPG123_OK; i++){
		short* temp = reinterpret_cast<short*> (buffer);	// nie wiem jak to bez tej linijki zrobić, możnaby to poprawić
		for(int j=0; j<elemPerSmp; j++)
			signal[i*elemPerSmp + j] = temp[j];
	}
	std::cout << "Wczytałem próbki dźwięku w formacie PCM." << std::endl;
	
	delete [] buffer;
	mpg123_close(handler);
	mpg123_delete(handler);
	mpg123_exit();
}

////////////////////////////// ODTWARZANIE SYGNAŁU
void signalClass::playSound(){
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
	
	for(int j=0; j<totSize/bufsize-1; j++){
		char* temp = (char*) malloc(bufsize);
		temp = reinterpret_cast<char*> (&signal[j*bufsize/sizeof(short)]); // tylko dla char* działa ao_play
		ao_play(device, temp, bufsize);
	}

	ao_close(device);
	ao_shutdown();
}

/////////////////////////////////////////FOURIER
void signalClass::fft(bool invert, size_t size){
	int lg_n = 0;
	while((1 << lg_n) < size)
		lg_n++; // najwyższa potęga 2 mniejsza od size

	for(int i=0; i<n; i++){
		if( i < reverse(i, lg_n))
			swap( fourier[], fourier[reverse(i, lg_n)]);
	}
}

template<typename T> void swap(T* a, T* b){
	T* temp = a;
	a = b;
	b = temp;
}

short reverse(short num, short lg_n){
	int res = 0;
	for(int i=0; i<lg_n; i++){
		if( num & (1 << i))
			res |= 1 << (lg_n - 1 - i);
	}
	return res;
}
