#include <iostream>
//#include <cmath>
//#include <mpg123.h>
//#include <ao/ao.h>		// chyba nie potrzebne 
#include "signal.h"

//const char* path = "/home/stud/Music/ERIKA.mp3"; // można dać jako argument do czegoś w rodzaju loop'a
const char* path = "/home/stud/Music/02 - Ice Cube - Check Yo Self (feat. Das Efx)(Remix).mp3"; 

int main(){
	Signal erika(path);
	erika.playSound();
	return 0;
}

