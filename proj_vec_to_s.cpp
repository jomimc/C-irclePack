#include <cmath>

double proj_vec_to_s(double vec[]) {
    const double S_TOLER = 0.0000000000001;
    double dist = std::sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
    if (dist < S_TOLER) {
        return 0.0;
    }
    double sz = std::atan2(vec[1], vec[0]) + std::acos(vec[2]/dist)*1i;
    return sz;
}
