#include "eight_puzzle.h"

eight_puzzle::eight_puzzle()
{
	initial_state = new state_node();
	algorithm = 0;
}

eight_puzzle::~eight_puzzle()
{
	delete initial_state;
}

void eight_puzzle::set_alg(bool a)
{
	algorithm = a;
}

void eight_puzzle::solve(int(*h)(int*))
{
	if (algorithm == 0)
		tree_search(h);
	else
		graph_search(h);
}

void eight_puzzle::tree_search(int(*h)(int*))
{
	if (solvable())
	{
		priority_states.clear();
		priority_states.push_front(initial_state); 
		explored.clear();
		while (!solution.empty())
			solution.pop();
		solution_state = NULL;
		tree_size = 1;
		bool done = false;

		std::clock_t start;
		double duration;
		start = std::clock();

		while (!done)
		{
			state_node *current = (priority_states.front());
			priority_states.pop_front();
			if (is_goal(current->get_state()))
			{
				done = true;
				solution_state = current;
				solution_depth = current->get_moves_made();
				std::cout << "nodes: " << tree_size
					<< "\ndepth: " << solution_depth
					<< std::endl;
			}
			else
			{
				int blank = blank_index(current->get_state());
				insert_best_first(generate_up(blank, current), h);
				insert_best_first(generate_down(blank, current), h);
				insert_best_first(generate_left(blank, current), h);
				insert_best_first(generate_right(blank, current), h);
			}
			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			if (duration > 30)
			{
				std::cout << "timeout. tree search likely cycling\nlast state checked:\n";
				current->print();
				return;
			}
		}

		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		std::cout << "Duration: " << duration << "s" << '\n';
	}
}

void eight_puzzle::graph_search(int(*h)(int*))
{
	if (solvable())
	{
		priority_states.clear();
		priority_states.push_front(initial_state);
		explored.clear();
		while (!solution.empty())
			solution.pop();
		solution_state = NULL;
		tree_size = 1;
		bool done = false;

		std::clock_t start;
		double duration;
		start = std::clock();

		while (!done)
		{
			state_node *current = priority_states.front();
			priority_states.pop_front();
			explored.push_back(current->get_state());
			if (is_goal(current->get_state()))
			{
				done = true;
				solution_state = current;
				solution_depth = current->get_moves_made();
				std::cout << "nodes: " << tree_size
					<< "\ndepth: " << solution_depth
					<< std::endl;

			}
			else
			{
				int blank = blank_index(current->get_state());
				insert_best_first(generate_up(blank, current), h);
				insert_best_first(generate_down(blank, current), h);
				insert_best_first(generate_left(blank, current), h);
				insert_best_first(generate_right(blank, current), h);
			}
		}

		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		std::cout << "Duration: " << duration << "s" << '\n';
	}
}

int eight_puzzle::blank_index(int *s)
{
	int blank;
	for (int i = 0; i < 9; i++)
	{
		if (s[i] == 0)
		{
			blank = i;
			return blank;
		}
	}
	return -1;
}

int eight_puzzle::blank_index(std::vector<int> s)
{
	int blank;
	for (int i = 0; i < 9; i++)
	{
		if (s[i] == 0)
		{
			blank = i;
			return blank;
		}
	}
	return -1;
}

bool eight_puzzle::is_goal(int *s)
{
	for (int i = 0; i < 9; i++)
	{
		if (s[i] != i)
			return false;
	}
	return true;
}

void eight_puzzle::insert_best_first(state_node *s, int(*h)(int*))
{
	if (s!=NULL)
	{
		tree_size += 1;
		int priority = s->get_moves_made() + h(s->get_state());
		s->set_priority_level(priority);

		if (priority_states.empty())
			priority_states.push_front(s);
		else
		{
			for (auto i = priority_states.begin(); i != priority_states.end(); ++i)
			{
				if ((*i)->get_priority() > s->get_priority())
				{
					priority_states.insert(i, s);
					return;
				}
			}
			priority_states.push_back(s);
		}
	}
}

void swap(int &a, int &b)
{
	int dummy = a;
	a = b;
	b = dummy;
}

state_node* eight_puzzle::generate_up(int empty_index, state_node *parent)
{
	if (empty_index - 3 < 0 || empty_index < 0)
		return NULL;
	else
	{
		int array[9];
		for (int i = 0; i < 9; i++)
			array[i] = parent->get_state()[i];
		swap(array[empty_index], array[empty_index - 3]);
		if (already_visited(array))
			return NULL;

		state_node* dummy = new state_node(array, parent->get_moves_made() + 1, parent);
		catalogue.push(dummy);
		return dummy;
	}
}

state_node* eight_puzzle::generate_down(int empty_index, state_node *parent)
{
	if (empty_index + 3 > 8 || empty_index < 0)
		return NULL;
	else
	{
		int array[9];
		for (int i = 0; i < 9; i++)
			array[i] = parent->get_state()[i];
		swap(array[empty_index], array[empty_index + 3]);
		if (already_visited(array))
			return NULL;

		state_node* dummy = new state_node(array, parent->get_moves_made() + 1, parent);
		catalogue.push(dummy);
		return dummy;
	}
}

state_node* eight_puzzle::generate_left(int empty_index, state_node *parent)
{
	if (empty_index % 3 == 0 || empty_index <= 0)
		return NULL;
	else
	{
		int array[9];
		for (int i = 0; i < 9; i++)
			array[i] = parent->get_state()[i];
		swap(array[empty_index], array[empty_index - 1]);
		if (already_visited(array))
			return NULL;

		state_node* dummy = new state_node(array, parent->get_moves_made() + 1, parent);
		catalogue.push(dummy);
		return dummy;
	}
}

state_node* eight_puzzle::generate_right(int empty_index, state_node *parent)
{
	if (empty_index % 3 == 2 || empty_index < 0)
		return NULL;
	else
	{
		int array[9];
		for (int i = 0; i < 9; i++)
			array[i] = parent->get_state()[i];
		swap(array[empty_index], array[empty_index + 1]);
		if (already_visited(array))
			return NULL;

		state_node* dummy = new state_node(array, parent->get_moves_made() + 1, parent);
		catalogue.push(dummy);
		return dummy;
	}
}

void eight_puzzle::solution_path()
{
	if (solution_state != NULL)
	{
		state_node * i = solution_state;
		while (!solution.empty())
			solution.pop();
		int count = 0;
		while (i != NULL)
		{
			solution.push(i);
			i = (*i).get_parent();
			count++;
		}
		std::cout << "Solution:\n";
		int step = 0;
		while (!solution.empty())
		{
			i = solution.top();
			std::cout << step << ")\t" << (*i).get_state()[0] << " " << (*i).get_state()[1] << " " << (*i).get_state()[2] << ", "
				<< (*i).get_state()[3] << " " << (*i).get_state()[4] << " " << (*i).get_state()[5] << ", "
				<< (*i).get_state()[6] << " " << (*i).get_state()[7] << " " << (*i).get_state()[8] 
				<< std::endl;
			solution.pop();
			step++;
		}
	}
}

bool eight_puzzle::solvable()
{
	int inversion_count = 0;
	for (int i = 0; i < 8; i++) //i will be compared against the rest of the puzzle: j
	{
		int tile_i = initial_state->get_state()[i];
		if (tile_i > 0) //ignore the blank tile 0
		{
			for (int j = i + 1; j < 9; j++) //j iterates through the rest of the puzzle starting from i + 1
			{
				int tile_j = initial_state->get_state()[j];
				if (tile_j < tile_i  && tile_j > 0) // if j<i, we have an inversion. ignore the blank tile 0.
					inversion_count += 1;
			}
		}
	}
	if (inversion_count % 2 == 0)
		return true;
	else
		return false;
}

bool eight_puzzle::solvable(int* state)//checks a given state array instead of initial_state
{
	int inversion_count = 0;
	for (int i = 0; i < 8; i++) //i will be compared against the rest of the puzzle: j
	{
		int tile_i = state[i];
		if (tile_i > 0) //ignore the blank tile 0
		{
			for (int j = i + 1; j < 9; j++) //j iterates through the rest of the puzzle starting from i + 1
			{
				int tile_j = state[j];
				if (tile_j < tile_i  && tile_j > 0) // if j<i, we have an inversion. ignore the blank tile 0.
					inversion_count += 1;
			}
		}
	}
	if (inversion_count % 2 == 0)
		return true;
	else
		return false;
}

void eight_puzzle::random_state()
{
	srand(time(NULL));
	while (!catalogue.empty())
	{
		delete catalogue.top();
		catalogue.pop();
	}
	int tiles[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	for (int i = 0; i < 20; i++)
	{
		for (int i = 8; i > 0; i--)
		{
			int j = rand() % i;
			int temp = tiles[i];
			tiles[i] = tiles[j];
			tiles[j] = temp;
		}
		if (solvable(tiles))
		{
			initial_state = new state_node(tiles, 0);
			std::cout << "istate solvable" << std::endl;
			for (int i = 0; i < 9; ++i)
				std::cout << initial_state->get_state()[i] << " ";
			std::cout << std::endl;
			return;
		}
	}
	std::cout << "No solvable state in 20 tries." << std::endl;
}

void eight_puzzle::random_state(int depth)
{
	srand(time(NULL));
	while (!catalogue.empty())
	{
		delete catalogue.top();
		catalogue.pop();
	}
	std::vector<int> *goal = new std::vector<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	std::vector<std::vector<int>> explored;
	explored.push_back(*goal);
	std::vector<int> direction;
	for (int i = 0; i < depth; ++i)
	{
		int empty = blank_index(*goal);
		direction.clear();
		if (empty - 3 > 0)
			direction.push_back(empty - 3);
		if (empty + 3 < 9 && empty >= 0)
			direction.push_back(empty + 3);
		if ((empty - 1) % 3 != 2 && empty > 0)
			direction.push_back(empty - 1);
		if ((empty + 1) % 3 != 0 && empty >= 0)
			direction.push_back(empty + 1);

		bool repeated_state = true;
		while(repeated_state)
		{
			int move = rand() % direction.size();
			swap((*goal)[empty], (*goal)[direction[move]]);
			for (auto it = explored.begin(); it != explored.end();++it)
			{
				bool same = true;
				for (int c = 0; c < 9; ++c)
				{
					if ((*it)[c] != (*goal)[c])
					{
						same = false;
					}
				}
				if (same)
				{
					repeated_state = true;
					break;
				}
				else
				{
					repeated_state = false;
				}
			}
			if (repeated_state)
				swap((*goal)[empty], (*goal)[direction[move]]);
			else
				explored.push_back(*goal);
		}
	}
	int d[9];
	for (int i = 0; i < 9; i++)
		d[i] = (*goal)[i];
	initial_state = new state_node(d, 0);

	int count=0;
	for (auto i = explored.begin(); i != explored.end(); ++i)
	{
		std::cout << "Step " << count << ":\n"
			<< (*i)[0] << " " << (*i)[1] << " " << (*i)[2] << "\n"
			<< (*i)[3] << " " << (*i)[4] << " " << (*i)[5] << "\n"
			<< (*i)[6] << " " << (*i)[7] << " " << (*i)[8] << "\n"
			<< std::endl;
		count++;
	}
	for (int i = 0; i < 9; ++i)
		std::cout << initial_state->get_state()[i] << " ";
	std::cout << std::endl;
}

void eight_puzzle::set_initial(int* i)
{
	while (!catalogue.empty())
	{
		delete catalogue.top();
		catalogue.pop();
	}
	initial_state = new state_node(i, 0);
}

bool eight_puzzle::already_visited(int *s)
{
	bool exists = true;
	bool same = true;
	for (auto i = explored.begin(); i != explored.end(); ++i)
	{
		same = true;
		for (int j = 0; j < 9; j++)
		{
			if (s[j] != (*i)[j])
				same = false;
		}
		if (same)
			return true;
	}
	return false;
}
