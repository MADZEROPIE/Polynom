#include "polynom.h"

Polynom::Monom::Monom(real _coef, int32_t _pow_coef)
{
	coef = _coef;
	pow_coef = _pow_coef;
}

Polynom::Monom::Monom(int a, int b, int c, real _coef)
{
	coef = _coef;
	pow_coef = a * maxp * maxp + b * maxp + c;
}

std::pair<int, std::string::iterator>  getFirstNumber(std::string::iterator a, std::string::iterator b) {
	std::string s = "0123456789";
	bool ok = false;
	int k = 1;
	for (; a != b && s.find(*a) != std::string::npos; ++a)
	{
		if (!ok)
		{
			ok = true;
			k = 0;
		}
		k = 10 * k - '0' + *a;
	}
	if (!ok && a != b)
		return std::pair<int, std::string::iterator>(k, a++);
	return std::pair<int, std::string::iterator>(k, a);
}

Polynom::Monom::Monom(std::string s)
{
	int a = 0, b = 0, c = 0;
	std::pair<int, std::string::iterator> pr = getFirstNumber(s.begin(), s.end());
	coef = pr.first;
	for (std::string::iterator it = pr.second; it != s.end();)
	{
		if (*it == 'x' || *it == 'X')
		{
			std::pair<int, std::string::iterator> p = getFirstNumber(it + 1, s.end());
			a += p.first;
			it = p.second;
		}
		else if (*it == 'y' || *it == 'Y')
		{
			std::pair<int, std::string::iterator> p = getFirstNumber(it + 1, s.end());
			b += p.first;
			it = p.second;
		}
		else if (*it == 'z' || *it == 'Z')
		{
			std::pair<int, std::string::iterator> p = getFirstNumber(it + 1, s.end());
			c += p.first;
			it = p.second;
		}
		else
			throw 1;
	}
	set_deg(a, b, c);
}

bool Polynom::Monom::operator<(const Monom& b)
{
	return pow_coef < b.pow_coef; //Надо сравнивать только степени
}

bool Polynom::Monom::operator<=(const Monom& b)
{
	return pow_coef <= b.pow_coef; //Надо сравнивать только степени
}

bool Polynom::Monom::operator==(const real a)
{
	return coef == a;
}

bool Polynom::Monom::operator>(const real a)
{
	return coef > a;
}

bool Polynom::Monom::operator<(const real a)
{
	return coef < a;
}

bool Polynom::Monom::operator==(Polynom::Monom b)
{
	return pow_coef == b.pow_coef; //Надо сравнивать только степени
}

Polynom::Monom Polynom::Monom::operator-()
{
	Monom res(*this);
	res.coef = -res.coef;
	return res;
}

Polynom::Monom Polynom::Monom::abs()
{
	Monom res(*this);
	if (res.coef < 0.0) res.coef = -res.coef;
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

Polynom::Monom& Polynom::Monom::operator+=(const Polynom::Monom& b)
{
	if (b.pow_coef != pow_coef) throw b.pow_coef;
	else coef += b.coef;
	return *this;
}

Polynom::Monom Polynom::Monom::operator-(const Monom& b)
{
	if (b.pow_coef != pow_coef) throw b.pow_coef;
	else {
		Monom res(*this);
		res.coef -= b.coef;
		return res;
	}
}

Polynom::Monom& Polynom::Monom::operator-=(const Polynom::Monom& b)
{
	if (b.pow_coef != pow_coef) throw b.pow_coef;
	else coef -= b.coef;
	return *this;
}

Polynom::Monom& Polynom::Monom::operator*=(const Monom& b)
{
	if (b.pow_coef % maxp + pow_coef % maxp >= maxp ||
		b.pow_coef / maxp % maxp + pow_coef / maxp % maxp >= maxp ||
		b.pow_coef / maxp / maxp % maxp + pow_coef / maxp / maxp % maxp >= maxp)
		throw 1;
	pow_coef += b.pow_coef;
	coef *= b.coef;
	return *this;
}

std::vector<int> Polynom::Monom::get_deg()
{
	std::vector<int> res;
	res.push_back(pow_coef / maxp / maxp % maxp);
	res.push_back(pow_coef / maxp % maxp);
	res.push_back(pow_coef % maxp);
	return res;
}

int Polynom::Monom::set_deg(int a, int b, int c)
{
	pow_coef = a * maxp * maxp + b * maxp + c;
	return pow_coef;
}

std::string Polynom::Monom::ToString()
{
	std::vector<int> kof = get_deg();
	std::stringstream ans;
	ans << "";
	std::string vars = "xyz";
	if (coef == 0)
		return ans.str();
	std::stringstream out;
	if (coef != 1)
	{
		out << coef;
		ans << out.str();
	}
	for (size_t i = 0; i < 3; ++i)
	{
		if (kof[i] != 0)
		{
			if (kof[i] == 1)
			{
				ans << vars[i];
			}
			else
			{
				ans << vars[i];
				ans << kof[i];
			}
		}
	}
	return ans.str();
}