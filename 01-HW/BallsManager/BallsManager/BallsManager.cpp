#include <iostream>

const int NUM_BALLS = 20; // массив из 20 ячеек для мячей

int main()
{
	int balls[NUM_BALLS]; // длина массива

	for (int& ball : balls)
	{
		ball = 0; // в каждую ячейку поместили 0 мячей
	}

	bool shouldContinue = true;
//	int currentBalls = 0; //использовать balls
	while (shouldContinue)
	{
		std::cout << "List of commands" << std::endl;
        std::cout << "1 - Add ball" << std::endl;
        std::cout << "2 - Remove ball" << std::endl;
        std::cout << "3 - Count balls" << std::endl;
        std::cout << "4 - Total balls" << std::endl;
        std::cout << "5 - Needed balls" << std::endl;
		std::cout << "6 - Move balls" << std::endl;
		std::cout << "7 - Clear article" << std::endl;
		std::cout << "0 - Exit" << std::endl;

		std::string command;
		std::cin >> command;

		if (command == "1")
		{
			// спросить номер артикула, можно вывести от 1 до NUM_BALLS, после выбора спросить сколько мячей нужно добавить, после ввода нужно по артиклу (по идексу массива) положить количество введенных мячей в эту ячейку и вывести столько-то добавлено, столько-то лежит
			
			std::cout << "Enter article: " << std::endl;
			int article = -1;
			std::cin >> article;
			
			if (article < 0 || article > NUM_BALLS - 1)
			{
				std::cout << "Incorrect article" << std::endl;
				continue;
			}

			std::cout << "Enter count balls for adding: ";
			int countBalls = 0;
			std::cin >> countBalls;
			
			if (countBalls <= 0)
			{
				std::cout << "Incorrect count" << std::endl;
				continue;
			}
			balls[article] += countBalls;
			std::cout << "You added " << countBalls << " balls in " << article << " article" << std::endl;
			std::cout << "Total balls is " << balls[article] << std::endl;

		}
		else if (command == "2") 
		{
			// спрашиваем номер артикула, показываем сколько хранится мячей, предлагаем ввести количество вытаскиваемых мячей, показываем ошибку, если задано больше чем есть, после удаления показываем сколько удалено, сколько осталось

			std::cout << "Enter article: " << std::endl;
			int article = -1;
			std::cin >> article;

			if (article < 0 || article > NUM_BALLS - 1)
			{
				std::cout << "Incorrect article" << std::endl;
				continue;
			}
			
			if (balls[article] == 0)
			{
				std::cout << "The article is empty" << std::endl;
				continue;
			}

			std::cout << "The article is has a " << balls[article] << " balls" << std::endl;
			std::cout << "Enter count balls for removing: ";
			int countBalls = 0;
			std::cin >> countBalls;
			
			if (countBalls <= 0)
			{
				std::cout << "You can input only positive integer " << std::endl;
				continue;
			}
			if (countBalls > balls[article])
			{
				std::cout << "You can remove only " << balls[article] << std::endl;
				continue;
			}
			
			balls[article] -= countBalls;
			std::cout << "Your remove " << countBalls << " from article "  << article << std::endl;
			std::cout << "The article has " << balls[article] << std::endl;
		}
		else if (command == "3")
		{
			std::cout << "Enter article: ";
			int article = -1;
			std::cin >> article;
			if (article < 0 || article > NUM_BALLS - 1)
			{
				std::cout << "Incorrect article" << std::endl;
			}
			else
			{
				std::cout << "They are " << balls[article] << " balls of article " << article << std::endl;
			}
		}
		else if (command == "4")
		{
			// выводить общее число мячей по всем артикулам

			int totalBalls = 0;
			for (int i = 0; i < NUM_BALLS; i++)
			{
				totalBalls += balls[i];
			}
			std::cout << "Total balls is " << totalBalls << std::endl;
				
		}
		else if (command == "5")
		{
			for (int i = 0; i < NUM_BALLS; i++)
			{
				if (balls[i] == 0)
				{
					std::cout << "There are no balls of article " << i << std::endl;
				}
			}
		}
		else if (command == "6") 
		{
			// выбираем артикул и показываем количество мячей в нем, предлагаем сумму перевода и выбираем в какой артрикул переместить

			std::cout << "Enter article from move: " << std::endl;
			int articleFrom = -1;
			std::cin >> articleFrom;

			if (articleFrom < 0 || articleFrom > NUM_BALLS - 1)
			{
				std::cout << "Incorrect article" << std::endl;
				continue;
			}

			if (balls[articleFrom] == 0)
			{
				std::cout << "The article is empty" << std::endl;
				continue;
			}
			
			std::cout << "You have chosen is " << articleFrom << " article." << " Article has a " << balls[articleFrom] << " balls." << " How count balls you want to move: " << std::endl;
			int countBalls;
			std::cin >> countBalls;
			if (countBalls <= 0)
			{
				std::cout << "You can insert only positive integer";
				continue;
			}
			if (countBalls > balls[articleFrom])
			{
				std::cout << "Incorrect count balls" << " Article has a " << balls[articleFrom] << std::endl;
				continue;
			}
			std::cout << "Which article do you want to put the balls in?" << std::endl;
			int articleTo = -1;
			std::cin >> articleTo;
			if (articleTo < 0 || articleTo > NUM_BALLS - 1)
			{
				std::cout << "Incorrect article" << std::endl;
				continue;
			}
			balls[articleFrom] -= countBalls;
			balls[articleTo] += countBalls;
			std::cout << "You are moving " << countBalls << " to article " << articleTo << std::endl;
			std::cout << "Now article " << articleFrom << " has a " << balls[articleFrom] << " and " << articleTo << " has a " << balls[articleTo] << std::endl;

		}
		else if (command == "7")
		{
			// выбираем артикул и происходит очистка мячей

			std::cout << "Enter article: " << std::endl;
			int article = -1;
			std::cin >> article;

			if (article < 0 || article > NUM_BALLS - 1)
			{
				std::cout << "Incorrect article" << std::endl;
				continue;
			}

			if (balls[article] == 0)
			{
				std::cout << "The article is already empty" << std::endl;
				continue;
			}
			int ballsToRemoving = balls[article];
			balls[article] = 0;
			std::cout << "The article is empty now, removing are " << ballsToRemoving << std::endl;
		}
		else if (command == "0")
		{
			std::cout << "Bye!" << std::endl;
			break;

		}
		else {
			std::cout << "Unknown operation!" << std::endl;
		}
	}
}