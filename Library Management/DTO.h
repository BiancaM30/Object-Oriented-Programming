#pragma once
#include <string>

using std::string;

class DTO {
private:
	string gen;
	int count;
public:
	DTO() : gen{ "" }, count{ 0 }{}
	DTO(string gen) : gen{ gen }, count{ 1 }{}
	void addCount() noexcept {
		count++;
	}
	const string getGen() const;
	const int getCount() const noexcept;
};