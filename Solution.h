#pragma once
#include <vector>
#include "Truck.h"
#include "Node.h"
#include "ProblemInstance.h"
#include "Route.h"
#include <iostream>
#include <numeric>

using namespace std;

class Solution {
public:
    double distance;
    vector<int> recollected; //x type

    Node * plant;
    vector<int> unsatisfiedDemand;
    vector<Truck *> unusedTrucks;
    vector<Node *> unvisitedNodes;

    vector<int> nodesXQuality;

    ProblemInstance *problemInstance; // TODO que paso aqui :D

    vector<Route *> routes;

    vector<double> literCost;
    double kilometerCost;

public:
    explicit Solution(ProblemInstance *problemInstance);
    ~Solution();

    void updateSolution(Trip *trip, Route *route);
    void decreaseDemand(int position, int production);
    void updateDemands(int position, Trip *trip, int production, Route *route);
    void updateDistance(int distance);

    void setQualities(double size);
    void setRecollected(double size);
    void setUnusedTrucks(vector<Truck *> trucks);
    void setUnvisitedNodes(vector<Node *> nodes);

    void addTruck(Truck *truck);
    void addNode(Node *node);
    void addRoute(int type);
    void addTrip(Trip *trip, Route *route);

    Trip *newTrip(Node *node1, Node *node2);
    Trip *fakeTrip(Node *node1, Node *node2, Node *node3, int routeId);


    vector<Route *> getUnfilledRoutes();
    int getUnsatisfiedType();
    Node *getCurrentNode();
    Truck *getNextTruck();

    void removeTruck(Truck *truck);
    void removeNode(Node *node);

    void printAll();
    void printRoute();

    double calculateBenefit(Trip *trip);
};