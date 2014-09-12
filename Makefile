CC=clang++ #Compiler
CFLAGS= -c -std=c++11 -Ofast #Compiler Flags
LDFLAGS=-lallegro -lallegro_primitives -lallegro_ttf -lallegro_font #Linker options
SOURCES=main.cpp globals.cpp Ball.cpp  #cpp files
OBJECTS=$(SOURCES:.cpp=.o)  #Object files
EXECUTEABLE=FunWithBalls #Output name

all: $(SOURCES) $(EXECUTEABLE)
	
$(EXECUTEABLE): $(OBJECTS) 
	$(CC)   $(OBJECTS) -o $(EXECUTEABLE) $(LDFLAGS)

.cpp.o:
	$(CC)  $(CFLAGS)   $< -o $@


clean:  ; rm *.o $(EXECUTEABLE)
