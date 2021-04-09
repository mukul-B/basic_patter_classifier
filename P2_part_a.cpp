#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <math.h>

#include "MatricOP.h"
#include "DiscriminantCases.h"

#define classifierCase1 1
#define classifierCase3 3

using namespace std;

vector< pair<string, string> > returnDataToString(string filename);
vector< pair<double, double> > convertStringToFloat(vector< pair<string, string> > dataSet);
void problem(vector<vector<double> > mu1, vector<vector<double> > cov1, int sampCount1,
             vector<vector<double> > mu2, vector<vector<double> > cov2, int sampCount2,
             int classificationMethod, 
             vector<pair<double, double>> inputData1, vector<pair<double, double>> inputData2);
void classification(vector<Matrix> sam1, vector<Matrix> sam2, ClassifierClass *classifier);

vector<Matrix> vector_inter(const vector<Matrix> &c1, const vector<Matrix> &c2);
vector<Matrix> vector_union(vector<Matrix> m1, vector<Matrix> m2);
vector<Matrix>
sampleMatrix(vector<vector<double>> mu, vector<vector<double> > sigma, pair<int, int> mudimen, int sampCount
                , vector<pair<double, double>> inputData);

struct sampleSpace {
    vector<vector<double> > mu1;
    vector<vector<double> > cov1;
    int sampCount1;
    vector<vector<double> > mu2;;
    vector<vector<double> > cov2;
    int sampCount2;
};
//  sample space 1 have two distribution with same covariance matrix
sampleSpace samplespace1(float mux1, float muy1, float sigmax1, float sigmay1,
                            float mux2, float muy2, float sigmax2, float sigmay2) {
    sampleSpace s1;
    s1.mu1 = {{mux1},
              {muy1}};
    s1.cov1 = {{sigmax1, 0},
               {0, sigmay1}};
    s1.sampCount1 = 60000;

    s1.mu2 = {{mux2},
              {muy2}};
    s1.cov2 = {{sigmax2, 0},
               {0, sigmay2}};

    s1.sampCount2 = 140000;

    return s1;
}

//  sample space 1 have two distribution with different covariance matrix
sampleSpace samplespace2(float mux1, float muy1, float sigmax1, float sigmay1,
                            float mux2, float muy2, float sigmax2, float sigmay2) {
    sampleSpace s2;
    s2.mu1 = {{mux1},
              {muy1}};
    s2.cov1 = {{sigmax1, 0},
               {0, sigmay1}};
    s2.sampCount1 = 40000;

    s2.mu2 = {{mux2},
              {muy2}};
    s2.cov2 = {{sigmax2, 0},
               {0, sigmay2}};
    s2.sampCount2 = 160000;

    return s2;
}

int main() {
    int input;

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

    vector< pair<double, double> > dataSet1f;
    vector< pair<double, double> > dataSet2f;

    dataSet1f = convertStringToFloat(dataSet1);
    dataSet2f = convertStringToFloat(dataSet2);


    double sample_mu_x1 = 0, sample_mu_y1 = 0;
    int counter = 0;
    for (counter; counter < dataSet1f.size(); counter++) {
        sample_mu_x1 += dataSet1f[counter].first;
        sample_mu_y1 += dataSet1f[counter].second;
    }
    sample_mu_x1 /= counter;
    sample_mu_y1 /= counter;

    double sample_sigma_x1 = 0, sample_sigma_y1 = 0;
    counter = 0;
    for (counter; counter < dataSet1f.size(); counter++) {
        sample_sigma_x1 += pow(dataSet1f[counter].first - sample_mu_x1, 2);
        sample_sigma_y1 += pow(dataSet1f[counter].second - sample_mu_y1, 2);
    }
    sample_sigma_x1 /= counter;
    sample_sigma_y1 /= counter;



    double sample_mu_x2 = 0, sample_mu_y2 = 0;
    counter = 0;
    for (counter; counter < dataSet2f.size(); counter++) {
        sample_mu_x2 += dataSet2f[counter].first;
        sample_mu_y2 += dataSet2f[counter].second;
    }
    sample_mu_x2 /= counter;
    sample_mu_y2 /= counter;

    double sample_sigma_x2 = 0, sample_sigma_y2 = 0;
    counter = 0;
    for (counter; counter < dataSet2f.size(); counter++) {
        sample_sigma_x2 += pow(dataSet2f[counter].first - sample_mu_x2, 2);
        sample_sigma_y2 += pow(dataSet2f[counter].second - sample_mu_y2, 2);
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

    sampleSpace sampleSet;
    int classifierType;

    switch(input) {
        case 1:
            sampleSet = samplespace1(sample_mu_x1, sample_mu_y1, sample_sigma_x1, sample_sigma_y1, 
                                        sample_mu_x2, sample_mu_y2, sample_sigma_x2, sample_sigma_y2);
            classifierType = classifierCase3;
            break;
        case 2:
            sampleSet = samplespace2(sample_mu_x1, sample_mu_y1, sample_sigma_x1, sample_sigma_y1, 
                                        sample_mu_x2, sample_mu_y2, sample_sigma_x2, sample_sigma_y2);
            classifierType = classifierCase3;
            break;
    }

    problem(sampleSet.mu1, sampleSet.cov1, sampleSet.sampCount1,
            sampleSet.mu2, sampleSet.cov2, sampleSet.sampCount2,
            classifierType, dataSet1f, dataSet2f);

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

vector< pair<double, double> > convertStringToFloat(vector< pair<string, string> > dataSet) {
    vector< pair<double, double> > dataSetf;
    for (int i = 0; i < dataSet.size() - 1; i++) {
        dataSetf.push_back(make_pair(stod(dataSet[i].first), stod(dataSet[i].second)));
    }
    return dataSetf;
}

void problem(vector<vector<double> > mu1, vector<vector<double> > cov1, int sampCount1,
             vector<vector<double> > mu2, vector<vector<double> > cov2, int sampCount2,
             int classificationMethod, 
             vector<pair<double, double>> inputData1, vector<pair<double, double>> inputData2) {

    // the Object of Matrix class is created for each mu and covariance from sample space
    int noOfFfeatures = 2;
    pair<int, int> mudimen = {noOfFfeatures, 1};
    pair<int, int> covdimen = {noOfFfeatures, noOfFfeatures};
    Matrix m1, m2;
    m1.input(mu1, mudimen);
    m2.input(mu2, mudimen);
    Matrix cv1, cv2;
    cv1.input(cov1, covdimen);
    cv2.input(cov2, covdimen);

 //  Prior probability from sample size
    int sampCountT = sampCount1 + sampCount2;
    double prior1 = (double) sampCount1 / sampCountT;
    double prior2 = (double) sampCount2 / sampCountT;

 // creating random Samples in form of Matrix  by  using box muller method
 // sampleMatrix return vector of Matrix using box-mular and given  mu and sigma values
    vector<Matrix> sam1 = sampleMatrix(mu1, cov1, mudimen, sampCount1, inputData1);
    vector<Matrix> sam2 = sampleMatrix(mu2, cov2, mudimen, sampCount2, inputData2);

// Using case of classifier as per the requirement
// the object is initiated by the class of required classfier ( eg case1, case3, EuclideanClass)
// all the class are inherited by ClassifierClass
// so we can use the pointer to the ClassifierClass to achieve virtualization
    ClassifierClass *classifier;
    /* if (classificationMethod == classifierCase1) {
        Case1 classifierType = Case1(m1, m2, cv1, cv2, prior1, prior2);
        classification(sam1, sam2, classifier = &classifierType);
    } else if (classificationMethod == classifierCase3) { */
        Case3 classifierType = Case3(m1, m2, cv1, cv2, prior1, prior2);
        classification(sam1, sam2, classifier = &classifierType);
    //}

}
// classification function takes samples and classifier
// method used of classifier
//classifier_>getDecision : to get the discriminate value
//classifier->getErrorBound : to get the Error bound
//vector_inter to get the miss classification

void classification(vector<Matrix> samp1, vector<Matrix> samp2,
                    ClassifierClass *classifier) {

    // both the sample are added , so that it can be classified into a class
    //vector_union to take union of two vectors
    vector<Matrix> sampT = vector_union(samp1, samp2);

    vector<Matrix> w1, w2;
    for (Matrix xp : sampT) {
        // the samples are input to the getDecision function of classifier
        double discriminate_value = classifier->getDecision(xp);
        // depending on the value the sample is either goes to w1 or w2 class
        if (discriminate_value >= 0)
            w1.push_back(xp);
        else
            w2.push_back(xp);
    }

    // the sample points are derived which are not correctly classified in it particular class
    vector<Matrix> miss1 = vector_inter(samp1, w2);
    vector<Matrix> miss2 = vector_inter(samp2, w1);

    double miss_class_rate = (double) (miss1.size() + miss2.size()) / sampT.size();

    // Theoretical  errorbound is calculated with Battacharya constant
    double errorbound = classifier->getErrorBound(0.5);

    // Report generation: classification class size ,initial sample size ,
    // miss classification rate and eroor bound
    cout << "\nSamples classified in  class 1: " << w1.size() << ", class 2: " << w2.size() << "\n";
    cout << "Miss-classified from sample 1: " << miss1.size() << ", sample 2: " << miss2.size() << "\n";
    cout << "Miss-classification rate  for class 1 : " << (double) miss1.size() / samp1.size() << ", class 2: "
         << (double) miss2.size() / samp2.size() << "\n";
    cout << "Total miss-classification rate : " << miss_class_rate << '\n';
    cout << "Bhattacharyya error bound: " << errorbound << endl;

    //writeAllResultsToFile(sam1,sam1,w1,w2,miss1,miss2);
    // the values can be stored in excel to get plots
}

// vector_inter will return the values present in c1 but not in c2
vector<Matrix> vector_inter(const vector<Matrix> &c1, const vector<Matrix> &c2) {
    set<Matrix> s_c1(c1.begin(), c1.end());
    set<Matrix> s_c2(c2.begin(), c2.end());
    vector<Matrix> result;
    set_intersection(s_c1.begin(), s_c1.end(),
                     s_c2.begin(), s_c2.end(),
                     back_inserter(result));
    // back_inserter uses < to sort the element
    // for that reason operator< is overloaded for the class
    return result;
}

vector<Matrix> vector_union(vector<Matrix> m1, vector<Matrix> m2) {
    vector<Matrix> samT;
    samT.insert(samT.end(), m1.begin(), m1.end());
    samT.insert(samT.end(), m2.begin(), m2.end());
    return samT;
}

vector<Matrix>
sampleMatrix(vector<vector<double>> mu, vector<vector<double> > sigma, pair<int, int> mudimen, int sampCount
                , vector<pair<double, double>> inputData) {
    vector<Matrix> sam;
    for (int k = 0; k < sampCount; k++) {
        double x = inputData[k].first;
        double y = inputData[k].second;
        vector<vector<double> > sampler
                = {{x},
                   {y}};
        Matrix sample;
        sample.input(sampler, mudimen);
        sam.push_back(sample);
    }
    return sam;
}