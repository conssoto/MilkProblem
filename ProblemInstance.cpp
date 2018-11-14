#include "ProblemInstance.h"

ProblemInstance::ProblemInstance(int totalNodes){
    this->distances = new int *[totalNodes];
    for (int i = 0; i < totalNodes; ++i){
        this->distances[i] = new int[totalNodes];
    }
}

ProblemInstance::~ProblemInstance(){
    cout << "Deleting Problem Instance" << endl;

    for (int i = 0; i < this->getNumberOfNodes(); ++i){
        delete[] this->distances[i];
    }
    delete[] distances;

    for (Truck *truck: this->trucks){
        delete truck;
    }
    trucks.clear();

    for (Node *node: this->nodes){
        delete node;
    }
    nodes.clear();
}


double ProblemInstance::getNumberOfNodes(){ return this->nodes.size(); }

double ProblemInstance::getNumberOfTrucks(){ return this->trucks.size(); }

double ProblemInstance::getNumberOfQualities(){ return this->qualities.size(); }


void ProblemInstance::addNode(Node *node){ this->nodes.push_back(node); }

void ProblemInstance::addTruck(Truck *truck){ this->trucks.push_back(truck); }

void ProblemInstance::addQuality(int quality){ this->qualities.push_back(quality); }


void ProblemInstance::setDistances(int row, int col, int distance) { this->distances[row][col] = distance; }


int ProblemInstance::calculateDistance(Node *initialNode, Node *finalNode){
    return this->distances[initialNode->getId()][finalNode->getId()];
}

void ProblemInstance::printAll(){
    for(double q: this->qualities){
        cout << "quality: " << q << endl;
    }
    for(Node *n: this->nodes){
        cout << " node: " << n->getId() << " type: " << n->getType() << " prod: " << n->getProduction() << endl;
    }
    for(Truck *t: this->trucks){
        cout << "truck: " << t->getId() << endl;
    }
    cout << "distances:" << this->distances[0][0] << endl; //matriz con diagonal de ceros
}

void ProblemInstance::sortNodes(){ sort(nodes.begin(),nodes.end(), sortByType); }
