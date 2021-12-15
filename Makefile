INPUT_FILENAME=main.cpp fuzzylib/fuzzylib.cpp
OUTPUT_FILENAME=fuzzycheck
FL_MAIN=fuzzylite-6.0
FL_LANG=c++11

# --------------

INPUT=$(INPUT_FILENAME)
OUTPUT=-o $(OUTPUT_FILENAME)
INCLUDE_DIRS=-I./$(FL_MAIN)/fuzzylite -I./fuzzylib
LINKING_DIRS=-L./$(FL_MAIN)/release/bin
LIB_NAMES=-lfuzzylite-static
ADDLS_FLAGS=-Wno-conversion-null --std=$(FL_LANG)

all:
	g++ $(INPUT) $(OUTPUT) $(INCLUDE_DIRS) $(LINKING_DIRS) $(LIB_NAMES) $(ADDLS_FLAGS)
