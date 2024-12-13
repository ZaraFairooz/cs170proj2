#include "DataEntry.h"
#include "NN.h"
#include "forward_backward.h"
#include <set>
#include <queue>
#include <numeric>
#include <iostream>
#include <vector>
#include <algorithm>

void ForwardSelection(NN dataset, int totalFeatures) { //forward feature selection based on dataset
    vector<int> currentFeatures; 
    FeatAndAcc bestOverall;
    bestOverall.accuracy = 0.0;

    for (int level = 0; level < totalFeatures; ++level) {
        FeatAndAcc bestThisLevel;
        bestThisLevel.accuracy = 0.0;
        //feature iteration
        for (int feature = 0; feature < totalFeatures; ++feature) {
            if (find(currentFeatures.begin(), currentFeatures.end(), feature) == currentFeatures.end()) {
                vector<int> candidateFeatures = currentFeatures;
                candidateFeatures.push_back(feature);

                FeatAndAcc candidateSet;
                candidateSet.selected_features = candidateFeatures;
                candidateSet.accuracy = dataset.Nearest_Neighbor(candidateFeatures);

                if (candidateSet.accuracy > bestThisLevel.accuracy) {
                    bestThisLevel = candidateSet;
                }
            }
        }
        //level based best feature selection
        currentFeatures = bestThisLevel.selected_features;

        if (bestThisLevel.accuracy > bestOverall.accuracy) {
            bestOverall = bestThisLevel;
        } else {
            cout << "\nWarning, Accuracy has decreased! Continuing search in case of local maxima)\n" << endl;
        }

        bestThisLevel.print();
    }

    cout << "\nBest feature subset: ";
    bestOverall.print();
}

void BackwardElimination(NN dataset, int totalFeatures) {//backward elim based on dataset
    vector<int> currentFeatures(totalFeatures);
    iota(currentFeatures.begin(), currentFeatures.end(), 0);

    FeatAndAcc bestOverall; //retain best featureset
    bestOverall.accuracy = dataset.Nearest_Neighbor(currentFeatures);
    bestOverall.selected_features = currentFeatures;

    for (int level = 0; level < totalFeatures; ++level) {//compare level best features with curr best
        FeatAndAcc bestThisLevel;
        bestThisLevel.accuracy = 0.0;

        for (int feature : currentFeatures) {
            vector<int> candidateFeatures = currentFeatures;
            candidateFeatures.erase(remove(candidateFeatures.begin(), candidateFeatures.end(), feature), candidateFeatures.end());

            FeatAndAcc candidateSet;
            candidateSet.selected_features = candidateFeatures;
            candidateSet.accuracy = dataset.Nearest_Neighbor(candidateFeatures);

            if (candidateSet.accuracy > bestThisLevel.accuracy) { //new set overtakes previous best
                bestThisLevel = candidateSet;
            }
        }

        if (bestThisLevel.accuracy > bestOverall.accuracy) {
            bestOverall = bestThisLevel;
        } else {
            cout << "\nWarning, Accuracy has decreased! Continuing search in case of local maxima)\n" << endl;
        }

        bestThisLevel.print();
        currentFeatures = bestThisLevel.selected_features;
    }

    cout << "\nBest feature subset: ";
    bestOverall.print();
}