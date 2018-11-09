#pragma once
#include <iostream>

using namespace std;

class Node
{
public:
    int id;
    int production;
    int type;

public:
    Node(int id, int production, int type);
    ~Node();

    int getId();
    int getProduction();
    int getType();
    int getTypeIndex();

    bool operator==(const Node& node) const{return this->id == node.id;}
    bool operator!=(const Node& node) const{ return !operator==(node);}
};

bool sortByType(const Node *n1, const Node *n2);
