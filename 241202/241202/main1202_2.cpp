#include <iostream>

int main()
{
	int tmp[50];

	for (int i = 0;i < 5;i++) {
		for (int j = 0;j < 10;j++) {
			tmp[i * 10 + j] = i * 10 + j;
			std::cout << tmp[i * 10 + j] << std::endl;
		}
	}
	return 0;
}