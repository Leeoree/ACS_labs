#include <stdlib.h>
#include <iostream>

using namespace std;

void From_ASCII_to_numeral(unsigned int x)
{
	int num_x;
	asm("movl %1, %0\n"
		"andl $0xF, %0\n"
		:"+rm"(num_x)
		:"g"(x)
		:"cc"
	);
	cout << "0x" << hex << x << "->" << "0x"<< hex << num_x << endl;
}

void From_numeral_to_ASCII(unsigned int num_x)
{
	int x;
	asm("movl %1, %0\n"
		"xorl $0x30, %0\n"
		:"+rm"(x)
		: "g"(num_x)
		: "cc"
	);
	cout << "0x" << hex << num_x << "->" << "0x" << hex << x << endl;
}

void From_lowercase_to_uppercase(char low)
{
	char upper;
	asm("mov %1, %0\n"
		"and $0xDF, %0\n"
		:"+rm"(upper)
		: "g"(low)
		: "cc"
	);
	cout << low << "->" << upper << endl;
}

int main()
{
	cout << endl << "From ASCII to numeral: " << endl;

	From_ASCII_to_numeral(0x30);
	From_ASCII_to_numeral(0x31);
	From_ASCII_to_numeral(0x32);
	From_ASCII_to_numeral(0x33);
	From_ASCII_to_numeral(0x34);
	From_ASCII_to_numeral(0x35);
	From_ASCII_to_numeral(0x36);
	From_ASCII_to_numeral(0x37);
	From_ASCII_to_numeral(0x38);
	From_ASCII_to_numeral(0x39);

	cout << endl << "From numeral to ASCII: " << endl;

	From_numeral_to_ASCII(0);
	From_numeral_to_ASCII(1);
	From_numeral_to_ASCII(2);
	From_numeral_to_ASCII(3);
	From_numeral_to_ASCII(4);
	From_numeral_to_ASCII(5);
	From_numeral_to_ASCII(6);
	From_numeral_to_ASCII(7);
	From_numeral_to_ASCII(8);
	From_numeral_to_ASCII(9);

	cout << endl << "From lowercase to uppercase: " << endl;

	char x = 0x61;
	for (int i = 0; i < 26; i++)
	{
		From_lowercase_to_uppercase(x);
		x++;
	}

	return 0;
}
