#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

#include "date.h"

using namespace std;

class Database {
public:
	void Add(const Date& date, const string& event); // добавление события

	template <typename Predicate>
	vector<string> FindIf(Predicate predicate) const { // найти по условию и вернуть вектор событий
		vector<string> res;
		for (const auto& date : db_) {
			for (const auto& event : date.second) {
				if (predicate(date.first, event)) {
					res.push_back(date.first.GetDate() + " " + event);
				}
			}
		}
		return res;
	}

	template <typename Predicate>
	int RemoveIf(Predicate predicate) { // удалить по условию и вернуть сколько удалилось
		int count = 0;
		vector<Date> del_ev;
		for (auto it = db_.begin(); it != db_.end(); it++) {
			auto pos = stable_partition(it->second.begin(), it->second.end(),
				[it, predicate](const string& event) {return !predicate(it->first, event); }
			);
			count += it->second.end() - pos;
			it->second.erase(pos, it->second.end());

			if (it->second.size() > 0) {
				db_[it->first] = it->second;
				events.erase(it->first);
				for (const auto& i : it->second) {
					events[it->first].insert(i);
				}
			}
			else {
				del_ev.push_back(it->first);
			}
		}
		for (const auto& i : del_ev) {
			events.erase(i);
			db_.erase(i);
		}
		return count;
	}

	pair<Date, string> Last(Date d) const; // последние событие до определенной даты

	map<Date, vector<string>> Base() const; // вернуть нашу бабу данных

	void Print(ostream& out) const; // распечатать базу данных

private:
	map<Date, vector<string>> db_; // тут храним события в порядке добавления
	map<Date, set<string>> events; // это чтобы быстро проверять есть ли оперделенное событие в определенную дату
};
