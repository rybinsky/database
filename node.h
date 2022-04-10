#pragma once

#include <string>
#include <memory>
#include "date.h"
#include "condition_parser.h"

using namespace std;

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
};

enum class LogicalOperation {
	Or,
	And,
};


template <typename T>
bool Comp(const Comparison& op, const T& a, const T& b) {
	if (op == Comparison::GreaterOrEqual) {
		return a >= b;
	}
	if (op == Comparison::Greater) {
		return a > b;
	}
	if (op == Comparison::Equal) {
		return a == b;
	}
	if (op == Comparison::Less) {
		return a < b;
	}
	if (op == Comparison::LessOrEqual) {
		return a <= b;
	}
	if (op == Comparison::NotEqual) {
		return a != b;
	}
	return 0;
}

class Node { // базовый класс звено
public:
	virtual bool Evaluate(const Date& d, const string& ev) = 0;
};

class EmptyNode :public Node { // пустое звено
public:
	bool Evaluate(const Date& d, const string& ev);
};

class DateComparisonNode :public Node { // звено сравнения дат
public:
	DateComparisonNode(const Comparison& op, const Date& d);

	bool Evaluate(const Date& d, const string& ev);

private:
	const Comparison op_;
	Date d_;
};

class EventComparisonNode :public Node { // звено сравнения событий
public:
	EventComparisonNode(const Comparison& op, const string& ev);

	bool Evaluate(const Date& d, const string& ev);

private:
	const Comparison op_;
	string ev_;

};

class LogicalOperationNode :public Node { // логическое звено
public:
	LogicalOperationNode(const LogicalOperation& op, const shared_ptr<Node>& left,
		const shared_ptr<Node>& right);
	bool Evaluate(const Date& d, const string& ev);

	void SetLeft(shared_ptr<Node> node);
	void SetRight(shared_ptr<Node> node);

private:
	LogicalOperation op_;
	shared_ptr<Node> left_, right_;
};
