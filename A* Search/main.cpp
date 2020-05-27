#include <iostream>
#include <vector>
#include "eight_puzzle.h"

int ham_dist(int* state);
int man_dist(int* state);

int main()
{
	eight_puzzle puzzle;
	bool heuristic_flag = 1;
	bool exit = false;
	while (!exit)
	{
		std::cout << "What would you like to do?\n"
			<< "\t1. Set initial puzzle state.\n"
			<< "\t2. Choose Heuristic (Default:Manhattan Dist).\n"
			<< "\t3. Solve using Tree Search.\n"
			<< "\t4. Solve using Graph Search.\n"
			<< "\t5. Display solution step by step.\n"
			<< "\tX. Exit program.\n";
		char choice;
		std::cin >> choice;
		std::cout << std::endl;
		if (choice == '1')
		{
			bool initialized = false;
			while (!initialized)
			{
				std::cout << "How would you like to set the initial state?\n"
					<< "\t1. Custom input.\n"
					<< "\t2. Random (scrambled using legal moves from goal state).\n"
					<< "\t3. Random (scrambled using illegal moves).\n";
				char i;
				std::cin >> i;
				std::cout << std::endl;
				if (i == '1')
				{
					bool good_input = false;
					while (!good_input)
					{
						std::cout << "Enter the order of the tiles separated by space:\n";
						int arr[9];
						char garbage[50];
						std::cin.getline(garbage,50);
						for (int t = 0; t < 9; t++)
							std::cin >> arr[t];
						if (puzzle.solvable(arr))
						{
							good_input = true;
							puzzle.set_initial(arr);
							initialized = true;
							std::cout << "Initialized succesfully. State is solvable.\n";
						}
						else
						{
							std::cout << "bad input. try again.\n";
						}

					}
				}
				else if (i == '2')
				{
					std::cout << "Enter the number of random moves you want to make.\n"
						<< "Be wary, for Tree Search, a puzzle scrambled by more than ~18 moves is likely to cause failure\n";
					int moves;
					std::cin >> moves;
					puzzle.random_state(moves);
					initialized = true;
				}
				else if (i == '3')
				{
					std::cout << "Randomly scrambling the puzzle until we find a viable state.\n";
					puzzle.random_state();
					initialized = true;
				}
				else
				{
					std::cout << "Bad input, try again.\n";
				}
			}
		}
		else if (choice == '2')
		{
			std::cout << "Which Heuristic would you like to use?\n"
				<< "\t1. Hamming Distance.\n"
				<< "\t2. Manhattan Distance.\n";
			char heur;
			std::cin >> heur;
			if (heur == '1')
				heuristic_flag = 0;
			else
				heuristic_flag = 1;
		}
		else if (choice == '3')
		{
			if (puzzle.solvable())
			{
				if (!heuristic_flag)
					puzzle.tree_search(ham_dist);
				else
					puzzle.tree_search(man_dist);
			}
			else
			{
				std::cout << "Puzzle not initialized properly.\n";
			}
		}
		else if (choice == '4')
		{
			if (puzzle.solvable())
			{
				if (!heuristic_flag)
					puzzle.graph_search(ham_dist);
				else
					puzzle.graph_search(man_dist);
			}
			else
			{
				std::cout << "Puzzle not initialized properly.\n";
			}
		}
		else if (choice == '5')
		{
			puzzle.solution_path();
		}
		else if (choice == 'X' || choice == 'x')
		{
			exit = true;
		}
		else
		{
			std::cout << "Invalid choice. Try again.\n";
		}
	}
}

int ham_dist(int* state) 
{
	int ham = 0;
	for (int i = 0; i <9; i++)
	{
		if ((i != state[i]) && (state[i] != 0))
			ham++;
	}
	return ham;
}

int man_dist(int* state) 
{
	int man = 0;
	for (int i = 0; i < 9; i++)
	{
		if ((i != state[i]) && (state[i] != 0))
		{
			int linear_displacement = abs(i - state[i]);
			man += (linear_displacement / 3) + (linear_displacement % 3);
		}
	}
	return man;
}