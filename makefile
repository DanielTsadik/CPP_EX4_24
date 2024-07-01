## Tsadik88@gmail.com
CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: main test

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o $(LDFLAGS)

test: test.o
	$(CXX) $(CXXFLAGS) -o test test.o $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -f main test *.o
