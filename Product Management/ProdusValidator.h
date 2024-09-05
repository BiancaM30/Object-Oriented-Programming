#pragma once
#include "Produs.h"
#include <vector>
using std::vector;

class ValidateException {
	vector<string>messages;
public:
	ValidateException(vector<string>messages) : messages{ messages } {};
	const vector<string> getMsg() {
		return messages;
	}
};
class ProdusValidator
{
public:
	/*
	* Valideaza produsul dat 
	* param: p(Produs)
	* arunca ValidateException daca produsul este invalid
	*/
	void validate(const Produs& p);
};

