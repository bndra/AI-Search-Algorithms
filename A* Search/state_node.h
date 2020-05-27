#pragma once
#include <cstdlib>
#include <iostream>

class state_node
{
private:
	int* state;
	state_node *parent;//*up, *down, *left, *right;
	int moves_made, priority_level;

public:
	state_node::state_node();
	state_node::state_node(int* s, int m);
	state_node::state_node(int* s, int m, state_node* p);
	int get_priority();
	int* get_state();
	int get_moves_made();
	state_node* get_parent();
	void set_parent(state_node* p);
	void set_priority_level(int h);
	void print();
};