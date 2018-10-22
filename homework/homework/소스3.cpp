#include <iostream>
#include <time.h>
using namespace std;

int num[10];
int i = -1, j = -1;

void quicksort(int num[], int left, int right)//Äü Á¤·Ä
{
	if (num[left] > num[right])
		j++;
	else
	{
		i++;
		int save = num[left];
		num[left] = num[i];
		num[i] = save;
	}

	left++;

	if(left != right)
		quicksort(num, left, right);
	else
	{
		i++;
		int save = num[left];
		num[left] = num[i];
		num[i] = save;
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

	quicksort(num, 0, 9);

	for (int i = 0; i < 10; i++)
	{
		cout << num[i] << " ";
	}
	cout << endl;

	return 0;
}