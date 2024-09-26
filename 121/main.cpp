#include <iostream>
using namespace std;

bool is_prime(int number)
{

	// short-circuit 0; neither prime nor composite and short-circuit 1; not prime by definition
	if (number <= 1)
	{
		return false;
	}

	// excluding 0, 1 and the number itself, we iterate from the number across all possible divisors; if any of them cleanly divide n, it is not prime.
	for (int i = number - 1; i > 1; i--)
	{
		if (number % i == 0)
		{
			return false;
		}
	}

	// Shortcut to true; if nothing is divisible, it is prime.
	return true;
}

int main()
{

	int number;

	cout << "Enter an integer number: ";

	cin >> number;

	if (is_prime(number))
	{

		cout << number << " is a prime number." << endl;
	}

	else
	{

		cout << number << " is not a prime number." << endl;
	}

	return 0;
}
