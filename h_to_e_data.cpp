double* h_to_e_data(double hz, double hr) {
    double* result = new double[2];
    double er, ahc, s_rad, n1, n2, b, ez;
    if (hr < 0) {
        er = -hr;
        ez = hz * (1 - er);
        result[0] = ez;
        result[1] = er;
        return result;
    }
    ahc = abs(hz);
    s_rad = exp(-hr);
    n1 = pow((1 + s_rad), 2);
    n2 = n1 - ahc * ahc * pow((1 - s_rad), 2);
    er = (1.0 - pow(s_rad, 2)) * (1.0 - pow(ahc, 2)) / n2;
    b = 4.0 * s_rad / n2;
    ez = hz * b;
    result[0] = ez;
    result[1] = er;
    return result;
}
