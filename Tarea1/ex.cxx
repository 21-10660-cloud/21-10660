#include <vector>
#include <numeric>
#include <cmath>

double mean(const std::vector<double>& v) {
    if (v.empty()) return 0.0;
    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double variance(const std::vector<double>& v) {
    if (v.size() < 2) return 0.0;
    double m = mean(v);
    double temp = 0;
    for (double x : v) temp += (x - m) * (x - m);
    return temp / v.size();
}

double pearson_r(const std::vector<double>& VA, const std::vector<double>& VB) {
    if (VA.size() != VB.size() || VA.empty()) return 0.0;
    double n = VA.size();
    double sA = std::accumulate(VA.begin(), VA.end(), 0.0);
    double sB = std::accumulate(VB.begin(), VB.end(), 0.0);
    double sAB = 0, sA2 = 0, sB2 = 0;
    for (size_t i = 0; i < n; i++) {
        sAB += VA[i] * VB[i];
        sA2 += VA[i] * VA[i];
        sB2 += VB[i] * VB[i];
    }
    double num = (n * sAB) - (sA * sB);
    double den = std::sqrt(((n * sA2) - (sA * sA)) * ((n * sB2) - (sB * sB)));
    return (den == 0) ? 0.0 : num / den;
}