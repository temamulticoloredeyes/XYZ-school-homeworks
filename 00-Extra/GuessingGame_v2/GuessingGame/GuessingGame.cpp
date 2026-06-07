// GuessingGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
	// Ask user to think about number from 1 to 100
	// Set min as 1 and max as 100
	// isGuessed = false
	// numTries = 0
	// while (!isGuessed)
	//     ++numTries
	//     guess = (min + max) / 2
	//     ask user is guess correct
	//     if yes
	//         isGuessed = true
	//     else
	//         ask user if his number is greater than guess
	//         if yes
	//             min = guess + 1
	//         if no
	//             max = guess - 1
	//     if min >= max
	//         say user he is cheating and break the cycle
	// Say about number of tries and exit

	std::cout << "Hello, let's play a game! You guess a number from 1 to 100 amd i guess, let's go? Y/N" << std::endl;;
	std::string answer;
	std::cin >> answer;
	if (answer != "y"  && answer != "Y" && answer != "Yes" && answer != "YES") {
		std::cout << "Sad, come back when you want to play." << std::endl;
		return 0;
	}

	int min = 1;
	int max = 100;
	bool isGuessed = false;
	int numTries = 0;

	while (!isGuessed)
	{
		numTries++;
		int guess = (min + max) / 2;
		std::cout << "Ok! Maybe youre number is " << guess << " ? Y/N" << std::endl;
		std::string answer;
		std::cin >> answer;
		
		if (answer == "y" || answer == "Y" || answer == "Yes" || answer == "YES") {
			isGuessed = true;
			std::cout << "Whoo-hoo, I was able to guess in " << numTries << " attempt(s). Thank you for playing!" << std::endl;
		}
		else
		{
			std::cout << "Hmm.. Youre number is greater than guess? Y/N" << std::endl;
			std::string answer;
			std::cin >> answer;

			if (answer == "y" || answer == "Y" || answer == "Yes" || answer == "YES")
			{
				min = guess + 1;
			}
			else
			{
				max = guess - 1;
			}
			if (min > max)
			{
				std::cout << "You are cheater! >_<" << std::endl;
				break;
			}
		}
	}
}