.PHONY: all doxy clean

CXX = g++


CXXFLAGS = -Wall 


TARGET = modAlphaCipher


SOURCES = main.cpp modAlphaCipher.cpp


OBJECTS = $(SOURCES:.cpp=.o)


DEPS = modAlphaCipher.h


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXXFLAGS) -o $(TARGET) 

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
doxy:
	doxygen

clean:
	rm -f $(OBJECTS) $(TARGET)
