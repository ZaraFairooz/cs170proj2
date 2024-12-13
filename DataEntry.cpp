#include <iostream>
#include "DataEntry.h"

using namespace std;

DataEntry::DataEntry() : classification(0) {}

void DataEntry::set_classification(double num) { //set classification value for entry
    classification = num;
}
void DataEntry::addFeature(double feature) {//push feature into feature set
    entry_features.push_back(feature);
}
double DataEntry::get_classification() const {//entry classification getter
    return classification;
}

vector<double> DataEntry::get_entry_features() const {//feature getter
    return entry_features;
}

void DataEntry::print() const {
    for (int i = 0; i < entry_features.size(); i++) {
        cout << entry_features.at(i) << " ";
    }
}