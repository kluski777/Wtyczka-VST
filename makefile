CXX=g++

CXXFLAGS=-std=c++11 -Wall -g ## do valgrind'a

LIBRARIES=-lao -lmpg123
FFTWLIBRARY=-lfftw3
FFTW_LOCATION=/usr/include

SOURCES=projekt.cpp signal.o fft.o modyfikacje.o
HEADERS=signal.h

TARGET=projekt

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LIBRARIES) -L$(FFTW_LOCATION) $(FFTWLIBRARY)

signal.o: signal.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o signal.o signal.cpp

fft.o: fft.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) fft.cpp -c -o fft.o

modyfikacja.o: modyfikacje.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o modyfikacje.o modyfikacje.cpp

clean:
	rm -f *.o
