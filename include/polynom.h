#pragma once

#include <cstdint>
#include <string>
#include <vector>

typedef double real;

#define maxp 1000
//Полином - это выражение следующего вида 10x3y4z5+5z == 10*(x^3)*(y^4)*(z^5)+5*z

class Polynom{

public:

	class Monom {
	public:
		real coef;
		int32_t pow_coef;


		Monom(real _coef = 0.0, int32_t _pow_coef = -1) {
			coef = _coef;
			pow_coef = _pow_coef;
		}

		Monom( int a,int b, int c, real _coef = 0.0) {
			coef = _coef;
			pow_coef = a * maxp * maxp + b * maxp + c;
		}

		bool operator<(const Monom& b) {
			//if(pow_coef==b.pow_coef) return coef < b.coef;
			return pow_coef < b.pow_coef; //Надо сравнивать только степени
		}

		bool operator==(const real a) {
			return coef == a;
		}

		bool operator==(const Monom& b){
			return pow_coef == b.pow_coef; //Надо сравнивать только степени
		}
		Monom operator-();
		Monom operator+(const Monom& b);
		Monom operator-(const Monom& b);
		Monom& operator*=(const Monom& b);

		std::vector<int> get_deg();
		int set_deg(int a, int b, int c);

		std::string ToString();
	};

public:
	class Node
	{
	public:
		Node* pNext;
		Monom mon;
		Node(Monom mon = Monom(), Node* pNext = nullptr) {
			this->mon = mon;
			this->pNext = pNext;
		}
	};

private:
	Node* head;

public:

	Polynom() {
		head = new Node;
		head->pNext = head;
	}

	Polynom(std::string str);

	Polynom(const Polynom& pol) {
		head = new Node(pol.head->mon);
		Node* p1 = head;
		Node* p2 = pol.head->pNext;
		while (p2 != pol.head) {
			p1->pNext = new Node(p2->mon,head);
			p2 = p2->pNext;
			p1 = p1->pNext;
		}
		
	}
	~Polynom();

	Polynom& operator=(const Polynom& pol) {
		if(head==pol.head) return *this;
		clear();
		Node* p2 = pol.head->pNext;
		Node* p1 = head;
		while (p2 != pol.head) {
			p1->pNext = new Node(p2->mon,head);
			p2 = p2->pNext;
			p1 = p1->pNext;
		}
		return *this;
	}

	Polynom operator+(const Polynom& pol) {
		Polynom res(*this);
		return res;
	}

	Polynom operator-() {
		Polynom res(*this);
		Node* tmp = res.head->pNext;
		while (tmp != res.head) {
			tmp->mon = - tmp->mon;
		}
		return res;
	}

	Polynom operator-(const Polynom& pol) {
		Polynom res(*this);
		return res;
	}

	Polynom operator*(const Polynom& pol) {
		Polynom res(*this);
		return res;
	}

	Polynom operator*(const real a) {
		Polynom res(*this);
		return res;
	}
	
	std::string ToString();

	void clear();

	void del_zeroes();
};