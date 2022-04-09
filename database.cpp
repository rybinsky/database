#include "database.h"

using namespace std;

void Database::Add(const Date& date, const string& event) {
	if (events[date].count(event) == 0) {
		events[date].insert(event);
		db_[date].push_back(event);
	}
}

pair<Date, string> Database::Last(Date d) const {
	auto it = db_.upper_bound(d);
	if (it == db_.begin()) {
		throw invalid_argument("");
	}
	it--;

	return make_pair(it->first,it->second.back());

}

map<Date, vector<string>> Database::Base() const {
	return db_;
}

void Database::Print(ostream& out) const {
	map<Date, vector<string>> d = db_;
	for (const auto& i : d) {
		int s = i.second.size();
		vector<string> ev = i.second;
		//sort(begin(ev), end(ev));
		for (int j = 0; j < s; j++) {
			out << setw(4) << setfill('0') << i.first.GetYear() << '-' << setw(2) << setfill('0') <<
				i.first.GetMonth() << '-'
				<< setw(2) << setfill('0') << i.first.GetDay() << ' ' << ev[j] << endl;
		}
	}
}


