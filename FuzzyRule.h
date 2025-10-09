#ifndef FUZZYRULE_H
#define FUZZYRULE_H

#include "Enums.h"
#include <algorithm> 

namespace FDSHA {

    struct FuzzyRule {
        MagnitudeTerm Mmax;
        DistanceTerm R;
        FaultTypeTerm F;
        PGATerm PGA; // Consequent

        FuzzyRule(MagnitudeTerm m, DistanceTerm r, FaultTypeTerm f, PGATerm p) 
            : Mmax(m), R(r), F(f), PGA(p) {}

        double getFiringStrength(double mmaxDeg, double rDeg, double fDeg) const {
            return std::min({mmaxDeg, rDeg, fDeg});
        }
    };

} // namespace FSHA

#endif // FUZZYRULE_H