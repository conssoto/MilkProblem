#include "Node.h"

Node::Node(int id, int production, int type): id(id), production(production), type(type) {}

Node::~Node(){}


int Node::getId(){ return this->id; }

int Node::getProduction(){ return this->production; }

int Node::getType(){ return this->type; }

int Node::getTypeIndex(){ return this->type - 1; }


bool sortByType(const Node *n1, const Node *n2){ return n1->type < n2->type; }
