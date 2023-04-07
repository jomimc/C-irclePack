double cosCorner(double z1, double z2, double z3) {
    double l2 = abs(z2 - z1);
    double l3 = abs(z3 - z1);
    double l23 = abs(z3 - z2);
    double denom = 2 * l2 * l3;
    double cosang = (l2 * l2 + l3 * l3 - l23 * l23) / denom;
    cosang = max(min(cosang, 1.0), -1.0); // force to be between -1 and 1
    return cosang;
}
