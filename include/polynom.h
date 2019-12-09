#pragma once

#include "List.h"
#include <cstdint>

typedef double real;

//������� - ��� ��������� ���������� ���� 10x3y4z5+5z ==10*(x^3)*(y^4)*(z^5)+5*z

class Polynom{

private:

	class Monom {
	public:
		real coef;
		uint32_t pow_coef;
		Monom(real _coef = 0.0, uint32_t _pow_coef = 0) {
			coef = _coef;
			pow_coef = _pow_coef;
		}
		bool operator<(const Monom& b) {
			//if(pow_coef==b.pow_coef) return coef < b.coef;
			return pow_coef < b.pow_coef; //���� ���������� ������ �������
		}
		bool operator==(const Monom& b){
			return pow_coef == b.pow_coef; //���� ���������� ������ �������
		}
	};

public:
	List<Monom> lis;
	Polynom() {
		lis.push_front(Monom());
	}
	Polynom(std::string str) {
		
	}
	Polynom(const Polynom& pol) {
		lis = pol.lis;//���� �������� �������� =
	}
	Polynom& operator= (const Polynom& pol) {
		return *this;
	}
	Polynom operator+(const Polynom& pol) {
		Polynom res(*this);
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
};