double e_to_h_data(double ez, double er, double& hz, double& hr) {
    double aec = abs(ez);
    double dist = aec + er;
    if (dist > 1.000000000001) {
        aec = aec / dist;
        er = er / dist;
        dist = 1.0;
    }
    if (0.99999999 < dist) {
        if (abs(er) > 0.99999999) {
            er = er / 2.0;
        }
        hr = -er;
        if (aec < 0.0001) {
            hz = 0.0;
        } else {
            hz = ez * (1 / aec);
        }
        return 0;
    }
    double c2 = aec * aec;
    double r2 = er * er;
    if (aec < 0.0000000000001) {
        hz = 0.0;
    } else {
        double t = 1 + c2 - r2;
        double b = sqrt((t + 2 * aec) / (t - 2 * aec));
        double ahc = (b - 1) / (b + 1);
        hz = ez * ahc / aec;
    }
    double t = 1 + r2 - c2;
    double s = sqrt((t - 2 * er) / (t + 2 * er));
    double x = 1.0 - s * s;
    if (x > 0.0001) {
        hr = (-0.5) * log(1.0 - x);
    } else {
        hr = x * (1.0 + x * (0.5 + x / 3)) / 2;
    }
    return 0;
}
