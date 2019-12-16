#include <iostream>
#include "polynom.h"


int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");
	Polynom::Monom a(1, 185);
	a.set_deg(1, 0, 0);

	return 0;
}

