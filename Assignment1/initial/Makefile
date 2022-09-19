#!/bin/sh 
#!/usr/bin/env

#This is my make file
.ONESHELL:
SHELL   := /bin/bash

CC		= g++
CFLAGS  = -Wall -Werror -std=c++11

_NAME = main.cpp StackFrame.cpp #Put all your .cpp file here, 
EXE = main #Your exe file's name

SDIR = src
CODE = $(patsubst %,$(SDIR)/%,$(_NAME))

ODIR = obj
OBJ = $(patsubst %.cpp,%.o,$(_NAME))
#OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


#Option for make file:
#	- make: build project like normal
#	- make test: test project
build: check
	@cd $(ODIR)
	$(CC) -c $(CODE) $(CFLAGS) &&
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS) &&
	{
		echo "======================================================================"
		echo "Status: Build sucessfully!"
		cp main ../
	} || {
		echo "======================================================================"
		echo "Status: Failed!"
	}
	echo "======================================================================"
	cd ..
	
check:
	@if [ ! -d "$(ODIR)/" ]; then
		mkdir $(ODIR)
	fi

	if [ ! -d "$(ODIR)/$(SDIR)/" ]; then
		mkdir $(ODIR)/$(SDIR) 
		mv *.h *.cpp $(ODIR)/$(SDIR) 
	fi

test: clean_exec build
	@if [ -f "main" ]; then
		python -m unittest run_testcase
	fi

clean:
	@rm -rf $(ODIR)/*.o $(ODIR)/main 
	rm -rf main
	echo "Clean done!"

clean_exec:
	@rm -rf main

run: build
	./main testcase/test126.txt