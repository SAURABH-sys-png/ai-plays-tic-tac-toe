#include "Print.hpp"

void printBoard(int arr[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << " | " << arr[i][j];
		}
		std::cout << " | " << '\n';
	}
}
