#include "problem.h"
#include <ctime>
#define MAX_STEPS 100
#define MAX_RETRY 100
#define TEST_CASES 500

bool min_conf(problem &csp, int max)
{
	int counter = 0;
	//table to keep track of which var are in conflict
	bool conf_table[N];
	for (int i = 0; i < N; i++)
		conf_table[i] = csp.is_conf(i);

	for (int i = 0; i < max; i++)
	{
		//check if solved: return the solution
		if (csp.get_h() == 0)
		{
			return true;
		}
		//randomly select conflicted var
		int rand_conf = rand() % N;
		while (!conf_table[rand_conf])
		{
			rand_conf++;
			rand_conf = rand_conf % N;
		}
		//calculate and assign it the min conflicts value
		csp.set_state_at(rand_conf, csp.min_conf(rand_conf));
		//update table
		for (int i = 0; i < N; i++)
			conf_table[i] = csp.is_conf(i);

		counter++;
	}
	//return failure
	return false;
}

int main()
{
	/*bool success[TEST_CASES] = { false };
	double runtime[TEST_CASES];
	for (int i = 0; i < TEST_CASES; i++)
	{
		std::clock_t start = std::clock();
		problem csp;
		int initial[N];
		bool out = false;
		for (int j = 0; j < MAX_RETRY; j++)
		{


			for (int k = 0; k < N; k++)
				initial[k] = 0;
			csp.set_state(initial);
			out = min_conf(csp, MAX_STEPS);
			if (out)
			{
				success[i] = out;
				break;
			}
		}
		runtime[i] = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	}
	double success_rate = 0;
	double avg_runtime = 0;
	for (int i = 0; i < TEST_CASES; i++)
	{
		if (success[i])
			success_rate++;
		avg_runtime += runtime[i];
	}
	success_rate /= TEST_CASES;
	avg_runtime /= TEST_CASES;
	std::cout << TEST_CASES << " trials.\nsuccess rate: " << success_rate
		<< "\navg runtime: " << avg_runtime;
	std::cin.get();*/

	srand(time(NULL));
	problem csp; 
	int initial[N];
	bool out = false;
	std::clock_t start = std::clock();
	for (int i = 0; i < MAX_RETRY; i++)
	{

		for (int i = 0; i < N; i++)
			initial[i] = 0;
		csp.set_state(initial);
		out = min_conf(csp, MAX_STEPS);
		if (out)
		{
			csp.print();
			std::cout << "true on try " << i << std::endl;
			break;
		}
		else
			std::cout << "false" << std::endl;

		

	}
	double runtime = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "runtime: " << runtime;
	std::cin.get();
}