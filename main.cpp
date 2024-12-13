#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "limits.h"
#include "DataEntry.h"
#include "NN.h"
#include "forward_backward.h"

using namespace std;

void displayMenu() {
    cout << "Welcome to the CS 170 Feature Selection Algorithm" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Choose a feature selection algorithm:" << endl;
    cout << "1) Forward Selection" << endl;
    cout << "2) Backward Elimination" << endl;
    cout << "Enter your choice (1 or 2): ";
}

vector<DataEntry> loadData(const string& input_file) { //load data by parsing input file
    ifstream file(input_file);
    if (!file) {
        cerr << "Error: Unable to open file " << input_file << endl;
        exit(EXIT_FAILURE);
    }

    vector<DataEntry> data;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        double classification;
        iss >> classification;

        if (classification == INT_MAX) {
            break;
        }

        DataEntry entry;
        entry.set_classification(classification);

        double feature;
        while (iss >> feature) {
            entry.addFeature(feature);
        }
        data.push_back(entry);
    }

    if (data.empty()) {
        cerr << "Error: No valid data entries found in the file." << endl;
        exit(EXIT_FAILURE);
    }

    return data;
}

int getAlgorithmChoice() { //menu
    int choice = 0;
    while (true) {
        displayMenu();
        cin >> choice;

        if (choice == 1 || choice == 2) {
            break;
        } else {
            cout << "Invalid input. Please enter 1 or 2." << endl;
        }
    }
    return choice;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return EXIT_FAILURE;
    }

    const string input_file = argv[1];
    cout << "Loading data from file: " << input_file << endl;

    auto data = loadData(input_file);

    NN featureSet(data);
    size_t feature_count = data[0].get_entry_features().size();

    int choice = getAlgorithmChoice();
    if (choice == 1) {
        cout << "Running Forward Selection..." << endl;
        ForwardSelection(featureSet, feature_count);
    } 
    else if (choice == 2) {
        cout << "Running Backward Elimination..." << endl;
        BackwardElimination(featureSet, feature_count);
    }
    

    return EXIT_SUCCESS;
}