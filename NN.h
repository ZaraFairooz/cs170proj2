#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <vector>
#include "DataEntry.h"

using namespace std;

class NN
{
    private:
        vector<DataEntry> ds;

    public: 
        NN(const vector<DataEntry>&);
        double Euclidean(const vector<double>&, const vector<double>&, const vector<int>&);
        double Nearest_Neighbor(const vector<int>&);
};
#endif