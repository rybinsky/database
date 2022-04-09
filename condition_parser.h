#pragma once

#include "node.h"

#include <memory>
#include <iostream>

using namespace std;

class Node;

shared_ptr<Node> ParseCondition(istream& is);