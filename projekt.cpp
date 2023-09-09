#include "signal.h"

//const char* path = "/home/stud/Music/ERIKA.mp3"; // można dać jako argument do czegoś w rodzaju loop'a
//const char* path = "/home/stud/Music/02 - Ice Cube - Check Yo Self (feat. Das Efx)(Remix).mp3"; 
const char* path = "/home/stud/Music/Cypress Hill - Lowrider (Official Video).mp3";

int main(){
	
	Signal erika(path);
//	erika.fft(); // mniej więcej tak to będzie w przyszłości działać

//	erika.ifft();
	std::cout << "Sygnał oryginalny." << std::endl;

	erika.showSignal();

	std::cout << "Po analizie Fouriera. Fourier:" << std::endl;
	
	erika.DFT();

	erika.showFourier();	

	std::cout << "Po IDFT. Znowu signal:" << std::endl;

	erika.iDFT();

	erika.showSignal();

	erika.playSound();
	
	return 0;
}

