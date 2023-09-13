#include "signal.h"
#include <string>
#include <cstdlib>
#include <limits>

//std::string path = "/home/stud/Music/ERIKA.mp3"; // można dać jako argument do czegoś w rodzaju loop'a
//std::string path = "/home/stud/Music/02 - Ice Cube - Check Yo Self (feat. Das Efx)(Remix).mp3"; 
//std::string path = "/home/stud/Music/Cypress Hill - Lowrider (Official Video).mp3";
//std::string path = "/home/stud/Music/Fear of the Dark (2015 Remaster).wav";
std::string path = "/home/stud/Music/Rebel.wav";

int main(){
	std::cout << "Żeby przerwać program naciśnij # (o ile nie gra muzyki)." << std::endl;
	

	bool out = true;
	std::string input(path);	
	int elems[2] = {0,0};

	do{ // jak nie przerywał tak nie przerywa nie.
		bool goToMenu = true;
	
		std::cout << "Podaj ścieżkę do pliku, który ma być przeczytany." << std::endl;
				
		if(!std::getline(std::cin, input))
			throw("Wrong input.");
		else if(input == "#")
			break;

		Signal utwor(input.c_str()); // konwersja std::string na char*
		
		int sajz = utwor.size();

		std::cout << "Wczytana próbka ma " << sajz << " elementów.\n";		

		while(goToMenu){

			std::cout << "\nCo chcesz zrobić:\nNaciśnij 1 żeby zapisać sygnał w pliku.\n2 żeby zapisać widmo fourierowskie w pliku.\n3 żeby odtworzyć sygnał.\n4 żeby zmienić amplitudy (może się wiązać ze stratą jakości).\n5 żeby wczytac następny plik.\n# żeby zakończyć działanie." << std::endl;

			if(!std::getline(std::cin, input))
				throw("Wrong input.");
			else if(input == "#")
				break;

			switch(input[0]){
				case '1':
					std::cout << "Od którego elementu zapisać sygnał?" << std::endl;
					std::cin >> elems[0];
			 		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Do którego elementu zapisać sygnał?" << std::endl;
					std::cin >> elems[1];
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					
					if( elems[0] < elems[1] && elems[0] >= 0 && elems[1] >= 0 && elems[1] < sajz && elems[0] < sajz )
						utwor.saveSignal(elems);
					else
						std::cout << "Coś poszło nie tak z zapisywaniem sygnału. Sprawdź czy dobrze wpisałeś liczby." << std::endl;
					break;
				case '2':
					std::cout << "Trwa liczenie transformaty..." << std::endl;
					utwor.DFT();
					std::cout<<"Od którego elementu zapisać widmo fouriera?"<<std::endl;
					std::cin >> elems[0]; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Do którego elementu zapisać widmo?" << std::endl;
					std::cin >> elems[1]; 
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // czyszczenie bufora
					
					if( elems[0] < elems[1] && elems[0] >= 0 && elems[1] >= 0 && elems[1] < sajz && elems[0] < sajz )
						utwor.saveFourier(elems);
					else
						std::cout << "Coś poszło nie tak z zapisywaniem sygnału. Sprawdź czy dobrze wpisałeś liczby." << std::endl;
					break;
				case '3':
					utwor.playSound();
					break;
				case '4':{
					std::cout << "O ile chcesz wymnożyć amplitudy." << std::endl;
					input = "";
					std::cin >> input;
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					utwor.volume(std::stod(input));
					break;
				}
				case '5':
					goToMenu = false;
					break;
				case '#':
					std::cout << "Nacisnąłeś # gratulacje." << std::endl;
					out = false;
					goToMenu = false;
					break;	
				default:
					std::cout << "Spróbuj jeszcze raz." << std::endl;
					break;
			}
		}
	}while( out );
	return 0;
}

