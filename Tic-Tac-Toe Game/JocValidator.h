#pragma once
#include "Joc.h"
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

class JocValidator
{
public:
	/*
	* Valideaza jocul dat
	* param: j(Joc)
	* arunca ValidateException daca jocul este invalid
	*/
	void validate(const Joc& j);
};

