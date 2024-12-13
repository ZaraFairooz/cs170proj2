#ifndef FORWARD_BACKWARD_H
#define FORWARD_BACKWARD_H

#include <iostream>
#include <vector>
#include "NN.h"
using namespace std;


struct FeatAndAcc {
    vector<int> selected_features;                                     
    double accuracy;
                                     
    
    void print() const {
        cout << "Using feature(s) {";
        for (int i = 0; i < selected_features.size(); ++i) {
            cout << (selected_features[i] + 1);
            if (i < selected_features.size() - 1) {
                cout << ", ";
            }
        }
        cout << "} accuracy is " << accuracy * 100 << "%" << endl;
    }

    const bool operator <(const FeatAndAcc& rhs) const {     
        return accuracy < rhs.accuracy;
    }
};

void ForwardSelection(NN ds, int size);
void BackwardElimination(NN featureSet, int size);
#endif