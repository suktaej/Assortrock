#include<iostream>
#include<ctime>
int main()
{
	int ar[25] = {};
	int i = 0, j=0;
	int inp = 0;

	for (int i = 0;i < 25;i++)
		ar[i] = i + 1;

	srand(time(0));

	for (i = 24;i > 0;i--)
	{
		j = rand() % (i + 1);
		std::swap(ar[i], ar[j]);
	}

	int score = 0;

	while(1)
	{
		system("cls");

		for (i = 0;i < 5;i++) 
		{
			for (j = 0;j < 5;j++)
			{
				if(ar[i*5+j]==INT_MAX)
					std::cout << "*\t";
				else
					std::cout << ar[i * 5 + j] << "\t";
			}
			std::cout << std::endl;
		}

		std::cout << "Score:" << score << std::endl;
		score = 0;

		std::cout << "input number:";
		std::cin >> inp;
		
		if (inp == 0)
			break;
		else if (inp < 0 || inp>25)
			continue;
		else
		{
			for (i = 0;i < 25;i++)
			{
				if (inp == INT_MAX)
					continue;
				else if(inp == ar[i])
				{
					ar[i] = INT_MAX;
					break;
				}
			}
		}

		int cnt1, cnt2;


		for (i = 0;i < 5;i++)
		{
			cnt1 = 0;
			cnt2 = 0;
			
			for (j = 0;j < 5;j++)
			{
				if (ar[i * 5 + j] == INT_MAX)	cnt1++;
				if (ar[j * 5 + i] == INT_MAX)	cnt2++;
			}
			if (cnt1 == 5) score++;
			if (cnt2 == 5) score++;
		}

		cnt1 = 0;
		for (i = 0;i < 25;i += 6)
		{
			if (ar[i] == INT_MAX) cnt1++;
		}
		if (cnt1 == 5) score++;
		
		cnt1 = 0;
		for (i = 4;i <= 20;i += 4)
		{
			if (ar[i] == INT_MAX) cnt1++;
		}
		if (cnt1 == 5) score++;
	}

	return 0;
}