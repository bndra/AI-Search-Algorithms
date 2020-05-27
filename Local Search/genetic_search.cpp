#include "genetic_search.h"

genetic_alg::genetic_alg()
{
	iterations = 0;
	solved = false;
}

void genetic_alg::solve(problem p)
{

	iterations = 0;
	randomize();
	pop.sort();
	//print();
	std::list<problem> new_pop;
	for (int i = 0; i < GEN_COUNT; i++)
	{
		for (int j = 0; j < POP_SIZE; j++)
		{
			problem parent1 = fitness_selector();
			problem parent2 = fitness_selector();

			problem* child = parent1.cross(parent2);

			if(decide_to_mutate())
				child->mutate();

			new_pop.push_back(*child);
		}
		set_pop(new_pop);
		new_pop.clear();

		pop.sort();
		//print();
		iterations++;
		if (pop.begin()->get_h() == 0)
		{
			solved = true;
			return;
		}
	}
	solved = false;
}

void genetic_alg::randomize()
{
	pop.clear();
	for (int i = 0; i < POP_SIZE;i++)
	{
		problem *dummy = new problem();
		pop.push_back(*dummy);
		delete dummy;
	}
}
problem genetic_alg::fitness_selector()
{
	int r = rand()%(POP_SIZE/4);
	auto it = pop.begin();
	std::advance(it, r);
	return(*it);
}
bool genetic_alg::decide_to_mutate()
{
	//random, 20% of time return true
	int r = rand() % 100;
	if (r < MUTATION_PERCENT)
		return true;
}
void genetic_alg::set_pop(std::list<problem> new_pop)
{
	pop.clear();
	for (int i = 0; i < POP_SIZE; i++)
	{
		pop.push_back(new_pop.front());
		new_pop.pop_front();
	}
}
void genetic_alg::print_pop()
{
	int count = 1;
	for (auto it = pop.begin(); it != pop.end(); it++)
	{
		std::cout << count << ":\th = " << it->get_h() << "\n\t";
		for (int i = 0; i < N; i++)
			std::cout << it->state_at(i) << " ";
		std::cout << std::endl;
		count++;
	}
	std::cout << "\n";
}
void genetic_alg::print()
{
	pop.begin()->print();
	std::cout << "generations: " << iterations << std::endl;
	std::cout << "of pop size: " << POP_SIZE << std::endl;
}
bool genetic_alg::is_solved()
{
	return solved;
}
int genetic_alg::get_iterations()
{
	return iterations;
}