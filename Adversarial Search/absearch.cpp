#include "absearch.h"
int absearch(state current, int depth)
{
	int choice = -1;
	/*if (players_separated(current))
	{
		std::cout << "invoking single player mode\n";
		max_depth(current, choice, 0);
	}
	else*/
		max_value(current, -DBL_MAX, DBL_MAX, choice, depth);
	return choice;
}

double max_value(state current, double a, double b, int &choice, int depth)
{
	if (gg(current))
		return -DBL_MAX;
	if (depth <= 0)
		return option_ratio(current);
	int move;
	double v = -DBL_MAX, tempv;
	state s;
	//west successors
	int dir = -1;
	int cursor = current.x + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		tempv = v;
		v = std::max(v, min_value(s, a, b, move, depth - 1));
		if (v != tempv || choice == -1)
			choice = s.x;
		if (v > b)
			return v;
		a = std::max(a, v);
		cursor += dir;
	}
	//northwest successors
	dir = -9;
	cursor = current.x + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		tempv = v;
		v = std::max(v, min_value(s, a, b, move, depth - 1));
		if (v != tempv || choice == -1)
			choice = s.x;
		if (v > b)
			return v;
		a = std::max(a, v);
		cursor += dir;
	}
	//north successors
	dir = -8;
	cursor = current.x + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		tempv = v;
		v = std::max(v, min_value(s, a, b, move, depth - 1));
		if (v != tempv || choice == -1)
			choice = s.x;
		if (v > b)
			return v;
		a = std::max(a, v);
		cursor += dir;
	}
	//northeast successors
	dir = -7;
	cursor = current.x + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		tempv = v;
		v = std::max(v, min_value(s, a, b, move, depth - 1));
		if (v != tempv || choice == -1)
			choice = s.x;
		if (v > b)
			return v;
		a = std::max(a, v);
		cursor += dir;
	}
	//east successors
	dir = 1;
	cursor = current.x + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		tempv = v;
		v = std::max(v, min_value(s, a, b, move, depth - 1));
		if (v != tempv || choice == -1)
			choice = s.x;
		if (v > b)
			return v;
		a = std::max(a, v);
		cursor += dir;
	}
	//southeast successors
	dir = 9;
	cursor = current.x + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		tempv = v;
		v = std::max(v, min_value(s, a, b, move, depth - 1));
		if (v != tempv || choice == -1)
			choice = s.x;
		if (v > b)
			return v;
		a = std::max(a, v);
		cursor += dir;
	}
	//south successors
	dir = 8;
	cursor = current.x + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		tempv = v;
		v = std::max(v, min_value(s, a, b, move, depth - 1));
		if (v != tempv || choice == -1)
			choice = s.x;
		if (v > b)
			return v;
		a = std::max(a, v);
		cursor += dir;
	}
	//southwest successors
	dir = 7;
	cursor = current.x + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		tempv = v;
		v = std::max(v, min_value(s, a, b, move, depth - 1));
		if (v != tempv || choice == -1)
			choice = s.x;
		if (v > b)
			return v;
		a = std::max(a, v);
		cursor += dir;
	}

	return v;
}

double min_value(state current, double a, double b, int &choice, int depth)
{
	if (gg(current))
		return DBL_MAX;
	if (depth <= 0)
		return option_ratio(current);
	int move;
	double v = DBL_MAX, tempv;
	state s;
	//west successors
	int dir = -1;
	int cursor = current.o + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		tempv = v;
		v = std::min(v, max_value(s, a, b, move, depth - 1));
		if (v != tempv)
			choice = s.o;
		if (v < a)
			return v;
		b = std::min(b, v);
		cursor += dir;
	}
	//northwest successors
	dir = -9;
	cursor = current.o + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		tempv = v;
		v = std::min(v, max_value(s, a, b, move, depth - 1));
		if (v != tempv)
			choice = s.o;
		if (v < a)
			return v;
		b = std::min(b, v);
		cursor += dir;
	}
	//north successors
	dir = -8;
	cursor = current.o + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		tempv = v;
		v = std::min(v, max_value(s, a, b, move, depth - 1));
		if (v != tempv)
			choice = s.o;
		if (v < a)
			return v;
		b = std::min(b, v);
		cursor += dir;
	}
	//northeast successors
	dir = -7;
	cursor = current.o + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		tempv = v;
		v = std::min(v, max_value(s, a, b, move, depth - 1));
		if (v != tempv)
			choice = s.o;
		if (v < a)
			return v;
		b = std::min(b, v);
		cursor += dir;
	}
	//east successors
	dir = 1;
	cursor = current.o + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		tempv = v;
		v = std::min(v, max_value(s, a, b, move, depth - 1));
		if (v != tempv)
			choice = s.o;
		if (v < a)
			return v;
		b = std::min(b, v);
		cursor += dir;
	}
	//southeast successors
	dir = 9;
	cursor = current.o + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		tempv = v;
		v = std::min(v, max_value(s, a, b, move, depth - 1));
		if (v != tempv)
			choice = s.o;
		if (v < a)
			return v;
		b = std::min(b, v);
		cursor += dir;
	}
	//south successors
	dir = 8;
	cursor = current.o + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		tempv = v;
		v = std::min(v, max_value(s, a, b, move, depth - 1));
		if (v != tempv)
			choice = s.o;
		if (v < a)
			return v;
		b = std::min(b, v);
		cursor += dir;
	}
	//southwest successors
	dir = -7;
	cursor = current.o + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		tempv = v;
		v = std::min(v, max_value(s, a, b, move, depth - 1));
		if (v != tempv)
			choice = s.o;
		if (v < a)
			return v;
		b = std::min(b, v);
		cursor += dir;
	}

	return v;
}

double option_ratio(state s)
{
	int weights[64];
	for (int i = 0; i < 64; i++)
	{
		if (i < 8 || i>55 || (i % 8) == 0 || (i % 8) == 7)
			weights[i] = 1;
		else if ((i % 8) == 1 || (i % 8) == 6 || i < 23 || i>48)
			weights[i] = 2;
		else if ((i % 8) == 2 || (i % 8) == 5 || i < 30 || i>41)
			weights[i] = 10;
		else
			weights[i] = 20;
	}

	double computer_options = 0, opponent_options = 0;
	//Player X
	//west successors
	int dir = -1;
	int cursor = s.x + dir;
	while (legal(s, cursor))
	{
		computer_options += weights[cursor];
		cursor += dir;
	}
	//northwest successors
	dir = -9;
	cursor = s.x + dir;
	while (legal(s, cursor))
	{
		computer_options += weights[cursor];
		cursor += dir;
	}
	//north successors
	dir = -8;
	cursor = s.x + dir;
	while (legal(s, cursor))
	{
		computer_options += weights[cursor];
		cursor += dir;
	}
	//northeast successors
	dir = -7;
	cursor = s.x + dir;
	while (legal(s, cursor))
	{
		computer_options += weights[cursor];
		cursor += dir;
	}
	//east successors
	dir = 1;
	cursor = s.x + dir;
	while (legal(s, cursor))
	{
		computer_options += weights[cursor];
		cursor += dir;
	}
	//southeast successors
	dir = 9;
	cursor = s.x + dir;
	while (legal(s, cursor))
	{
		computer_options += weights[cursor];
		cursor += dir;
	}
	//south successors
	dir = 8;
	cursor = s.x + dir;
	while (legal(s, cursor))
	{
		computer_options += weights[cursor];
		cursor += dir;
	}
	//southwest successors
	dir = -7;
	cursor = s.x + dir;
	while (legal(s, cursor))
	{
		computer_options += weights[cursor];
		cursor += dir;
	}

	//Player O
	//west successors
	dir = -1;
	cursor = s.o + dir;
	while (legal(s, cursor))
	{
		opponent_options += weights[cursor];
		cursor += dir;
	}
	//northwest successors
	dir = -9;
	cursor = s.o + dir;
	while (legal(s, cursor))
	{
		opponent_options += weights[cursor];
		cursor += dir;
	}
	//north successors
	dir = -8;
	cursor = s.o + dir;
	while (legal(s, cursor))
	{
		opponent_options += weights[cursor];
		cursor += dir;
	}
	//northeast successors
	dir = -7;
	cursor = s.o + dir;
	while (legal(s, cursor))
	{
		opponent_options += weights[cursor];
		cursor += dir;
	}
	//east successors
	dir = 1;
	cursor = s.o + dir;
	while (legal(s, cursor))
	{
		opponent_options += weights[cursor];
		cursor += dir;
	}
	//southeast successors
	dir = 9;
	cursor = s.o + dir;
	while (legal(s, cursor))
	{
		opponent_options += weights[cursor];
		cursor += dir;
	}
	//south successors
	dir = 8;
	cursor = s.o + dir;
	while (legal(s, cursor))
	{
		opponent_options += weights[cursor];
		cursor += dir;
	}
	//southwest successors
	dir = -7;
	cursor = s.o + dir;
	while (legal(s, cursor))
	{
		opponent_options += weights[cursor];
		cursor += dir;
	}
	if (opponent_options == 0)
		return DBL_MAX;
	computer_options += 10 * weights[s.x];
	opponent_options += 10 * weights[s.o];
	return computer_options / opponent_options;
}

/*int max_depth(state current, int &choice, int depth)
{
	if (gg(current))
		return depth;
	int move;
	int best_depth = depth;
	int temp;
	state s;
	//west successors
	int dir = -1;
	int cursor = current.x + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		temp = best_depth;
		best_depth = std::max(best_depth, max_depth(s, move, depth + 1));
		if (best_depth != temp || choice == -1)
			choice = s.x;
		cursor += dir;
	}
	//northwest successors
	dir = -9;
	cursor = current.x + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		temp = best_depth;
		best_depth = std::max(best_depth, max_depth(s, move, depth + 1));
		if (best_depth != temp || choice == -1)
			choice = s.x;
		cursor += dir;
	}
	//north successors
	dir = -8;
	cursor = current.x + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		temp = best_depth;
		best_depth = std::max(best_depth, max_depth(s, move, depth + 1));
		if (best_depth != temp || choice == -1)
			choice = s.x;
		cursor += dir;
	}
	//northeast successors
	dir = -7;
	cursor = current.x + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		temp = best_depth;
		best_depth = std::max(best_depth, max_depth(s, move, depth + 1));
		if (best_depth != temp || choice == -1)
			choice = s.x;
		cursor += dir;
	}
	//east successors
	dir = 1;
	cursor = current.x + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		temp = best_depth;
		best_depth = std::max(best_depth, max_depth(s, move, depth + 1));
		if (best_depth != temp || choice == -1)
			choice = s.x;
		cursor += dir;
	}
	//southeast successors
	dir = 9;
	cursor = current.x + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		temp = best_depth;
		best_depth = std::max(best_depth, max_depth(s, move, depth + 1));
		if (best_depth != temp || choice == -1)
			choice = s.x;
		cursor += dir;
	}
	//south successors
	dir = 8;
	cursor = current.x + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		temp = best_depth;
		best_depth = std::max(best_depth, max_depth(s, move, depth + 1));
		if (best_depth != temp || choice == -1)
			choice = s.x;
		cursor += dir;
	}
	//southwest successors
	dir = 7;
	cursor = current.x + dir;
	while (legal(current, cursor))
	{
		s = successor(current, cursor);
		temp = best_depth;
		best_depth = std::max(best_depth, max_depth(s, move, depth + 1));
		if (best_depth != temp || choice == -1)
			choice = s.x;
		cursor += dir;
	}

	return best_depth;
}

bool players_separated(state s)
{
	bool checked[64];
	for (int i = 0; i < 64; i++)
		checked[i] = false;
	s.board[s.o] = '-';
	s.my_turn = true;
	return !contiguous(s, checked);
}

bool contiguous(state c, bool* checked)
{
	if (c.x == c.o)
		return true;
	state next;
	//west
	int dir = c.x - 1;
	if (legal(c, dir) && !checked[dir])
	{
		next = successor(c, dir);
		next.my_turn = true;
		checked[dir] = true;
		if (contiguous(next, checked))
			return true;
	}
	//nortwest
	dir = c.x - 9;
	if (legal(c, dir) && !checked[dir])
	{
		next = successor(c, dir);
		next.my_turn = true;
		checked[dir] = true;
		if (contiguous(next, checked))
			return true;
	}
	//north
	dir = c.x - 8;
	if (legal(c, dir) && !checked[dir])
	{
		next = successor(c, dir);
		next.my_turn = true;
		checked[dir] = true;
		if (contiguous(next, checked))
			return true;
	}
	//northeast
	dir = c.x - 7;
	if (legal(c, dir) && !checked[dir])
	{
		next = successor(c, dir);
		next.my_turn = true;
		checked[dir] = true;
		if (contiguous(next, checked))
			return true;
	}
	//east
	dir = c.x + 1;
	if (legal(c, dir) && !checked[dir])
	{
		next = successor(c, dir);
		next.my_turn = true;
		checked[dir] = true;
		if (contiguous(next, checked))
			return true;
	}
	//southeast
	dir = c.x + 9;
	if (legal(c, dir) && !checked[dir])
	{
		next = successor(c, dir);
		next.my_turn = true;
		checked[dir] = true;
		if (contiguous(next, checked))
			return true;
	}
	//south
	dir = c.x + 8;
	if (legal(c, dir) && !checked[dir])
	{
		next = successor(c, dir);
		next.my_turn = true;
		checked[dir] = true;
		if (contiguous(next, checked))
			return true;
	}
	//southwest
	dir = c.x + 7;
	if (legal(c, dir) && !checked[dir])
	{
		next = successor(c, dir);
		next.my_turn = true;
		checked[dir] = true;
		if (contiguous(next, checked))
			return true;
	}

	return false;
}*/