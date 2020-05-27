#include "problem.h"

problem::problem()
{
	for (int i = 0; i < N; i++)
	{
		state[i] = i;
	}

	appraise();
}

problem::problem(int* s)
{
	set_state(s);
}

double problem::get_h()
{
	return h;
}

int problem::state_at(int i)
{
	return state[i];
}

void problem::set_state(int* s)
{
	for (int i = 0; i < N; i++)
	{
		state[i] = s[i];
	}
	appraise();
}

problem* problem::cross(problem mate)
{
	int cutoff = rand() % (N - 1);
	cutoff++;

	int cstate[N];
	for (int i = 0; i < cutoff; i++)
		cstate[i] = state[i];
	for (int i = cutoff; i < N; i++)
		cstate[i] = mate.state_at(i);

	problem* child = new problem(cstate);
	return child;
}

problem* problem::neighbor()
{
	cost++;
	int x = 0, y = 0;
	while (x == y)
	{
		x = rand() % N;
		y = rand() % N;
	}
	int dummy[N];
	for (int i = 0; i < N; i++)
	{
		dummy[i] = state[i];
	}
	dummy[x] = state[y];
	dummy[y] = state[x];
	return(new problem(dummy));
}

void problem::mutate()
{
	int x = rand() % N;
	state[x] = rand() % N;
	appraise();
}

void problem::appraise()
{
	double attacking_pairs = 0;
	for (int i = 0; i < N - 1; i++)
	{
		bool up = false, side = false, down = false;
		for (int j = i + 1; j < N; j++)
		{
			if (state[j] == state[i] + (j - i))
				up = true;
			else if (state[j] == state[i] - (j - i))
				down = true;
			else if (state[j] == state[i])
				side = true;
		}
		if (up)
			attacking_pairs++;
		if (side)
			attacking_pairs++;
		if (down)
			attacking_pairs++;
	}

	double max_pairs = (N - 1) * 2;

	h = attacking_pairs / max_pairs;
}

bool problem::operator <(const problem& p) {
	if (h < p.h)
	{
		return true;
	}

	return false;
}

void problem::print()
{
	for (int i = 0; i < N; i++)
		std::cout << state[i] << " ";
	std::cout << "\n h = " << h << std::endl;
}

int problem::cost = 0;

int problem::get_cost()
{
	return cost;
}
void problem::reset_cost()
{
	cost = 0;
}

int problem::is_conf(int i)
{
	for (int j = i + 1; j < N; j++)
	{
		if (state[j] == state[i] + (j - i))
			return true;
		else if (state[j] == state[i] - (j - i))
			return true;
		else if (state[j] == state[i])
			return true;
	}
	for (int j = i - 1; j >= 0; j--)
	{
		if (state[j] == state[i] + (i - j))
			return true;
		else if (state[j] == state[i] - (i - j))
			return true;
		else if (state[j] == state[i])
			return true;
	}
	return false;
}

int problem::min_conf(int i)
{
	double current_min = h;
	int min_index = i;
	for (int j = 0; j < N; j++)
	{
		state[i] = j;
		appraise();
		if (current_min >= h)
		{
			current_min = h;
			min_index = j;
		}
	}
	//state[i] = min_index;
	//h = current_min;
	return min_index;
}

void problem::set_state_at(int i, int v)
{
	state[i] = v;
	appraise();
}