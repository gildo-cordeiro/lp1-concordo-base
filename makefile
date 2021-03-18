#	$@	Nome da regra.
#	$<	Nome da primeira dependência
#	$^	Lista de dependências
#	$?	Lista de dependências mais recentes que a regra.
#	$*	Nome do arquivo sem sufixo

FILE=main

COMPILER=g++
COMPILATION_FLAGS=-Wall -Wextra -pedantic #-g -DDEBUG
LINKER_FLAGS=

MAINFILE=concordo
SOURCE_EXT=.cpp
HEADER_EXT=.hpp

SRCFOLDER=src
INCFOLDER=include
OBJFOLDER=bin

SRCPATH=./$(SRCFOLDER)/
INCPATH=./$(INCFOLDER)/
OBJPATH=./$(OBJFOLDER)/
FILE-SOURCE=$(wildcard $(SRCPATH)*$(SOURCE_EXT))
HEADERS=$(wildcard $(INCPATH)*$(HEADER_EXT))
OBJECTS=$(subst $(SOURCE_EXT),.o,$(subst $(SRCPATH),$(OBJPATH),$(FILE-SOURCE)))

#DEVELOPEMENT
all: $(OBJFOLDER) $(FILE)
	@ echo Finished all

$(FILE): $(OBJECTS)
	@ echo  Linking executable $(FILE)
	@ $(COMPILER) $^ $(COMPILATION_FLAGS) $(LINKER_FLAGS) -o $(FILE) $(foreach I,$(INCPATH),$(shell echo -I$(I)))

$(OBJPATH)%.o: $(SRCPATH)%$(SOURCE_EXT) $(HEADERS)
	@ echo  Building $(COMPILER) object $@
	@ $(COMPILER) $< -c $(COMPILATION_FLAGS) -o $@ $(foreach I,$(INCPATH),$(shell echo -I$(I)))

$(OBJPATH)$(MAINFILE).o: $(SRCPATH)$(MAINFILE)$(SOURCE_EXT) $(HEADERS)
	@ echo  Building $(COMPILER) object $@
	@ $(COMPILER) $< -c $(COMPILATION_FLAGS) -o $@ $(foreach I,$(INCPATH),$(shell echo -I$(I)))

$(OBJFOLDER):
	@ mkdir $(OBJFOLDER)

clean: $(OBJFOLDER)
	@ del /f /s /q bin\*.o $(FILE) >nul

.PHONY: all clean
