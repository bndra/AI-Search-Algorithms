#include "isolation.h"
#include "absearch.h"

int main()
{
	game isolation(*absearch);
	isolation.play();
}