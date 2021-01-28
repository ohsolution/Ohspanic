all: OhsPanic

OhsPanic: OhsPanic.cpp
	g++ OhsPanic.cpp -lncurses -o OhsPanic
