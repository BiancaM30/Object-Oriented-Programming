#pragma once
#include "Task.h"
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
class TaskValidator
{
public:
	/*
	* Valideaza taskul dat
	* param: p(Task)
	* arunca ValidateException daca task este invalid
	*/
	void validate(const Task& t);
};

