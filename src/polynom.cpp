#include "polynom.h"


#pragma region Monom

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

#pragma endregion

#pragma region Polynom

Polynom::Polynom()
{
	head = new Node;
	head->pNext = head;
}

Polynom::Polynom(std::string s)
{
	{
		std::stringstream ss;
		ss << s;
		std::string word, lastword = "+";
		Monom data(-1, 0);
		std::vector<Monom> v;
		while (ss >> word)
		{
			if ((lastword == "+" || lastword == "-") && (word == "+" || word == "-") ||
				(lastword != "+" && lastword != "-") && (word != "+" && word != "-"))
			{
				throw 1;
			}
			else
			{
				if (word != "+" && word != "-")
				{
					Monom a(word);
					if (lastword == "-")
					{
						a = -a;
					}
					v.push_back(a);
				}
				lastword = word;
			}
		}
		std::sort(v.rbegin(), v.rend());
		head = new Node;
		Node* p = head;
		for (size_t i = 0; i < v.size(); ++i)
		{
			if (!(v[i] == p->mon))
			{

				Node* cur = new Node;
				cur->mon = v[i];
				p->pNext = cur;
				p = p->pNext;
			}
			else
			{
				p->mon += v[i];
			}

		}
		p->pNext = head;
		del_zeros();
	}
}

Polynom::Polynom(const Polynom& pol)
{
	head = new Node(pol.head->mon);
	Node* p1 = head;
	Node* p2 = pol.head->pNext;
	while (p2 != pol.head) {
		p1->pNext = new Node(p2->mon, head);
		p2 = p2->pNext;
		p1 = p1->pNext;
	}
	p1->pNext = head;

}

Polynom::~Polynom()
{
	clear();
	delete head;
}

Polynom& Polynom::operator=(const Polynom& pol)
{
	if (head == pol.head) return *this;
	clear();
	Node* p2 = pol.head->pNext;
	Node* p1 = head;
	while (p2 != pol.head) {
		p1->pNext = new Node(p2->mon, head);
		p2 = p2->pNext;
		p1 = p1->pNext;
	}
	return *this;
}

Polynom Polynom::operator+(const Polynom& pol)
{
	Polynom res(*this);
	return res += pol;
}

Polynom Polynom::operator-()
{
	Polynom res(*this);
	Node* tmp = res.head->pNext;
	while (tmp != res.head) {
		tmp->mon = -tmp->mon;
		tmp = tmp->pNext;
	}
	return res;
}

Polynom& Polynom::operator+=(const Polynom& pol)
{
	Polynom b = pol;
	return this->merge(b);
}

Polynom& Polynom::operator-=(Polynom& pol)
{
	return this->merge(-pol);
}

Polynom Polynom::operator-(Polynom& pol)
{
	Polynom res = -pol;
	return res += *this;
}

Polynom Polynom::operator*(Polynom::Monom& mon)
{
	Polynom res(*this);
	Node* p = res.head->pNext;
	while (p != res.head) {
		p->mon *= mon;
		p = p->pNext;
	}
	res.del_zeros();
	return res;
}

Polynom Polynom::operator*(const Polynom& pol)
{
	Polynom res;
	Node* p = pol.head->pNext;
	while (p != pol.head) {
		res.merge((*this) * p->mon);
		p = p->pNext;
	}
	return res;
}

Polynom Polynom::operator*(const real a)
{
	Polynom res(*this);
	Node* tmp = res.head->pNext;
	while (tmp != res.head) {
		tmp->mon *= a;
		tmp = tmp->pNext;
	}
	del_zeros();
	return res;
}

Polynom& Polynom::merge(Polynom& b)
{
	Node* head0 = new Node;
	Node* p1 = head->pNext, * p2 = b.head->pNext, * p0 = head0;
	while (p1 != head || p2 != b.head) {
		if (p1->mon <= p2->mon) {
			if (p2->mon == p0->mon)
			{
				p0->mon += p2->mon;
				Node* tmp = p2;
				p2 = p2->pNext;
				delete tmp;
			}
			else {
				p0->pNext = p2;
				p0 = p2;
				p2 = p2->pNext;
			}
		}
		else {
			if (p1->mon == p0->mon)
			{
				p0->mon += p1->mon;
				Node* tmp = p1;
				p1 = p1->pNext;
				delete tmp;
			}
			else {
				p0->pNext = p1;
				p0 = p1;
				p1 = p1->pNext;
			}
		}
	}
	head = head0;
	p0->pNext = head;
	b.head->pNext = b.head;
	del_zeros();
	return *this;
}

Polynom Polynom::merge(std::vector<Polynom> a)
{
	std::vector<Polynom> b = a;
	while (b.size() > 1)
	{
		a = {};
		for (int i = 0; i < b.size(); i += 2)
		{
			if (i + 1 < b.size())
				a.push_back(b[i].merge(b[i + 1]));
			else
				a.push_back(b[i]);
		}
		b = a;
	}
	return b[0];
	
}

std::string Polynom::ToString()
{
	Node* p = head;
	std::string ans = "";
	if (p->pNext == head)
		return "0";
	if (p->pNext->mon > 0.0)
		ans += p->pNext->mon.ToString();
	else
		ans += "-" + p->pNext->mon.abs().ToString();
	p = p->pNext;
	while (p->pNext != head)
	{
		if (p->pNext->mon < 0.0)
			ans += " - ";
		else
			ans += " + ";
		ans += (p->pNext->mon).abs().ToString();
		p = p->pNext;
	}
	return ans;
}


void Polynom::clear()
{
	Node* tmp = head->pNext;
	while (tmp != head) {
		Node* tmp2 = tmp;
		tmp = tmp->pNext;
		delete tmp2;
	}
	head->pNext = head;
}

void Polynom::del_zeros()
{
	Node* tmp = head;
	while (tmp->pNext != head) {
		if (tmp->pNext->mon == 0.0) {
			Node* tmp2 = tmp->pNext;
			tmp->pNext = tmp->pNext->pNext;
			tmp = tmp->pNext;
			delete tmp2;
		}
		else tmp = tmp->pNext;
	}
}
#pragma endregion