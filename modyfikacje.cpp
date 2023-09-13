#include "signal.h"

// podgłośnienie void volume(double)
// jakiś filtr? 
// opóźnienie?

void Signal::volume(double multiply){
	const long SHORT_MIN = -32768;
	const long SHORT_MAX = 32767;	

	for( int i=0; i<numElements; i++){
		long temp = signal[i]*multiply;
		if( temp > SHORT_MAX )
			signal[i] = SHORT_MAX;
		else if(temp < SHORT_MIN)
			signal[i] = SHORT_MIN;
		else
			signal[i] = temp;
	}
}

//void filterFIR(){
	
//}
