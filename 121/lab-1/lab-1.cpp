#include <stdio.h>
#include <time.h>
#include <iostream>
using namespace std;

int random_val(int lower_bound, int upper_bound)
{
	return lower_bound + rand() % upper_bound;
}

int shot_event(string shot_team)
{
	cout << shot_team << " has shot at target" << endl;
	int scored = random_val(0, 3);

	if (scored == 0)
	{
		// Team scored
	}

	if (scored == 1)
	{
	}

	if (scored == 2)
	{
	}

	if (scored == 3)
	{
	}

	return 'hi';
}

int foul_event(string penalized_team, string awarded_team)
{
	cout << team << " has fouled, " << team << " has free kick" << endl;
	return 0;
}

int penalty_event(string penalized_team, string awarded_team)
{
	cout << penalized_team << " has committed a foul close to the goal and team " << awarded_team << " was awarded a penalty" << endl;

	return 0;
}

int run_event()
{
	int event_type = 1 + rand() % 6;
	switch (event_type)
	{
	case 1:
		// A has shot at target
		break;
	case 2:
		// B has shot
		break;
	case 3:
		// B has fouled, A has free kick
		break;
	case 4:
		//
		break;
	case 5:
		// B has committed a foul close to the goal and team A was awarded a penalty
		break;
	case 6:
		break;

	default:
		break;
	}

	return 0;
}

int run_half(int events, string)
{
	return 0;
}

int main()
{
	srand(time(NULL));					// Initialize seed for srand
	float num_events = 1 + rand() % 30; // Float because we need to divide into two
	cout << "Number of events: " << num_events << endl;

	// Split halves:
	int half1 = floor(num_events / 2);
	int half2 = ceil(num_events / 2);

	cout << "Half 1: " << half1 << endl;
	cout << "Half 2: " << half2 << endl;

	return 0;
}
