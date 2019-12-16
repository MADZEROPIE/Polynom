#include "polynom.h"

Polynom::Polynom(std::string str): Polynom()
{

}

Polynom::~Polynom()
{
	clear();
	delete head;
}

std::string Polynom::ToString()
{
	return std::string();
}

void Polynom::clear()
{
	Node* tmp = head->pNext;
	while (tmp != head) {
		Node* tmp2 = tmp;
		tmp = tmp->pNext;
		delete tmp2;
	}
}

void Polynom::del_zeroes()
{
	Node* tmp = head->pNext;
	while (tmp != head) {
		if (tmp->mon == 0.0) {
			Node* tmp2 = tmp;
			tmp = tmp->pNext;
			delete tmp2;
		}
		else tmp = tmp->pNext;
	}
}

Polynom::Monom Polynom::Monom::operator-()
{
	Monom res(*this);
	res.coef = -res.coef;
	return res;
}

Polynom::Monom Polynom::Monom::operator+(const Monom& b)
{
	if (b.pow_coef != pow_coef) throw b.pow_coef;
	else {
		Monom res(*this);
		res.coef += b.coef;
		return res;
	}
}

Polynom::Monom Polynom::Monom::operator-(const Monom& b)
{
	if (b.pow_coef != pow_coef) throw b.pow_coef;
	else {
		Monom res(*this);
		res.coef += b.coef;
		return res;
	}
}

Polynom::Monom& Polynom::Monom::operator*=(const Monom& b)
{
	if (b.pow_coef % maxp + pow_coef % maxp >= maxp ||
		b.pow_coef / maxp % maxp + pow_coef / maxp % maxp >= maxp ||
		b.pow_coef / maxp / maxp % maxp + pow_coef / maxp / maxp % maxp >= maxp)
			throw 1;
	pow_coef += b.pow_coef;
	coef*=b.coef;
	return *this;
}

std::vector<int> Polynom::Monom::get_deg()
{
	return std::vector<int>();
}

int Polynom::Monom::set_deg(int a, int b, int c)
{
	pow_coef = a * maxp * maxp + b * maxp + c;
	return pow_coef;
}

std::string Polynom::Monom::ToString()
{
	return std::string();
}
