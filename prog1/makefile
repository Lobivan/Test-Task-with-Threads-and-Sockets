CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -pthread

SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = prog1

all: $(TARGET) run

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm $(OBJ) $(TARGET)
