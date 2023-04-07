#include <cmath>
#include <complex>

using namespace std;

complex<double> sph_tangent(complex<double> v, complex<double> w) {
    complex<double> z = (v + w) / 2.0;
    double r = abs(v - w) / 2.0;
    double t = arg(v - w) / 2.0;
    return z + polar(r, t);
}

void e_to_s_data(complex<double> ez, complex<double> er, complex<double>& sz, double& sr) {
    double ns = pow(real(ez), 2) + pow(imag(ez), 2);
    double rr = abs(er);
    const double S_TOLER = 0.00000000001;

    // er is too small; project center, er unchanged.
    if (rr < S_TOLER) {
        sr = er;
        double denom = ns + 1.0;
        double tmpd = 1.0 / denom;
        double P3[3] = {(2 * real(ez)) * tmpd, (2 * imag(ez)) * tmpd, (2.0 - denom) * tmpd};
        if (P3[2] > (1.0 - S_TOLER)) {
            sz = 0.0;
            return;
        }

        if (P3[2] < (S_TOLER - 1.0)) {
            sz = 0.0 + M_PI * 1i;
        } else {
            sz = atan2(P3[1], P3[0]) + acos(P3[2]) * 1i;
        }
        return;
    }

    double norm = sqrt(ns);
    if (norm < S_TOLER) {  // close to origin
        double mn = -rr;
        double x = mn;
        double y = 0.0;
        double a = rr;
        double b = 0.0;
    } else {
        double denom = 1 / norm;
        double mn = norm - rr;
        // a point on the circle closest to origin */
        double x = mn * real(ez) * denom;
        double y = mn * imag(ez) * denom;
        // a point on the circle furthest from the origin */
        double a = (norm + rr) * real(ez) * denom;
        double b = (norm + rr) * imag(ez) * denom;
    }

    // now we project these two points onto the sphere
    double d1 = (x * x + y * y + 1.0);
    double tmpd = 1.0 / d1;
    double P1[3] = {2.0 * x * tmpd, 2.0 * y * tmpd, (2.0 - d1) * tmpd};
    double d2 = a * a + b * b + 1.0;
    tmpd = 1.0 / d2;
    double P2[3] = {2.0 * a * tmpd, 2.0 * b * tmpd, (2.0 - d2) * tmpd};

    // We may need some point along the geo between these, for they
    //    themselves might be too far apart to get the correct angle
    //    between them or to get the right tangent direction from one
    //    toward the other.
    //
    // We may use the origin, the euclidean center, or a point
    //    on the unit circle, depending on which is well placed
    //    vis-a-vis the endpoints.

    double brk = 100.0 * S_TOLER;
    int midflag = 0;
    double P3[3];
    if (mn <= -brk) {  // origin is well enclosed; use it.
        midflag = 1;
        P3[1] = 0;
        P3[0] = P3[1];
        P3[2] = 1.0;
    } else if (mn <= brk && norm > 2) {  // use pt on unit circle in direction of center
        midflag = 1;
        P3[0] = real(ez) / norm;
        P3[1] = imag(ez) / norm;
        P3[2] = 0.0;
    }

    if (midflag == 1) {  // use pt along geo; radius in two parts
        d1 = P1[0] * P3[0] + P1[1] * P3[1] + P1[2] * P3[2];
        if (d1 >= 1.0) {
            d1 = 1.0 - S_TOLER;
        }
        d2 = P2[0] * P3[0] + P2[1] * P3[1] + P2[2] * P3[2];
        if (d2 >= 1.0) {
            d2 = 1.0 - S_TOLER;
        }
        double ang13 = acos(d1);
        double ang23 = acos(d2);
        double rad = (ang13 + ang23) / 2.0;
        if (ang13 < ang23) {
            double E[3] = {P1[0], P1[1], P1[2]};
        } else {
            double E[3] = {P2[0], P2[1], P2[2]};
        }

        // Use E and P3 to find center; tangent direction from E toward P3.

        complex<double> v = atan2(E[1], E[0]) + acos(E[2]) * 1i;
        complex<double> w = atan2(P3[1], P3[0]) + acos(P3[2]) * 1i;
        complex<double> T = sph_tangent(v, w);
    } else {
        d1 = P1[0] * P2[0] + P1[1] * P2[1] + P1[2] * P2[2];
        if (d1 >= 1.0) {
            d1 = 1.0 - S_TOLER;
        }
        double rad = acos(d1) / 2.0;
        double E[3] = {P1[0], P1[1], P1[2]};
        complex<double> v = atan2(E[1], E[0]) + acos(E[2]) * 1i;
        complex<double> w = atan2(P2[1], P2[0]) + acos(P2[2]) * 1i;
        complex<double> T = sph_tangent(v, w);
    }

    // C will be the rectangular coordinates of the center
    double C[3] = {E[0] * cos(rad) + T.real() * sin(rad), E[1] * cos(rad) + T.imag() * sin(rad), E[2] * cos(rad) + T.imag() * sin(rad)};
    sr = rad;

    if (rad < 0) {  // actually, wanted outside of circle
        sr = M_PI - rad;
        double C[3] = {-1.0, -1.0, -1.0};
    }
    if (C[2] > 1 - S_TOLER) {
        sz = 0.0;
    } else if (C[2] < (S_TOLER - 1.0)) {
        sz = M_PI * 1i;
    } else {
        sz = atan2(C[1], C[0]) + acos(C[2]) * 1i;
    }
}
