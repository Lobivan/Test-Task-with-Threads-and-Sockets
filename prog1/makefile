CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -pthread

SRCDIR = src
BUILDDIR = build

SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC))
TARGET = program1

all: run

dir:
	mkdir -p $(BUILDDIR)

$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ)

$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp dir
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
