#include <iostream>
#include "polynom.h"


int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");
	Polynom a;
	Polynom b("10x3y4z5");
	Polynom c("x3");
	
	a=b*c;

	std::cout << a.ToString()<<'\n';
	std::cout << c.ToString();
	
	return 0;
}

