#include "genetic_search.h"
#include <vector>
#define TEST_MODE true
#define TEST_CASES 100

problem* anneal(problem* p, double(*sched)(double));
double schedule(double time);

int main()
{
	srand(time(NULL));
	genetic_alg test;
	problem a;
	std::cout << "GA:\n";
	std::clock_t start = std::clock();
	test.solve(a);
	double runtime = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	test.print();
	std::cout << "time: " << runtime << "s\n\n";

	std::cout << "SA:\n";
	problem* b = new problem();
	start = std::clock();
	problem* best = anneal(b, schedule);
	runtime = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	best->print();
	std::cout << "time: " << runtime << "s";
	std::cin.get();
	/*srand(time(NULL));
	std::vector<bool> ga_solved, sa_solved;
	std::vector<int> ga_cost, sa_cost;
	std::vector<double> ga_runtime, sa_runtime;
	genetic_alg* test;
	problem* a, *b;
	for (int i = 0; i < TEST_CASES; i++)
	{
		test = new genetic_alg();
		a = new problem();
		std::clock_t start = std::clock();
		test->solve(*a);
		double runtime = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		//record results
		ga_solved.push_back(test->is_solved());
		ga_cost.push_back(test->get_iterations() * POP_SIZE);
		ga_runtime.push_back(runtime);

		b = new problem();
		problem::reset_cost();
		start = std::clock();
		problem* best = anneal(b, schedule);
		runtime = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		//record results
		sa_solved.push_back(best->get_h() == 0);
		sa_cost.push_back(problem::get_cost());
		sa_runtime.push_back(runtime);
	}
	double ga_success = 0;
	for (auto it = ga_solved.begin(); it != ga_solved.end(); it++)
	{
		if (*it)
			ga_success++;
	}
	std::cout << ga_success << "/" << TEST_CASES << " solved by GA." << std::endl;
	std::cout << ga_success / double(TEST_CASES) << " is the success ratio." << std::endl;

	double ga_cost_avg = 0;
	for (auto it = ga_cost.begin(); it != ga_cost.end(); it++)
	{
		ga_cost_avg += *it;
	}
	ga_cost_avg /= double(TEST_CASES);
	std::cout << ga_cost_avg << " children generated on avg." << std::endl;

	double ga_run_avg = 0;
	for (auto it = ga_runtime.begin(); it != ga_runtime.end(); it++)
	{
		ga_run_avg += *it;
	}
	ga_run_avg /= double(TEST_CASES);
	std::cout << ga_run_avg << " second runtime on avg.\n" << std::endl;



	double sa_success = 0;
	for (auto it = sa_solved.begin(); it != sa_solved.end(); it++)
	{
		if (*it)
			sa_success++;
	}
	std::cout << sa_success << "/" << TEST_CASES << " solved by SA." << std::endl;
	std::cout << sa_success / double(TEST_CASES) << " is the success ratio." << std::endl;

	double sa_cost_avg = 0;
	for (auto it = sa_cost.begin(); it != sa_cost.end(); it++)
	{
		sa_cost_avg += *it;
	}
	sa_cost_avg /= double(TEST_CASES);
	std::cout << sa_cost_avg << " children generated on avg." << std::endl;

	double sa_run_avg = 0;
	for (auto it = sa_runtime.begin(); it != sa_runtime.end(); it++)
	{
		sa_run_avg += *it;
	}
	sa_run_avg /= double(TEST_CASES);
	std::cout << sa_run_avg << " second runtime on avg." << std::endl;

	std::cin.get();*/
}

problem* anneal(problem* p, double(*sched)(double))
{
	std::clock_t start = std::clock();
	problem* best = p;
	double best_val = p->get_h();
	problem* current = p;
	problem* next = new problem();
	double temperature=1;
	while (temperature > 0)
	{
		temperature = sched((std::clock() - start) / (double)CLOCKS_PER_SEC);
		next = current->neighbor();
		double delta = current->get_h() - next->get_h();
		bool move = false;
		if (delta > 0)
		{
			delete current;
			current = next;
			move = true;
		}
		else
		{
			double prob = exp(delta / temperature);
			double roll = double(double(rand()) / (RAND_MAX + 1));
			if (prob > roll)
			{
				delete current;
				current = next;
				move = true;
			}
		}
		if (move)
		{
			double h = current->get_h();
			if (h == 0)
			{
				return current;
			}
			else if (h < best_val)
			{
				best = current;
				best_val = h;
			}
		}

	}
	return best;
}

double schedule(double time)
{
	return(1 - (time / .3));
}