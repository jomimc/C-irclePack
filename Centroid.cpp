double Centroid(double* P, double* trans, double& normsq, double& X, double& Y, double& Z) {
    double mu = trans[0] * P[0] + trans[1];
    double mv = trans[0] * P[1] + trans[2];
    double sq = pow(mu, 2) + pow(mv, 2);
    double denom = 1 + sq;
    double x = 2 * mu / denom;
    double y = 2 * mv / denom;
    double z = (1 - sq) / denom;
    X = x;
    Y = y;
    Z = z;
    normsq = pow(X, 2) + pow(Y, 2) + pow(Z, 2);
    return normsq;
}
