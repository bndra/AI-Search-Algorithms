#pragma once
#include "problem.h"
#include <list>
#include <iterator>
#include <cstdlib>
#include <iostream>
#include <ctime>
#define GEN_COUNT 10000
#define POP_SIZE 100
#define MUTATION_PERCENT 20

class genetic_alg
{
private:
	std::list<problem> pop;
	int iterations;
	bool solved;
public:
	genetic_alg();
	void solve(problem p);
	void randomize();
	problem fitness_selector();
	bool decide_to_mutate();
	void set_pop(std::list<problem> new_pop);
	void print_pop();
	void print();
	bool is_solved();
	int get_iterations();
};