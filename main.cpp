#include <iostream>
#include "Reader.h"
#include "Truck.h"
#include "Node.h"
#include "Solution.h"
#include "Construction.h"

using namespace std;

int main() {

    char instanceOption[3];

//    cout << "Enter instance number: ";
//    cin.getline(instanceOption, 3);
//    srand(4);
    ProblemInstance *problemInstance;

//    Reader r(instanceOption);
    Reader r("2");
    problemInstance = r.readInputFile();

    auto *solution = new Solution(problemInstance);
    auto *construction = new Construction(5);

    construction->feasibleSolution(solution);
    delete solution;

//    construction->feasibleSolution(solution, problemInstance);
//
//    cout << "Distance cost: " << solution->kilometerCost *  solution->distance << endl;
//
//    cout << "Milk cost: " << endl;
//    double suma(0);
//    for(int i = 0; i < solution->recollected.size(); ++i){
//        suma +=solution->recollected[i] * solution->literCost[i];
//        cout << solution->recollected[i] * solution->literCost[i] << endl;
//    }
//    cout << "Total Milk cost: " << suma << endl;

    return 0;
}