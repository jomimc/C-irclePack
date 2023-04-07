double cosAngle(double r, double r1, double r2) {
    double c = r1 * r2;
    double cosang = 1 - 2 * c / (r * r + r * (r1 + r2) + c);
    return cosang;
}
