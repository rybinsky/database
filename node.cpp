#include "node.h"

using namespace std;

bool EmptyNode::Evaluate(const Date& d, const string& ev) { return true; }

DateComparisonNode::DateComparisonNode(const Comparison& op, const Date& d) :op_(op), d_(d) {}

bool DateComparisonNode::Evaluate(const Date& d, const string& ev) {
	return Comp(op_, d, d_);
}


EventComparisonNode::EventComparisonNode(const Comparison& op, const string& ev) :op_(op), ev_(ev) {}

bool EventComparisonNode::Evaluate(const Date& d, const string& ev) {
	if (ev.empty()) {
		return 0;
	}
	return Comp(op_, ev, ev_);
}


LogicalOperationNode::LogicalOperationNode(const LogicalOperation& op,
	const shared_ptr<Node>& left, const shared_ptr<Node>& right)
	: op_(op), left_(left), right_(right) {}

		bool LogicalOperationNode::Evaluate(const Date& d, const string& ev) {
			if (op_ == LogicalOperation::And) {
				return left_->Evaluate(d, ev) && right_->Evaluate(d, ev);
			}
			if (op_ == LogicalOperation::Or) {
				return left_->Evaluate(d, ev) || right_->Evaluate(d, ev);
			}
			return 0;
		}

		void LogicalOperationNode::SetLeft(shared_ptr<Node> node) { left_ = node; }
		void LogicalOperationNode::SetRight(shared_ptr<Node> node) { right_ = node; }


