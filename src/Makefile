#
# Project: dhcp-stats
# Author:  Michal Ľaš (xlasmi00)
# Date:    03.12.2023
#

CC=g++
CFLAGS=-std=c++17 -Wall -Wextra -Werror -pedantic
LIBS=-lsimlib

ZIP=T5_xlasmi00_xlazik00.zip

BIN=./bin/
HDR_FILES := $(wildcard *.hpp)
SRC_FILES := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,$(BIN)/%.o,$(SRC_FILES))
DEP := $(OBJ:.o=.d)

TOPACK= *.cpp *.hpp Makefile ../doc/simulation_study.pdf ../doc/images

PROGS=main
OBJ=$(BIN)argparser.o $(BIN)main.o $(BIN)GasCar.o $(BIN)WorkDay.o $(BIN)ElectricCar.o $(BIN)AutonomousCar.o $(BIN)Car.o $(BIN)ParcelBatch.o

.PHONY: clean all pack run


all: $(BIN) $(PROGS)


#######################################################################


$(PROGS): $(OBJ)
	$(CC)  -fsanitize=address -o $@ $^ $(LIBS)


$(BIN)%.o: %.cpp %.hpp | $(BIN)
	$(CC) -c $(CFLAGS) -o $@ $<

$(BIN)main.o: main.cpp | $(BIN)
	$(CC) -c $(CFLAGS) -o $@ $<

-include $(DEP)


$(BIN):
	mkdir -p $(BIN)


#######################################################################


run: $(PROGS)
	./main


pack: clean
	zip -r $(ZIP) $(TOPACK)


clean:
	rm -rf $(BIN) $(PROGS) $(wildcard $(DEP))
