#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include "DataEntry.h"
#include "NN.h"

using namespace std;

NN::NN(const vector<DataEntry>& ds): ds(ds) {}

double NN::Euclidean(const vector<double>& test_data, const vector<double>& train_data, const vector<int>& features) {
    double distance = 0;
    for (int feature : features) {
        distance += pow(test_data.at(feature) - train_data.at(feature), 2);
    }
    return sqrt(distance); 
}

double NN::Nearest_Neighbor(const vector<int>& features) {//grab nearest neighbor based on euclidean distance for classification
    double accurate_classification = 0; 
    double instances = 0;

    for (int i = 0; i < ds.size(); i++) {
        double smallest_distance = numeric_limits<double>::max();
        DataEntry nearest_neighbor;

        for (int j = 0; j < ds.size(); j++) { //curr feature distance to every other feature (REPEATS CALCULATIONS)
            if (i != j) {
                double calc_distance = Euclidean(
                    ds[i].get_entry_features(), 
                    ds[j].get_entry_features(), 
                    features
                );

                if (calc_distance < smallest_distance) {
                    smallest_distance = calc_distance;
                    nearest_neighbor = ds[j];
                }
            }
        }

        if (nearest_neighbor.get_classification() == ds[i].get_classification()) {
            accurate_classification++;
        }
        instances++;
    }

    double classification_rate = accurate_classification / instances;
    return classification_rate;
}