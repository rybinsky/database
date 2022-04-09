#pragma once

#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <tuple>

using namespace std;

class Date {
public:

	Date(int a, int b, int c);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

	string GetDate() const;

private:
	int year;
	int month;
	int day;
};

ostream& operator<<(ostream& out, const Date& d);

Date ParseDate(istream& in);

bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);