#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cmath>
#include <cstdlib>

using namespace std;

// Struct to represent a data instance
struct Instance {
    double label;
    vector<double> features;

    Instance(double label = 0) : label(label) {}

    void append_feature(double value) {
        features.push_back(value);
    }

    const vector<double>& get_features() const {
        return features;
    }

    void set_type(double label) {
        this->label = label;
    }
};

// Struct to represent a feature subset and its accuracy
struct FeatureSet {
    double accuracy;
    vector<int> selected_features;

    bool operator<(const FeatureSet& other) const {
        return accuracy < other.accuracy;
    }

    vector<int> incrementIndices(const vector<int>& features) const {
        vector<int> incremented_features = features;
        for (int& feature : incremented_features) {
            feature += 1;
        }
        return incremented_features;
    }

    void display() const {
        //store features
        vector<int> incremented_features = incrementIndices(selected_features);
        ostringstream oss;

        if (!incremented_features.empty()) {
            copy(incremented_features.begin(), incremented_features.end() - 1,
                 ostream_iterator<int>(oss, ","));
            oss << incremented_features.back();
        }

        cout << "Feature set {" << oss.str() << "} with accuracy: " << accuracy << endl;
    }
};

// Parse the input dataset file
vector<Instance> parseInputFile(const string& filename) {
    ifstream file_stream(filename);
    vector<Instance> instances;

    // parse file only while input stream is good
    while (file_stream.good()) {
        double label;
        vector<double> feature_values;
        double value;

        string line;
        getline(file_stream, line);
        if (line.empty()) continue;

        istringstream line_stream(line);
        line_stream >> label;

        Instance instance(label);
        while (line_stream >> value) {
            instance.append_feature(value);
        }

        instances.push_back(instance);
    }

    return instances;
}

// accuracy evaluation function (dummy)
double calculateAccuracy(const vector<int>& features) {
    return static_cast<double>(rand()) / RAND_MAX * 100.0;
}

// Perform forward selection
void performForwardSelection(const vector<Instance>& instances, int num_features) {
    cout << "This dataset has " << num_features << " features with "
         << instances.size() << " instances:" << endl << endl;

    priority_queue<FeatureSet> feature_queue;
    FeatureSet best_feature_set;
    best_feature_set.accuracy = 0;

    FeatureSet current_feature_set;
    current_feature_set.selected_features.clear();
    current_feature_set.accuracy = calculateAccuracy(current_feature_set.selected_features);
    current_feature_set.display();

    vector<int> selected_features;
    bool accuracy_warning = true;

    for (int round = 0; round < num_features; ++round) {
        for (int feature = 0; feature < num_features; ++feature) {
            if (find(selected_features.begin(), selected_features.end(), feature) != selected_features.end()) {
                continue;
            }

            FeatureSet candidate_feature_set;
            candidate_feature_set.selected_features = selected_features;
            candidate_feature_set.selected_features.push_back(feature);
            candidate_feature_set.accuracy = calculateAccuracy(candidate_feature_set.selected_features);
            feature_queue.push(candidate_feature_set);
        }

        current_feature_set = feature_queue.top();
        if (current_feature_set.accuracy > best_feature_set.accuracy) {
            best_feature_set = current_feature_set;
        }

        if (accuracy_warning && current_feature_set.accuracy < best_feature_set.accuracy) {
            accuracy_warning = false;
            cout << endl << "Warning: accuracy decreasing, continuing search..." << endl << endl;
        }

        current_feature_set.display();
        selected_features = current_feature_set.selected_features;

        while (!feature_queue.empty()) {
            feature_queue.pop();
        }
    }

    cout << endl << "The best feature subset is: ";
    best_feature_set.display();
}

// Perform backward elimination
void performBackwardElimination(const vector<Instance>& instances, int num_features) {
    cout << "This dataset has " << num_features << " features with "
         << instances.size() << " instances:" << endl << endl;

    priority_queue<FeatureSet> feature_queue;
    FeatureSet best_feature_set;
    best_feature_set.accuracy = 0;

    FeatureSet current_feature_set;
    vector<int> selected_features(num_features);
    iota(selected_features.begin(), selected_features.end(), 0);

    current_feature_set.selected_features = selected_features;
    current_feature_set.accuracy = calculateAccuracy(current_feature_set.selected_features);
    current_feature_set.display();

    bool accuracy_warning = true;

    for (int round = 0; round < num_features; ++round) {
        for (int feature = 0; feature < num_features; ++feature) {
            if (find(selected_features.begin(), selected_features.end(), feature) == selected_features.end()) {
                continue;
            }

            FeatureSet candidate_feature_set;
            candidate_feature_set.selected_features = selected_features;
            candidate_feature_set.selected_features.erase(
                remove(candidate_feature_set.selected_features.begin(),
                       candidate_feature_set.selected_features.end(),
                       feature),
                candidate_feature_set.selected_features.end());
            candidate_feature_set.accuracy = calculateAccuracy(candidate_feature_set.selected_features);
            feature_queue.push(candidate_feature_set);
        }

        current_feature_set = feature_queue.top();
        if (current_feature_set.accuracy > best_feature_set.accuracy) {
            best_feature_set = current_feature_set;
        }

        if (accuracy_warning && current_feature_set.accuracy < best_feature_set.accuracy) {
            accuracy_warning = false;
            cout << endl << "Warning: accuracy decreasing, continuing search..." << endl << endl;
        }

        current_feature_set.display();
        selected_features = current_feature_set.selected_features;

        while (!feature_queue.empty()) {
            feature_queue.pop();
        }
    }

    cout << endl << "The best feature subset is: ";
    best_feature_set.display();
}

int main(int argc, char* argv[]) {
    //error handlers for file stream
    if (argc != 2) {
        cout << "Error: Invalid program call. Provide the dataset filename." << endl;
        return 1;
    }

    string input_file(argv[1]);
    vector<Instance> instances = parseInputFile(input_file);

    if (instances.empty()) {
        cout << "Error: Failed to parse input file or file is empty." << endl;
        return 1;
    }

    int num_features = instances[0].get_features().size();

    cout << "Welcome to the Feature Selection Algorithm" << endl;
    cout << "Choose the selection algorithm:" << endl;
    cout << "\t1) Forward Selection" << endl;
    cout << "\t2) Backward Elimination" << endl;

    int choice;
    cin >> choice;

    if (choice == 1) {
        performForwardSelection(instances, num_features);
    } else {
        performBackwardElimination(instances, num_features);
    }

    return 0;
}
