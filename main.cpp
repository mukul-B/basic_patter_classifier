#include <iostream>
#include "bits/stdc++.h"

#include "MatricOP.h"
#include "DiscriminantCases.h"
#include "RandomNoGenerator.h"

#include "fileOP.h"
#define classifierCase1 1
#define classifierCase3 3
#define classifierEuclid 4

using namespace std;

void problem(vector<vector<double> > mu1, vector<vector<double> > cov1, int sampCount1,
             vector<vector<double> > mu2, vector<vector<double> > cov2, int sampCount2,
             int classificationMethod);
void classification(vector<Matrix> sam1, vector<Matrix> sam2, ClassifierClass *classifier);

vector<Matrix> vector_inter(const vector<Matrix> &c1, const vector<Matrix> &c2);
vector<Matrix> vector_union(vector<Matrix> m1, vector<Matrix> m2);

// structure is created to have the parameters to represent the likelihood gausian distribution
struct sampleSpace {
    vector<vector<double> > mu1;
    vector<vector<double> > cov1;
    int sampCount1;
    vector<vector<double> > mu2;;
    vector<vector<double> > cov2;
    int sampCount2;
};
//  sample space 1 have two distribution with same covariance matrix
sampleSpace samplespace1() {
    sampleSpace s1;
    s1.mu1 = {{1},
              {1}};
    s1.cov1 = {{1, 0},
               {0, 1}};
    s1.sampCount1 = 60000;

    s1.mu2 = {{4},
              {4}};
    s1.cov2 = {{1, 0},
               {0, 1}};

    s1.sampCount2 = 140000;

    return s1;
}

//  sample space 1 have two distribution with different covariance matrix
sampleSpace samplespace2() {
    sampleSpace s2;
    s2.mu1 = {{1},
              {1}};
    s2.cov1 = {{1, 0},
               {0, 1}};
    s2.sampCount1 = 40000;

    s2.mu2 = {{4},
              {4}};
    s2.cov2 = {{4, 0},
               {0, 8}};
    s2.sampCount2 = 160000;

    return s2;
}

// main program let user to choose the problem number to get its classification results.
// sample space(by calling function that return mu and covariance  parameter encapsulated in structure
// and classifier type is selected as per the choice
// and problem function is called by the parameter selected using the choice

int main() {

    sampleSpace sampleSet;
    int classierType;
    int prob;

    printf("Programing Assignment 1: \n");
    printf("------------------------------------------\n");
    printf("Main Menu\n");
    printf("1. Problem1.\n");
    printf("2. Problem2.\n");
    printf("3. Problem3.\n");
    printf("4. Problem4.\n");
    printf(" Please enter an option from the main menu: ");

      fflush(stdin);
      scanf("%d", &prob);

   // prob = 2;
    if (prob == 1) {
        // Problem 1: diagonal and equal covariance matrix, classification using case1
        sampleSet = samplespace1();
        classierType = classifierCase1;
    } else if (prob == 2) {
        // Problem 2: distinct covariance matrix, classification using case3
        sampleSet = samplespace2();
        classierType = classifierCase3;
    } else if (prob == 3) {
        // Problem 3: diagonal and equal covariance matrix, classification using  Euclidean distance classifier
        sampleSet = samplespace1();
        classierType = classifierEuclid;
    } else if (prob == 4) {
        // Problem 4: distinct covariance matrix, classification using Euclidean distance classifier
        sampleSet = samplespace2();
        classierType = classifierEuclid;
    } else return 0;

    problem(sampleSet.mu1, sampleSet.cov1, sampleSet.sampCount1,
            sampleSet.mu2, sampleSet.cov2, sampleSet.sampCount2,
            classierType);

    return 0;
}

// problem runs for particular distribution and classifier type
// it created classifier with ( mu , covariance, priors)
// along with parameters of particular case required for discriminate function
// it create sample matrix from box mullar for both distributions
// finally ClassifierClass is called to classify the sample using giver classifier

void problem(vector<vector<double> > mu1, vector<vector<double> > cov1, int sampCount1,
             vector<vector<double> > mu2, vector<vector<double> > cov2, int sampCount2,
             int classificationMethod) {

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
    vector<Matrix> sam1 = sampleMatrix(mu1, cov1, mudimen, sampCount1);
    vector<Matrix> sam2 = sampleMatrix(mu2, cov2, mudimen, sampCount2);

// Using case of classifier as per the requirement
// the object is initiated by the class of required classfier ( eg case1, case3, EuclideanClass)
// all the class are inherited by ClassifierClass
// so we can use the pointer to the ClassifierClass to achieve virtualization
    ClassifierClass *classifier;
    if (classificationMethod == classifierCase1) {
        Case1 classifierType = Case1(m1, m2, cv1, cv2, prior1, prior2);
        classification(sam1, sam2, classifier = &classifierType);
    } else if (classificationMethod == classifierCase3) {
        Case3 classifierType = Case3(m1, m2, cv1, cv2, prior1, prior2);
        classification(sam1, sam2, classifier = &classifierType);
    } else if (classificationMethod == classifierEuclid) {
        EuclideanClass classifierType = EuclideanClass(m1, m2, cv1, cv2, prior1, prior2);
        classification(sam1, sam2, classifier = &classifierType);
    }

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
    cout << "\nSamples classified in  class 1: " << w1.size() << " ,class 2: " << w2.size() << "\n";
    cout << "Miss-classified from sample 1: " << miss1.size() << " ,sample 2: " << miss2.size() << "\n";
    cout << "Miss-classification rate  for class 1 : " << (double) miss1.size() / samp1.size() << " ,class 2: "
         << (double) miss2.size() / samp2.size() << "\n";
    cout << "Total miss-classification rate  : " << miss_class_rate << '\n';
    cout << "Bhattacharyya error bound : " << errorbound;

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
