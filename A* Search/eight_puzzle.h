#pragma once
#include "state_node.h"
#include<vector>
#include <list>
#include <stack>
#include <time.h>
#include <iostream>
#include <ctime>

class eight_puzzle
{
private:
	state_node* initial_state, *solution_state;
	std::list<state_node*> priority_states;
	bool algorithm; //flag for which algorithm to use
	std::vector<int*> explored; //explored set for graph search
	std::stack<state_node*> solution, catalogue; //we will trace the path to our solution recursively and store it here
	int tree_size, solution_depth;

public:
	eight_puzzle::eight_puzzle();
	eight_puzzle::~eight_puzzle();
	void set_alg(bool a); //0: tree search, 1: graph search
	void solve(int (*h)(int*)); //takes into account our option flags and solves the puzzle
	void tree_search(int(*h)(int*));
	void graph_search(int(*h)(int*));
	int blank_index(int *s); //finds the index of the empty tile, 0
	int blank_index(std::vector<int> s);
	bool is_goal(int *s);
	void insert_best_first(state_node *s, int(*h)(int*));
	state_node* generate_up(int empty_index, state_node *parent);
	state_node* generate_down(int empty_index, state_node *parent);
	state_node* generate_left(int empty_index, state_node *parent);
	state_node* generate_right(int empty_index, state_node *parent);
	void solution_path(); 
	bool solvable(); //counts number of inversions and returns true if even
	bool solvable(int* state);
	void random_state();
	void random_state(int depth);
	void set_initial(int* i);
	bool already_visited(int *s);
};