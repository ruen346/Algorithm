#include<iostream>
using namespace std;

int main()
{
	int num, w10000, w5000, w1000, w500, w100, w50, w10;

	cout << "���Է� : ";
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
	
	cout << "���� : " << w10000 << endl;
	cout << "��õ�� : " << w5000 << endl;
	cout << "õ�� : " << w1000 << endl;
	cout << "����� : " << w500 << endl;
	cout << "��� : " << w100 << endl;
	cout << "���ʿ� : " << w50 << endl;
	cout << "�ʿ� : " << w10 << endl;

	return 0;
}