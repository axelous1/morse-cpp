CXX = g++
CXXFLAGS = -Wall -std=c++11

TARGET = morse
OBJS = main.o Morse.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Morse.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Morse.o: Morse.cpp Morse.h
	$(CXX) $(CXXFLAGS) -c Morse.cpp

clean:
	rm -f $(OBJS) $(TARGET)
