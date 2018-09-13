#include <iostream>
#include <time.h>
using namespace std;

int num[10];

void quicksort(int num[], int left, int right, int choose)
{
	int save = num[choose];
	num[choose] = num[right];
	num[right] = save;

	int j = left;
	for (int i = left; i < right; i++)
	{
		if (num[i] < num[right])
		{
			int save = num[i];
			num[i] = num[j];
			num[j] = save;
			j++;
		}
	}
	save = num[right];
	num[right] = num[j];
	num[j] = save;

	for (int i = left; i <= right; i++)
	{
		cout << num[i] << " ";
	}
	cout << endl;
	cout << "left : " << left << " right : " << right << " j = " << j << endl;

	if (choose <= 1)
	{
		cout << num[right] << "인가?" << endl;
	}
	else
	{
		if (choose < j)
			quicksort(num, left, j, choose);
		else
			quicksort(num, j, right, choose - j);

	}
}

int main()
{
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		num[i] = rand() % 100;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << num[i] << " ";
	}
	cout << endl;

	int choose;
	cout << "몇번째 구하실? : ";
	cin >> choose;

	quicksort(num, 0, 9, choose);

	for (int i = 0; i < 10; i++)
	{
		cout << num[i] << " ";
	}

	cout << endl;

	return 0;
}