

#ifndef PATERNREC_RANDOMNOGENERATOR_H
#define PATERNREC_RANDOMNOGENERATOR_H

#endif //PATERNREC_RANDOMNOGENERATOR_H


double ranf(double m) {
    return (m * rand() / (double) RAND_MAX);
}

double boxMuller() {
    double x1, x2, w, y1;
    static double y2;
    static int use_last = 0;
    if (use_last)                /* use value from previous call */
    {
        y1 = y2;
        use_last = 0;
    } else {
        do {
            x1 = 2.0 * ranf(1.0) - 1.0;
            x2 = 2.0 * ranf(1.0) - 1.0;
            w = x1 * x1 + x2 * x2;
        } while (w >= 1.0);
        w = sqrt((-2.0 * log(w)) / w);
        y1 = x1 * w;
        y2 = x2 * w;
    }
    return y1;
}

// using Box mullar random no and mu and sigma , distribution is created
vector<Matrix>
sampleMatrix(vector<vector<double>> mu, vector<vector<double> > sigma, pair<int, int> mudimen, int sampCount) {
    vector<Matrix> sam;
    for (int k = 0; k < sampCount; k++) {
        double x = boxMuller();
        double y = boxMuller();
        vector<vector<double> > sampler
                = {{mu[0][0] + x * sigma[0][0]},
                   {mu[1][0] + y * sigma[1][1]}};
        Matrix sample;
        sample.input(sampler, mudimen);
        sam.push_back(sample);
    }
    return sam;
}