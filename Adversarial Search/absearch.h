#pragma once
#include "isolation.h"
#include <algorithm>

int absearch(state current, int depth);
double max_value(state current, double a, double b, int &choice, int depth);
double min_value(state current, double a, double b, int &choice, int depth);
double option_ratio(state s);

/*int max_depth(state current, int &choice, int depth);
bool players_separated(state s);
bool contiguous(state c, bool* checked);*/