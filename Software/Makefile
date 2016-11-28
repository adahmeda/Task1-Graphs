
#########################################################

#########################################################
# compiler stuff 
#########################################################
CC= gcc
CFLAGS= -Wall -Wvla -Werror -g
#COPTFLAGS= -O -DNDEBUG

CXX= g++
CXXFLAGS= $(CFLAGS) 

CEXELINKFLAGS=
##########################################################

#######################
# executables name
#######################
EXE1= Graph


#######################

##########################################################
# sources files
##########################################################
SRCSEXE1NOMAIN= Graph.cpp
SRCSEXE1MAIN= $(EXE1).cpp
SRCSEXE1= $(SRCSEXE1NOMAIN) $(SRCSEXE1MAIN)
HEADERMEAN=  Graph.hpp


##########################################################

#########################################################
# actions
#########################################################
all: $(EXE1)

$(EXE1): $(subst .c,.o,$(SRCSEXE1))
	$(CC) $(CFLAGS)  $^ -o $@




clean:
	rm *.o $(EXE1) -f

depend: $(SRCSEXE1)
	makedepend -Y -- $(CXXFLAGS) -- $^



# DO NOT DELETE THIS LINE -- make depend depends on it.
Graph.o: Graph.hpp
