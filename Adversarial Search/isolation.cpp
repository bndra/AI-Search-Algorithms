#include "isolation.h"

int translate(std::string coord)
{
	char row = toupper(coord[0]);
	int col = (int(coord[1]) - 48), index;
	row = toupper(row) - 'A';
	index = int(row) * 8 + col - 1;
	return index;
}
std::string translate(int index)
{
	char row = 'A';
	for (int i = 0; i < index / 8; i++)
		row++;
	std::string coord = "";
	coord += row;
	coord += std::to_string((index % 8) + 1);
	return coord;
}

game::game()
{
	for (int i = 0; i < size; i++)
	{
		s.board[i] = '-';
	}
	s.board[0] = 'X';
	s.board[63] = 'O';
	s.x = 0;
	s.o = 63;
	s.my_turn = true;
	turns = 0;
}

game::game(int(*search)(state,int))
{
	for (int i = 0; i < size; i++)
	{
		s.board[i] = '-';
	}
	s.board[0] = 'X';
	s.board[63] = 'O';
	s.x = 0;
	s.o = 63;
	s.my_turn = true;
	turns = 0;
	ai = search;
}

void game::play()
{
	who_first();
	bool game_over = false;
	int index;
	std::string coord;
	while (!game_over)
	{
		//system("CLS");
		print();
		if (s.my_turn) //computer turn
			index = ai(s, 7);
		else           //player turn
			index = user_in();
		if (legal(s, index))
		{
			move(index);
			game_over = gg(s);
		}
		else
		{
			std::cout << translate(index) << " is an illegal move. press enter then try again.";
			std::cin.get();//eats the extra newline char
			std::cin.get();
		}
	}

	//system("CLS");
	print();
	std::cout << "Game over.\n";
	if (!s.my_turn)
		std::cout << "X wins.";
	else
		std::cout << "O wins.";
	std::cin.get();//eats the extra newline char
	std::cin.get();
}

void game::who_first()
{
	std::cout << "Who goes first, C for computer, O for opponent: ";
	char choice;
	bool done = false;
	while (!done)
	{
		std::cin >> choice;
		choice = toupper(choice);
		done = true;
		if (choice == 'C')
			s.my_turn = true;
		else if (choice == 'O')
			s.my_turn = false;
		else
		{
			std::cout << "Bad input. Please try again";
			done = false;
		}
	}
}

int game::user_in()
{
	std::cout << "Enter the move: ";
	std::string coord;
	std::cin >> coord;
	return translate(coord);
}

void game::move(int moveto)
{
	int current;
	if (s.my_turn)
		current = s.x;
	else
		current = s.o;

	s.board[moveto] = s.board[current];
	s.board[current] = '#';

	if (s.my_turn)
		s.x = moveto;
	else
		s.o = moveto;

	s.my_turn = !s.my_turn;

	hist[turns] = moveto;
	turns++;
}

void game::print()
{
	std::cout << "  1 2 3 4 5 6 7 8\tPlayer1 vs Player2" << std::endl; //or opponent vs computer
	char row = 'A';
	for (int i = 0; i < 8; i++)
	{
		std::cout << row;
		for (int j = i*8; j < (i+1)*8; j++)
		{
			std::cout << " " << s.board[j];
		}
		std::cout << "\t";
		if (turns > 2 * i)
			std::cout << translate(hist[2 * i]);
		if (turns > (2 * i) + 1)
			std::cout << "\t" << translate(hist[(2 * i) + 1]);
		std::cout << std::endl;
		row++;
	}
	for (int i = 8; i <= turns / 2; i++)
	{
		std::cout << "\t\t\t";
		if (turns > 2 * i)
			std::cout << translate(hist[2 * i]);
		if (turns >(2 * i) + 1)
			std::cout << "\t" << translate(hist[(2 * i) + 1]);
		std::cout << std::endl;
	}
}

state successor(state c, int moveto)
{
	int current;
	if (c.my_turn)
		current = c.x;
	else 
		current = c.o;

	c.board[moveto] = c.board[current];
	c.board[current] = '#';

	if (c.my_turn)
		c.x = moveto;
	else
		c.o = moveto;

	c.my_turn = !c.my_turn;
	return c;
}

bool legal(state s, int index)
{
	if (!sane(s, index))
		return false;

	int loc;
	if (s.my_turn)
		loc = s.x;
	else
		loc = s.o;

	if (loc > index)
	{
		if ((loc / 8) == (index / 8))
		{
			if (check_west(loc, index, s))
				return true;
		}
		else if ((loc % 8) == (index % 8))
		{
			if (check_north(loc, index, s))
				return true;
		}
		else if ((loc%9)==(index%9))
		{
			if (check_northwest(loc, index, s))
				return true;
		}
		else if ((loc%7)==(index%7))
		{
			if (check_northeast(loc, index, s))
				return true;
		}
	}
	else
	{
		if ((loc / 8) == (index / 8))
		{
			if (check_east(loc, index, s))
				return true;
		}
		else if ((loc % 8) == (index % 8))
		{
			if (check_south(loc, index, s))
				return true;
		}
		else if ((loc % 9) == (index % 9))
		{
			if (check_southeast(loc, index, s))
				return true;
		}
		else if ((loc % 7) == (index % 7))
		{
			if (check_southwest(loc, index, s))
				return true;
		}
	}
	return false;
}

bool sane(state s, int index)
{
	if (index > 63 || index < 0)//can't move out of bounds
		return false;
	if (s.board[index] != '-')//can't move to an occupied spot
		return false;
	return true;
}

bool gg(state c)
{
	int position;
	if (c.my_turn)
		position = c.x;
	else
		position = c.o;

	if (legal(c, position - 1))//<
		return false;
	if (legal(c, position - 9))//< ^
		return false;
	if (legal(c, position - 8))//  ^
		return false;
	if (legal(c, position - 7))//  ^ >
		return false;
	if (legal(c, position + 1))//    >
		return false;
	if (legal(c, position + 9))//  v >
		return false;
	if (legal(c, position + 8))//  v
		return false;
	if (legal(c, position + 7))//< v
		return false;

	//there were no moves available, the game is over
	return true;
}

bool check_west(int loc, int dest, state s)
{
	bool done = false;
	int cursor = loc;
	while (!done)
	{
		int col = cursor % 8;
		if (cursor == dest)
			return true;
		if (col == 0)//can't pass east border
			done = true;
		else if (s.board[cursor] != '-' && cursor != loc)
			done = true;
		cursor--;//shift left once
	}
	return false;
}
bool check_northwest(int loc, int dest, state s)
{
	bool done = false;
	int cursor = loc;
	while (!done)
	{
		int col = cursor % 8;
		if (cursor == dest)
			return true;
		if (col == 0 || cursor < 8)//can't pass west or north border
			done = true;
		else if (s.board[cursor] != '-' && cursor != loc)
			done = true;
		cursor--;//shift left once
		cursor -= 8;//shift up once
	}
	return false;
}
bool check_north(int loc, int dest, state s)
{
	bool done = false;
	int cursor = loc;
	while (!done)
	{
		if (cursor == dest)
			return true;
		if (cursor < 8)//can't pass north edge
			done = true;
		else if (s.board[cursor] != '-' && cursor != loc)
			done = true;
		cursor -= 8;//shift up once
	}
	return false;
}
bool check_northeast(int loc, int dest, state s)
{
	bool done = false;
	int cursor = loc;
	while (!done)
	{
		int col = cursor % 8;
		if (cursor == dest)
			return true;
		if (col == 7 || cursor < 8)//can't pass north or east edge
			done = true;
		else if (s.board[cursor] != '-' && cursor != loc)
			done = true;
		cursor++;//shift right once
		cursor -= 8;//shift up once
	}
	return false;
}
bool check_east(int loc, int dest, state s)
{
	bool done = false;
	int cursor = loc;
	while (!done)
	{
		int col = cursor % 8;
		if (cursor == dest)
			return true;
		if (col == 7)//can't pass east edge
			done = true;
		else if (s.board[cursor] != '-' && cursor != loc)
			done = true;
		cursor++;//shift right once
	}
	return false;
}
bool check_southeast(int loc, int dest, state s)
{
	bool done = false;
	int cursor = loc;
	while (!done)
	{
		int col = cursor % 8;
		if (cursor == dest)
			return true;
		if (col == 7 || cursor > 55)//can't pass east or south edge
			done = true;
		else if (s.board[cursor] != '-' && cursor != loc)
			done = true;
		cursor++;//shift right once
		cursor += 8;//shift down once
	}
	return false;
}
bool check_south(int loc, int dest, state s)
{
	bool done = false;
	int cursor = loc;
	while (!done)
	{
		if (cursor == dest)
			return true;
		if (cursor > 55)//can't go past south edge
			done = true;
		else if (s.board[cursor] != '-' && cursor != loc)
			done = true;
		cursor += 8;//shift down once
	}
	return false;
}
bool check_southwest(int loc, int dest, state s)
{
	bool done = false;
	int cursor = loc;
	while (!done)
	{
		int col = cursor % 8;
		if (cursor == dest)
			return true;
		if (col == 0 || cursor > 55)//if we're at the west or south edge we can't continue
			done = true;
		else if (s.board[cursor] != '-' && cursor != loc)
			done = true;
		cursor--;//shift left once
		cursor += 8;//shift down once
	}
	return false;
}


