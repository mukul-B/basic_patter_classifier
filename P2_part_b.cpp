#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

vector< pair<string, string> > returnDataToString(string filename);
vector< pair<float, float> > convertStringToFloat(vector< pair<string, string> > dataSet);

int main() {
    int input, inputp;

    vector< pair<string, string> > dataSet1;
    vector< pair<string, string> > dataSet2;

    cout << "Enter the Experiment no. (1 or 2): ";
    cin >> input;

    string filename1;
    string filename2;

    if (input == 1) {
        filename1 = "./psam1.csv";
        filename2 = "./psam2.csv";
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

    cout << "Select pct of samples:" << endl;
    cout << "1. 0.01%" << endl;
    cout << "2. 0.1%" << endl;
    cout << "3. 1%" << endl;
    cout << "4. 10%" << endl;
    cin >> inputp;

    int pctSample;
    switch(inputp) {
        case 1:
            pctSample = 10000;
            break;
        case 2:
            pctSample = 1000;
            break;
        case 3:
            pctSample = 100;
            break;
        case 4:
            pctSample = 10;
            break;  
    }

    int sampleSize1 = dataSet1f.size() / pctSample;
    int sampleSize2 = dataSet2f.size() / pctSample;

    vector< pair<float, float> > sampSet1;
    vector< pair<float, float> > sampSet2;

    srand (time(NULL));
    int results1[sampleSize1];
    int *begin1 = results1;
    int *end1 = begin1 + sampleSize1;
    for (int i = 0; i < sampleSize1; i++) {
        int r;
        do {
            r = rand() % dataSet1f.size();
        } while(find(begin1, end1, r) != end1);
        results1[i] = r;
        sampSet1.push_back(make_pair(dataSet1f[r].first, dataSet1f[r].second));
    }

    int results2[sampleSize2];
    int *begin2 = results2;
    int *end2 = begin2 + sampleSize2;
    for (int i = 0; i < sampleSize2; i++) {
        int r;
        do {
            r = rand() % dataSet2f.size();
        } while(find(begin2, end2, r) != end2);
        results2[i] = r;
        sampSet2.push_back(make_pair(dataSet2f[r].first, dataSet2f[r].second));
    }

    float sample_mu_x1 = 0, sample_mu_y1 = 0;
    int counter = 0;
    for (counter; counter < sampSet1.size(); counter++) {
        sample_mu_x1 += sampSet1[counter].first;
        sample_mu_y1 += sampSet1[counter].second;
    }
    sample_mu_x1 /= counter;
    sample_mu_y1 /= counter;

    float sample_sigma_x1 = 0, sample_sigma_y1 = 0;
    counter = 0;
    for (counter; counter < sampSet1.size(); counter++) {
        sample_sigma_x1 += pow(sampSet1[counter].first - sample_mu_x1, 2);
        sample_sigma_y1 += pow(sampSet1[counter].second - sample_mu_y1, 2);
    }
    sample_sigma_x1 /= counter;
    sample_sigma_y1 /= counter;



    float sample_mu_x2 = 0, sample_mu_y2 = 0;
    counter = 0;
    for (counter; counter < sampSet2.size(); counter++) {
        sample_mu_x2 += sampSet2[counter].first;
        sample_mu_y2 += sampSet2[counter].second;
    }
    sample_mu_x2 /= counter;
    sample_mu_y2 /= counter;

    float sample_sigma_x2 = 0, sample_sigma_y2 = 0;
    counter = 0;
    for (counter; counter < sampSet2.size(); counter++) {
        sample_sigma_x2 += pow(sampSet2[counter].first - sample_mu_x2, 2);
        sample_sigma_y2 += pow(sampSet2[counter].second - sample_mu_y2, 2);
    }
    sample_sigma_x2 /= counter;
    sample_sigma_y2 /= counter;

    cout << "Distribution 1" << endl;
    cout << "Sample mean: <" << sample_mu_x1 << ", " << sample_mu_y1 << ">" << endl;
    cout << "Sample covariance: <" << sample_sigma_x1 << ", " << sample_sigma_y1 << ">" << endl;
    cout << endl;
    cout << "Distribution 2" << endl;
    cout << "Sample mean: <" << sample_mu_x2 << ", " << sample_mu_y2 << ">" << endl;
    cout << "Sample covariance: <" << sample_sigma_x2 << ", " << sample_sigma_y2 << ">" << endl;

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