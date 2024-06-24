CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET_MAIN = main
TARGET_TEST = test
MAIN_OBJS = main.o
TEST_OBJS = test.o

all: $(TARGET_MAIN) $(TARGET_TEST)

$(TARGET_MAIN): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET_MAIN) $(MAIN_OBJS) $(LDFLAGS)

$(TARGET_TEST): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TEST) $(TEST_OBJS)

main.o: main.cpp tree.hpp node.hpp complex.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

test.o: test.cpp tree.hpp node.hpp complex.hpp doctest.h
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -f $(TARGET_MAIN) $(TARGET_TEST) $(MAIN_OBJS) $(TEST_OBJS)
