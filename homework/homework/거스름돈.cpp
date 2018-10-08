#include<iostream>
using namespace std;

int main()
{
	int num, w10000, w5000, w1000, w500, w100, w50, w10;

	cout << "돈입력 : ";
	cin >> num;
	
	w10000 = num / 10000;
	num -= w10000 * 10000;
	w5000 = num / 5000;
	num -= w5000 * 5000;
	w1000 = num / 1000;
	num -= w1000 * 1000;
	w500 = num / 500;
	num -= w500 * 500;
	w100 = num / 100;
	num -= w100 * 100;
	w50 = num / 50;
	num -= w50 * 50;
	w10 = num / 10;
	num -= w10 * 10;
	
	cout << "만원 : " << w10000 << endl;
	cout << "오천원 : " << w5000 << endl;
	cout << "천원 : " << w1000 << endl;
	cout << "오백원 : " << w500 << endl;
	cout << "백원 : " << w100 << endl;
	cout << "오십원 : " << w50 << endl;
	cout << "십원 : " << w10 << endl;

	return 0;
}