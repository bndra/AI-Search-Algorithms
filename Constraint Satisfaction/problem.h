#pragma once
#define N 25
#include <cstdlib>
#include <list>
#include <time.h>
#include <iostream>

class problem
{
private:
	int state[N];
	double h; //cost function result, measure of attacking queens
	static int cost;
public:
	problem();
	problem(int* s);
	double get_h();
	int state_at(int i);
	void set_state(int* s);
	problem* cross(problem mate);
	problem* neighbor();
	void mutate();
	void appraise();
	bool operator <(const problem& p);
	void print();
	static int get_cost();
	static void reset_cost();
	int is_conf(int i);
	int min_conf(int i);
	void set_state_at(int i, int v);
};