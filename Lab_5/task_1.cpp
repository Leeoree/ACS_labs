#include <stdlib.h>
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	float af1 = 123456789, bf1 = 123456788, af2 = 123456788, bf2 = 123456787, rf1, rf2;
	double ad1 = 123456789, bd1 = 123456788, ad2 = 123456788, bd2 = 123456787, rd1, rd2;

	rf1 = af1 + bf1;
	rf2 = af2 + bf2;
	rd1 = ad1 + bd1;
	rd2 = ad2 + bd2;

	cout << setprecision(9);

	//��� ������ � ��������� ������� ��������� �������� �������� 6 �������� ����, 7-�� � ������������, ��������� ����� ��������
	cout << "Type float:\n" << af1 << " + " << bf1 << " = " << rf1 << endl 
		<< af2 << " + " << bf2 << " = " << rf2 << endl << endl;  
	//��� ������ � ��������� ������� ������� �������� �������� 15 �������� ����, 16-�� � ������������, ��������� ����� ��������
	cout << "Type double:\n" << ad1 << " + " << bd1 << " = " << rd1 << endl 
		<< ad2 << " + " << bd2 << " = " << rd2 << endl << endl;
}