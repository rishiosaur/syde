/*

Lab 1: Soccer Simulation
Testing scenarios - I wanted to make sure a couple things were correct:
1. For every event and sub-event (define a sub-event to be either an event w/ a goal score or a foul and an event to be some composition of sub-events), the sum of the missed goals for a team should be the sum of the non-net shots and the sum of the other teams' blocked and saved shots.
2. The random value function should be inclusive across all possible ranges

In order to test these two constraints—correctness and randomness, I added in a few important measures.
1. Added a log_state function (and in previous versions, which are available on GitHub at z.rishi.cx/g/syde, event-specific logging) to log the differences between values—if, in any case, the sum of the relevant values did not match, the program would exit with an error code. I did this in addition to manually checking in initial versions of the program.
2. Added error cases to defaults for all the switch cases. If the random function delivered values that were out-of-range, the program would exit.
*/
#include <stdio.h>
#include <time.h>
#include <iostream>
using namespace std;

/*

assignment & state

tracking: goals scored, shots taken, shot on goal, shots saved, shots off goal, shots blocked

*/

// State
int a_goals, a_shots_on_target, a_shots_off_target, a_missed, a_saved, a_blocked, a_fouls, a_yellow, a_red;

int b_goals, b_shots_on_target, b_shots_off_target, b_missed, b_saved, b_blocked, b_fouls, b_yellow, b_red;

// Assignment Utils
void increment_team(string team, int &a_state, int &b_state);

/*

utilities

*/

int random_val(int lower_bound, int upper_bound);

string opposing_team(string team);

void log_state();
void log_divider();
void log_subdivider();

/*
sub-events
*/
void goal_sub_event(int options, string shot_team);
void card_sub_event(string foul_team);

/*

events

*/

void shot_event(string shot_team);
void foul_event(string penalized_team, string awarded_team);
void penalty_event(string penalized_team, string awarded_team);

/*
running

*/

void run_event();
void run_half(int events, string prefix);

int main()
{
	srand(time(NULL));					// Initialize seed for srand
	float num_events = 1 + rand() % 30; // Float because we need to divide into two
	cout << "🏟️ ⚽ WARRIOR FIELD, circa. 1980s ⚽🏟️" << endl;
	cout << "WATERLOO️ WARRIORS (A) 🆚 TORONTO VARSITY BLUES (B)" << endl;
	log_divider();
	cout << num_events << " events to be simulated" << endl;

	// Split halves:
	int half1 = floor(num_events / 2);
	int half2 = ceil(num_events / 2);

	cout << "1️⃣ First half: " << half1 << " events" << endl;
	cout << "2️⃣ Second half: " << half2 << " events" << endl;

	log_divider();

	srand(time(NULL)); // Initialize seed for srand
	run_half(half1, "FIRST");
	srand(time(NULL)); // Initialize seed for srand
	run_half(half2, "SECOND");

	// Final stats
	// Log out winning team and score
	if (a_goals > b_goals)
	{
		cout << "🏆 Waterloo Warriors (A) win by " << a_goals - b_goals << " goals." << endl;
	}
	else if (b_goals > a_goals)
	{
		cout << "🏆 Toronto Varsity Blues (B) win by " << b_goals - a_goals << " goals." << endl;
	}
	else
	{
		cout << "🏆 The game ends in a draw." << endl;
	}

	// Log out final score
	cout << "🏁 FINAL SCORE: A scored " << a_goals << " to B's " << b_goals << endl;

	return 0;
}

/*


===

DECLARATIONS

===


*/

int random_val(int lower_bound, int upper_bound)
{
	return lower_bound + (rand() % (upper_bound - lower_bound + 1));
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

void log_state()
{
	cout << "📊 GAME STATS 📊" << endl;

	// Log out summary
	cout << "✅ A has scored " << a_goals << " goals with " << a_shots_on_target << " shots on goal & " << a_shots_off_target << " shots off goal - " << b_saved + b_blocked << " shots were blocked, with " << a_missed << " goals missing the net entirely" << endl;
	cout << "✅ B has scored " << b_goals << " goals with " << b_shots_on_target << " shots on goal & " << b_shots_off_target << " shots off goal - " << a_saved + a_blocked << " shots were blocked, with " << b_missed << " goals missing the net entirely" << endl;
	cout << endl;

	// Log out general stats
	cout << "🥅 A's players have saved " << a_saved << " shots, and their goalie and defence have blocked " << a_blocked << " shots" << endl;
	cout << "🥅 B's players have saved " << b_saved << " shots, and their goalie and defence have blocked " << b_blocked << " shots" << endl;
	cout << endl;

	// Log out foul values
	cout << "💥 A has committed " << a_fouls << " fouls, with 🟨 " << a_yellow << " yellow cards and 🟥" << a_red << " red cards" << endl;
	cout << "💥 B has committed " << b_fouls << " fouls, with 🟨 " << b_yellow << " yellow cards and 🟥" << b_red << " red cards" << endl;
	cout << endl;

	// Winning at current state
	if (a_goals > b_goals)
	{
		cout << "🏆 A is currently winning by " << a_goals - b_goals << " goals" << endl;
	}
	else if (b_goals > a_goals)
	{
		cout << "🏆 B is currently winning by " << b_goals - a_goals << " goals" << endl;
	}
	else
	{
		cout << "🏆 The game is currently tied." << endl;
	}
}

void log_divider()
{
	cout << "====================" << endl;
}

void log_subdivider()
{
	cout << "---------------------" << endl;
}

/*

sub-events

*/

void goal_sub_event(int options, string shot_team)
{
	int scored = random_val(0, options);
	// increment_team(shot_team, a_shots, b_shots);
	switch (scored)
	{
	case 0:
		// Team scored
		increment_team(shot_team, a_shots_on_target, b_shots_on_target);
		increment_team(shot_team, a_goals, b_goals);
		cout << "↳ ✅ " << shot_team << " scores!" << endl;
		break;
	case 1:
		// Saved by opposing goalkeeper

		increment_team(shot_team, a_shots_on_target, b_shots_on_target);
		increment_team(opposing_team(shot_team), a_saved, b_saved);
		cout << "↳ ⛔ " << opposing_team(shot_team) << "'s goalkeeper or defenders just saved the shot!" << endl;
		break;
	case 2:
		// Missed goal

		increment_team(shot_team, a_shots_off_target, b_shots_off_target);
		increment_team(shot_team, a_missed, b_missed);
		cout << "↳ ❌ " << shot_team << " misses the goal!" << endl;
		break;
	case 3:
		// Blocked by player

		increment_team(shot_team, a_shots_on_target, b_shots_on_target);
		increment_team(opposing_team(shot_team), a_blocked, b_blocked);
		cout << "↳ 💨 " << opposing_team(shot_team) << "'s players just saved the shot!" << endl;
		break;
	default:
		exit(1);
		break;
	}
}

void card_sub_event(string foul_team)
{
	int resolved = random_val(0, 2);
	increment_team(foul_team, a_fouls, b_fouls);
	switch (resolved)
	{
	case 0:
		// No card given
		cout << "↳ 🏳️ " << "No card given to " << foul_team << endl;
		break;
	case 1:
		// Yellow card
		increment_team(foul_team, a_yellow, b_yellow);
		cout << "↳ 🟨 " << "Yellow card given to " << foul_team << endl;
		break;
	case 2:
		// Red card
		increment_team(foul_team, a_red, b_red);
		cout << "↳ 🟥 " << "Red card given to " << foul_team << endl;
		break;
	default:
		exit(1);
		break;
	}
}

/*

game events

*/

void shot_event(string shot_team)
{
	cout << shot_team << " has shot at target" << endl;

	goal_sub_event(3, shot_team);
}

void foul_event(string penalized_team, string awarded_team)
{
	cout << penalized_team << " has fouled, " << awarded_team << " has a free kick and shoots" << endl;

	goal_sub_event(3, awarded_team);
	card_sub_event(penalized_team);
}

void penalty_event(string penalized_team, string awarded_team)
{
	cout << penalized_team << " has committed a foul close to the goal and team " << awarded_team << " was awarded a penalty" << endl;

	goal_sub_event(2, awarded_team);
	card_sub_event(penalized_team);
}

void run_event()
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
		// Short circuit to test randomness
		exit(1);
		break;
	}
}

void run_half(int events, string prefix)
{

	srand(time(NULL));
	cout << "🏁  " << prefix << " HALF BEGINS: " << events << " events 🏁" << endl;

	for (int i = 0; i < events; i++)
	{
		cout << endl;
		cout << "🔵 Event " << i + 1 << ": ";
		run_event();
		cout << endl;
	}

	log_subdivider();
	cout << "🏁 HALF COMPLETE 🏁" << endl;
	log_state();
	log_divider();
}
