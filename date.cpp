#include "date.h"

using namespace std;

Date::Date(int a, int b, int c) {
	year = a;

	if (b <= 0 || b >= 13) {
		throw invalid_argument("Month value is invalid: " + to_string(b));
	}
	month = b;
	if (c <= 0 || c >= 32) {
		throw invalid_argument("Day value is invalid: " + to_string(c));
	}
	day = c;
}

int Date::GetYear() const {
	return year;
};
int Date::GetMonth() const {
	return month;
};
int Date::GetDay() const {
	return day;
};

string Date::GetDate() const {
	stringstream s;
	s << setfill('0');
	if (year < 0) {
		s << '-';
	}
	s << setw(4) << abs(year);
	s << '-';
	s << std::setw(2) << month;
	s << '-';
	s << std::setw(2) << day;
	return s.str();
}

ostream& operator<<(ostream& out, const Date& d) {
	out << setw(4) << setfill('0') << d.GetYear() << '-' << setw(2) << setfill('0') <<
		d.GetMonth() << '-'
		<< setw(2) << setfill('0') << d.GetDay();
	return out;
}

Date ParseDate(istream& in) {

	int y, m, d;
	bool f = 1;
	f = f && (in >> y);
	f = f && (in.peek() == '-');
	in.ignore(1);
	f = f && (in >> m);
	f = f && (in.peek() == '-');
	in.ignore(1);
	f = f && (in >> d);

	if (f) {
		return { y,m,d };
	}
	else {
		throw invalid_argument("Wrong date format");
	}
}

bool operator<(const Date& lhs, const Date& rhs) {
	auto lhs_ = make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay());
	auto rhs_ = make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
	return lhs_ < rhs_;
}
bool operator<=(const Date& lhs, const Date& rhs) {
	auto lhs_ = make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay());
	auto rhs_ = make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
	return lhs_ <= rhs_;
}
bool operator>(const Date& lhs, const Date& rhs) {
	auto lhs_ = make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay());
	auto rhs_ = make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
	return lhs_ > rhs_;
}
bool operator>=(const Date& lhs, const Date& rhs) {
	auto lhs_ = make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay());
	auto rhs_ = make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
	return lhs_ >= rhs_;
}
bool operator==(const Date& lhs, const Date& rhs) {
	auto lhs_ = make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay());
	auto rhs_ = make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
	return lhs_ == rhs_;
}
bool operator!=(const Date& lhs, const Date& rhs) {
	auto lhs_ = make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay());
	auto rhs_ = make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
	return lhs_ != rhs_;
}

