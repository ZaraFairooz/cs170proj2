#ifndef DATAENTRY_H
#define DATAENTRY_H

#include <iostream>
#include <vector>

using namespace std;

class DataEntry
{
    private:
        double classification;
        vector<double> entry_features;

    public:
        DataEntry();
        void set_classification(double);
        void addFeature(double);
        vector<double> get_entry_features() const;
        double get_classification() const;
        void print() const;
};

#endif