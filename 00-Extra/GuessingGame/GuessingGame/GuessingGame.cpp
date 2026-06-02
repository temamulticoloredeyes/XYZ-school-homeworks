#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    std::cout << "Helo, enter your name:  \n";
    std::string userName;
    std::cin >> userName;

    std::cout << "Hello " + userName + " " + "Let's play a game? I have picked a random number between 1 and 100. Try to guess it! \n";
    std::cout << "Enter your guess: \n";
    
    srand(time(nullptr));
    int randNumber = rand() % 100 + 1;
    int userNumber;
    int tries = 1;
    const int bestTries = 8;
   
    std::cin >> userNumber;
  
    while (randNumber != userNumber)
    {
        if (userNumber > randNumber)
        {
            std::cout << "My number is less! Try again! \n";
        }
        else 
        {
            std::cout << "My number is greater! Try again! \n";
        }
        tries++;
        std::cin >> userNumber;
    } 
    
    std::cout << "You win! ";

    if (tries > bestTries)
    {
        std::cout << "The number of your attempts is " << tries << ". It can be better!";
    }
    
}