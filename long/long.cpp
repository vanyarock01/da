#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include "TLongNumber.h"



int main(void) {

	const int base = 10000; 
	
	std::string x, y;
	char z;

	while (std::cin >> x >> y >> z) {

		TLongNumber a(x, base);
		TLongNumber b(y, base);

		TLongNumber err("-1", base);

		TLongNumber result;

		bool compare = false;
		bool fin;

		switch(z) {
			case '+':
			{
				result = a + b;
				break;
			}
			case '-':
			{
				result = a - b;
				break;
			}
			case '*':
			{
				result = a * b;
				break;
			}
			case '/':
			{
				result = a / b;
				break;
			}
			case '^':
			{
				result = a ^ b;
				break;
			}
			case '>':
			{
				fin = ( a > b );
				compare = true;
				break;
			}
			case '<':
			{
				fin = ( a < b );
				compare = true;
				break;
			}
			case '=':
			{
				fin = ( a == b );
				compare = true;
				break;
			}
		}

		if (compare) {
			std::cout << (fin ? "true" : "false");
		} else
		if (result == err) {
			std::cout << "Error";
		} else {
			std::cout << result;
		}

		std::cout << std::endl;
	}

	return 0;
}
