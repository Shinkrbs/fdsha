#ifndef FUZZYRULE_H
#define FUZZYRULE_H

#include "Enums.h"
#include <algorithm>

namespace FDSHA {

    /**
     * @brief Represents a single fuzzy rule: IF (Mmax AND R AND F) THEN (PGA)
     */
    struct FuzzyRule {
        MagnitudeTerm Mmax;
        DistanceTerm R;
        FaultTypeTerm F;
        PGATerm PGA; // Consequent

        FuzzyRule(MagnitudeTerm m, DistanceTerm r, FaultTypeTerm f, PGATerm p)
            : Mmax(m), R(r), F(f), PGA(p) {}

        /**
         * @brief Calculates rule's firing strength (alpha-cut) using MIN operator (T-norm).
         */
        double getFiringStrength(double mmaxDeg, double rDeg, double fDeg) const {
            return std::min({mmaxDeg, rDeg, fDeg});
        }
    };

} // namespace FDSHA

#endif // FUZZYRULE_H
