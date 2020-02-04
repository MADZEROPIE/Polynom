#include <iostream>
#include "polynom.h"


int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");
	Polynom a;
	Polynom b("10x3y4z5+5z1");
	Polynom c("x3");
	
	a=b*c;
	//b.clear();
	//Polynom::Monom a,b;
	
	std::cout << a.ToString()<<'\n';//, "x2 - y2 + z2";
	std::cout << c.ToString();// "y2";
	
	return 0;
}

