#pragma once
#include <iostream>
#include<map>
#include<set>
#include<string>

using namespace std;

class Calculate {  //Class made specifcally for operator overloading.  The way my operations were done in the main program might have been easier without this, but I couldn't get overloading done otherwise.
private:
	long number;
public:
	Calculate(long number) {
		this->number = number;
	}
	long getNumber() {
		return number;
	}
	string toString() {
		return to_string(number);
	}
	Calculate operator=(Calculate other) {
		number = other.getNumber();
	}
	Calculate operator+(Calculate other) {
		return Calculate(number + other.getNumber());
	}
	Calculate operator-(Calculate other) {
		return Calculate(number - other.getNumber());
	}
};