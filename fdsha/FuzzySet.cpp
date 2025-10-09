#include "FuzzySet.h"
#include <algorithm>

namespace FDSHA {

    // --- Triangular Fuzzy Set Implementation ---
    TriangularFuzzySet::TriangularFuzzySet(std::string name, double a_val, double b_val, double c_val) {
        Name = name; a = a_val; b = b_val; c = c_val;
    }

    double TriangularFuzzySet::getMembershipDegree(double x) const {
        if (x <= a || x >= c) return 0.0;
        if (x == b) return 1.0;
        // Rising slope
        if (x > a && x < b) return (x - a) / (b - a);
        // Falling slope
        if (x > b && x < c) return (c - x) / (c - b);
        return 0.0;
    }

    // --- Trapezoidal Fuzzy Set Implementation ---
    TrapezoidalFuzzySet::TrapezoidalFuzzySet(std::string name, double a_val, double b_val, double c_val, double d_val) {
        Name = name; a = a_val; b = b_val; c = c_val; d = d_val;
    }

    double TrapezoidalFuzzySet::getMembershipDegree(double x) const {
        if (x <= a || x >= d) return 0.0;
        // Peak (membership = 1.0)
        if (x >= b && x <= c) return 1.0;
        // Rising slope
        if (x > a && x < b) return (x - a) / (b - a);
        // Falling slope
        if (x > c && x < d) return (d - x) / (d - c);
        return 0.0;
    }

} // namespace FDSHA
