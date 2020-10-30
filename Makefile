# ############################################################
# 01/20/2018  6:36pm Michael: formated header/ added variables
# 01/22/2018 12:51am Cesar  : added default target, generate object files
# 				and generate executables
# 01/22/2018  2:39am Michael: added Obj files for FileIO.o/Locomotion.o
# 01/25/2018 20:30pm Bianca : added GUI.c support
# 01/29/2019 12:16am Tun    : add obj files for Legal.o, Alive.o
# 01/29/019  01:22am Bianca : gui support
# #############################################################

# Variables
CC     = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -Wall -std=c99 -c -g
LFLAGS = -ansi -Wall -std=c99

# Libs
GTKINC	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --cflags gtk+-2.0`
GTKLIBS	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --libs gtk+-2.0`
INC	= $(GTKINC)
LIBS	= $(GTKLIBS)

OPTS	= -g

PROJECT	= gui ZOTMATE

test: ./ZotMate

# Object Files
Legal.o: Legal.c Legal.h move.h chessLayout.h
	$(CC) $(CFLAGS) -g Legal.c -o Legal.o

Check.o: Check.h Locomotion.h Alive.h Legal.h chessLayout.h move.h FileIO.h  Check.c
	$(CC) $(CFLAGS) Check.c -o Check.o

chessLayout.o: chessLayout.h chessLayout.c
	$(CC) $(CFLAGS)  -g chessLayout.c -o chessLayout.o

Alive.o: Alive.c Alive.h chessLayout.h
	$(CC) $(CFLAGS)  -g Alive.c -o Alive.o

AI.o: AI.c AI.h chessLayout.h move.h Alive.h Legal.h Locomotion.h Check.h
	$(CC) $(CFLAGS)  -g AI.c -o AI.o

move.o: move.c move.h chessLayout.h
	$(CC) $(CFLAGS) move.c -o move.o

Main.o: Main.c chessLayout.h AI.h move.h Alive.h
	$(CC) $(CFLAGS)  -g Main.c -o Main.o

gui.o: gui.c gui.h
	$(CC) -c  gui.c $(INC) $(OPTS) -o gui.o

gui: gui.o
	$(CC) gui.o $(LIBS) $(OPTS) -o gui

basicChess.o: basicChess.c chessLayout.h move.h
	$(CC) $(CFLAGS)  -g basicChess.c -o basicChess.o

Locomotion.o: Locomotion.h Alive.h move.h FileIO.h chessLayout.h Locomotion.c
	$(CC) $(CFLAGS) Locomotion.c -o Locomotion.o 

FileIO.o: FileIO.h FileIO.c chessLayout.h move.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

Psuedocode.o: Locomotion.h Alive.h AI.h move.h chessLayout.h Check.h Psuedocode.c Legal.h FileIO.h
	$(CC) $(CFLAGS) Psuedocode.c -o Psuedocode.o

all: $(PROJECT)


#################### Generate executables  ####################
chess: chessLayout.o move.o Main.o Locomotion.o Legal.o Alive.o
	$(CC) $(LFLAGS) chessLayout.o move.o Locomotion.o Legal.o Alive.o Main.o -o Chess

BASICCHESS: basicChess.o chessLayout.o move.o Locomotion.o AI.o Alive.o 
	$(CC) $(LFLAGS) basicChess.o chessLayout.o move.o Locomotion.o Alive.o -o basicChess

ZOTMATE: Psuedocode.o Alive.o AI.o move.o chessLayout.o Check.o Locomotion.o Legal.o FileIO.o
	$(CC) $(LFLAGS) Psuedocode.o Alive.o AI.o move.o chessLayout.o Check.o Locomotion.o Legal.o FileIO.o -o ZotMate

clean:
	rm -rf *.o $(PROJECT)
	rm -rf ZotMate
