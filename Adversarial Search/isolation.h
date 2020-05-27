#pragma once
#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <string>
#include <float.h>
#define size 64

struct state
{
	char board[size];
	bool my_turn;
	int x, o;
};

int translate(std::string coord);
std::string translate(int index);

class game
{
private:
public:
	state s;
	int turns;
	int hist[size];
	int(*ai)(state,int);

	game();
	game(int(*search)(state,int));
	void play();
	void who_first();
	int user_in();
	void move(int moveto);
	void print();
};

state successor(state c, int moveto);
bool legal(state s, int index);
bool sane(state s, int index);
bool gg(state c);
bool check_west(int loc, int dest, state s);
bool check_northwest(int loc, int dest, state s);
bool check_north(int loc, int dest, state s);
bool check_northeast(int loc, int dest, state s);
bool check_east(int loc, int dest, state s);
bool check_southeast(int loc, int dest, state s);
bool check_south(int loc, int dest, state s);
bool check_southwest(int loc, int dest, state s);
