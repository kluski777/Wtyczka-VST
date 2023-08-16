CXX=g++

CXXFLAGS=-std=c++11 -Wall

LIBRARIES=-lao -lmpg123

SOURCES=signal.cpp projekt.cpp fft.cpp

TARGET=projekt

all:$(TARGET)

$(TARGET):$(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LIBRARIES)

run: $(TARGET)			# Dopisać run po make albo make potem ./projekt
	./$(TARGET)

clean:
	rm -f $(TARGET)
