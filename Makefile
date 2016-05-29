CXX=clang++
CXXFLAGS=-g -std=c++11 -Wall -pedantic ${INCLUDE} 

OUTPUT_BIN = ./bin
OUTPUT_OBJ = ./obj
SOURCE_FOLDER = ./src

EXAMPLE01 = exam01
EXAMPLE02 = exam02
CURRENT_EXAMPLE = $(EXAMPLE01)

$(shell mkdir -p $(OUTPUT_BIN))
$(shell mkdir -p $(OUTPUT_OBJ))
$(shell mkdir -p $(OUTPUT_OBJ)/$(SOURCE_FOLDER))
$(shell mkdir -p $(OUTPUT_OBJ)/$(CURRENT_EXAMPLE))

CPP_FILES := $(wildcard *.cpp $(SOURCE_FOLDER)/*.cpp $(CURRENT_EXAMPLE)/*.cpp)
OBJ=$(addprefix obj/, $(CPP_FILES:.cpp=.o))

BIN = ./bin/sample
LIBS = -lSDL2 -lGLEW -framework OpenGL

INCLUDE_FOLDERS = include include/utils
INCLUDE=$(foreach d, $(INCLUDE_FOLDERS), -I$d)

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(OBJ) $(LIBS) $(INCLUDE) -o $(BIN)

obj/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJ) $(BIN)
	