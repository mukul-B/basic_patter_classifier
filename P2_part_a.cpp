#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <math.h>

//#include "MatricOP.h"

using namespace std;

vector< pair<string, string> > returnDataToString(string filename);
vector< pair<float, float> > convertStringToFloat(vector< pair<string, string> > dataSet);

int main() {
    int input;

    vector< pair<string, string> > dataSet1;
    vector< pair<string, string> > dataSet2;

    cout << "Enter the Experiment no. (1 or 2): ";
    cin >> input;

    string filename1;
    string filename2;

    if (input == 1) {
        filename1 = "./w1.csv";
        filename2 = "./w2.csv";
    }
    else if (input == 2) {
        filename1 = "./sam1.csv";
        filename2 = "./sam2.csv";
    }

    dataSet1 = returnDataToString(filename1);
    dataSet2 = returnDataToString(filename2);

    vector< pair<float, float> > dataSet1f;
    vector< pair<float, float> > dataSet2f;

    dataSet1f = convertStringToFloat(dataSet1);
    dataSet2f = convertStringToFloat(dataSet2);

    dataSet1f.insert( dataSet1f.end(), dataSet2f.begin(), dataSet2f.end() );

    float sample_mu_x = 0, sample_mu_y = 0;
    int counter = 0;
    for (counter; counter < dataSet1f.size(); counter++) {
        sample_mu_x += dataSet1f[counter].first;
        sample_mu_y += dataSet1f[counter].second;
    }
    sample_mu_x /= counter;
    sample_mu_y /= counter;

    float sample_sigma_x = 0, sample_sigma_y = 0;
    counter = 0;
    for (counter; counter < dataSet1f.size(); counter++) {
        sample_sigma_x += pow(dataSet1f[counter].first - sample_mu_x, 2);
        sample_sigma_y += pow(dataSet1f[counter].second - sample_mu_y, 2);
    }
    sample_sigma_x /= counter;
    sample_sigma_y /= counter;

    cout << "Sample mean: <" << sample_mu_x << ", " << sample_mu_y << ">" << endl;
    cout << "Sample covariance: <" << sample_sigma_x << ", " << sample_sigma_y << ">" << endl;

    return 0;
}

vector< pair<string, string> > returnDataToString(string filename) {
    vector< pair<string, string> > dataSet;
    string x_val, y_val;

    ifstream dataFile(filename);
    if(dataFile.is_open()) {
        while (!dataFile.eof()) {
            getline(dataFile, x_val, ',');
            getline(dataFile, y_val, '\n');
			dataSet.push_back(make_pair(x_val, y_val));
        }
    }
    return dataSet;
}

vector< pair<float, float> > convertStringToFloat(vector< pair<string, string> > dataSet) {
    vector< pair<float, float> > dataSetf;
    for (int i = 0; i < dataSet.size() - 1; i++) {
        dataSetf.push_back(make_pair(stof(dataSet[i].first), stof(dataSet[i].second)));
    }
    return dataSetf;
}