#include<iostream>
#include<math.h>
using namespace std;

void mergesort(int A[], int p, int q)//병합정렬
{
	if (abs(p - q)>1)
	{
		int k = (p + q) / 2;
		mergesort(A, p, k);
		mergesort(A, k + 1, q);
		int star1 = p;
		int star2 = k + 1;
		int z = 0;
		int B[100];
		for (int i = p; i <= q; i++)
		{
			if (z == 1)
			{
				B[i] = A[star2];
				star2++;
			}
			else if (z == 2)
			{
				B[i] = A[star1];
				star1++;
			}
			else if (A[star1] < A[star2])
			{
				B[i] = A[star1];
				star1++;
				if (star1 > k)
					z = 1;
			}
			else
			{
				B[i] = A[star2];
				star2++;
				if (star2 > q)
					z = 2;
			}
		}
		for (int i = p; i <= q; i++)
		{
			A[i] = B[i];
		}
	}
}

int main(void)
{
	int A[100];
	int num;
	cout << "입력할 숫자의 갯수를 입력하세요 : ";
	cin >> num;
	cout << "숫자를 입력하세요 : ";
	for (int i = 0; i < num; i++)
	{
		cin >> A[i];
	}
	mergesort(A, 0, num - 1);
	for (int i = 0; i < num; i++)
	{
		cout << A[i] << " ";
	}
	return 0;
}