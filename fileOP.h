
#ifndef PATERNREC_FILEOP_H
#define PATERNREC_FILEOP_H

#endif //PATERNREC_FILEOP_H

using namespace std;

void writeSampleToFile(vector<Matrix> sample, string name) {
    fstream fout2;
    fout2.open(name, ios::out);

    for (Matrix cord  : sample) {
        vector<double> cordinate = cord.getVector();
        fout2 << cordinate[0] << ','
              << cordinate[1]
              << "\n";
    }

}

// it can be added at the end of code , to plot the results
void
writeAllResultsToFile(vector<Matrix> sam1, vector<Matrix> sam2,
                   vector<Matrix> w1, vector<Matrix> w2,
                   vector<Matrix> miss1, vector<Matrix> miss2) {
    writeSampleToFile(sam1, "psam1.csv");
    writeSampleToFile(sam2, "psam2.csv");
    writeSampleToFile(w1, "w1.csv");
    writeSampleToFile(w2, "w2.csv");
    writeSampleToFile(miss1, "miss1.csv");
    writeSampleToFile(miss2, "miss2.csv");
}


