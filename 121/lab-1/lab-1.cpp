#include <stdio.h>
#include <time.h>
#include <iostream>
using namespace std;

/*

assignment & state

*/

// State
int a_goals, a_shots, a_missed, a_saved, a_blocked, a_fouls, a_yellow, a_red;

int b_goals, b_shots, b_missed, b_saved, b_blocked, b_fouls, b_yellow, b_red;

// Assignment utils
void increment_team(string team, int &a_state, int &b_state)
{
	if (team == "A")
	{
		a_state++;
	}
	else
	{
		b_state++;
	}
}

/*

utilities

*/

int random_val(int lower_bound, int upper_bound)
{
	return lower_bound + rand() % upper_bound;
}

string opposing_team(string team)
{
	if (team == "A")
	{
		return "B";
	}
	else
	{
		return "A";
	}
}

/*

sub-events

*/

int goal_sub_event(int options, string shot_team)
{
	int scored = random_val(0, options);

	if (scored == 0)
	{
		// Team scored
		increment_team(shot_team, a_goals, b_goals);
		cout << shot_team << " has scored" << endl;
	}

	if (scored == 1)
	{
		// Saved by opposing goalkeeper
		increment_team(opposing_team(shot_team), a_saved, b_saved);
		cout << "shot by " << shot_team << " has been saved by the goalkeeper or last defender of " << opposing_team(shot_team) << endl;
	}

	if (scored == 2)
	{
		// missed goal
		increment_team(shot_team, a_missed, b_missed);
		cout << shot_team << " has missed the goal" << endl;
	}

	if (scored == 3)
	{
		// Blocked by player
		increment_team(opposing_team(shot_team), a_blocked, b_blocked);

		cout << "shot by " << shot_team << " has been blocked by a player who is not the last defender of " << opposing_team(shot_team) << endl;
	}

	return 0;
}

int card_sub_event(string foul_team)
{
	int resolved = random_val(0, 2);
	// increment_team(foul_team, a_fouls, b_fouls);
	if (resolved == 0)
	{
		// No card given
		cout << "No card given to " << foul_team << endl;
	}

	if (resolved == 1)
	{
		// Yellow card
		increment_team(foul_team, a_yellow, b_yellow);
		cout << "Yellow card given to " << foul_team << endl;
	}

	if (resolved == 2)
	{
		// Red card
		increment_team(foul_team, a_red, b_red);
		cout << "Red card given to " << foul_team << endl;
	}
}

/*

game events

*/

int shot_event(string shot_team)
{
	cout << shot_team << " has shot at target" << endl;
	increment_team(shot_team, a_shots, b_shots);

	goal_sub_event(3, shot_team);

	return 0;
}

int foul_event(string penalized_team, string awarded_team)
{
	cout << penalized_team << " has fouled, " << awarded_team << " has free kick" << endl;
	increment_team(penalized_team, a_fouls, b_fouls);

	goal_sub_event(3, awarded_team);
	card_sub_event(penalized_team);

	return 0;
}

int penalty_event(string penalized_team, string awarded_team)
{
	cout << penalized_team << " has committed a foul close to the goal and team " << awarded_team << " was awarded a penalty" << endl;

	goal_sub_event(2, awarded_team);
	card_sub_event(penalized_team);

	return 0;
}

int run_event()
{
	int event_type = random_val(1, 6);
	switch (event_type)
	{
	case 1:
		// A has shot at target

		shot_event("A");
		break;
	case 2:
		// B has shot
		shot_event("B");
		break;
	case 3:
		// B has fouled, A has free kick
		foul_event("B", "A");
		break;
	case 4:
		// A has fouled, B has free kick
		foul_event("A", "B");
		break;
	case 5:
		// B has committed a foul close to the goal and team A was awarded a penalty
		penalty_event("B", "A");

		break;
	case 6:
		// A has committed a foul close to the goal and team B was awarded a penalty
		penalty_event("A", "B");
		break;

	default:
		break;
	}

	return 0;
}

int run_half(int events)
{
	for (int i = 0; i < events; i++)
	{

		cout << "Event " << i + 1 << endl;
		run_event();
		cout << "---" << endl;
	}
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
	run_half(half1);
	cout << "Half 2: " << half2 << endl;
	run_half(half2);

	return 0;
}
