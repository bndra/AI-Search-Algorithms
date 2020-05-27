#include "state_node.h"

state_node::state_node()
{
	state = new int[9];
	moves_made = 0;
	parent = NULL;
};

state_node::state_node(int* s, int m)
{
	state = new int[9];
	for (int i = 0; i < 9; i++)
		state[i] = s[i];
	moves_made = m;
	parent = NULL;
};

state_node::state_node(int* s, int m, state_node* p)
{
	state = new int[9];
	for (int i = 0; i < 9; i++)
		state[i] = s[i];
	moves_made = m;
	parent = p;
};


int state_node::get_priority()
{
	return priority_level;
}

int* state_node::get_state()
{
	int* dummy = new int[9];
	for (int i = 0; i < 9; i++)
		dummy[i] = state[i];
	return dummy;
}

int state_node::get_moves_made()
{
	return moves_made;
}

state_node* state_node::get_parent()
{
	return parent;
}

void state_node::set_priority_level(int h)
{
	priority_level = h;
}

void state_node::print()
{
	for (int i = 0; i < 9; i++)
		std::cout << state[i] << " ";
	std::cout << std::endl
		<< "moves: " << moves_made
		<< "\nprio: " << priority_level
		<< std::endl;

}
