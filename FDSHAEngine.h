#ifndef FDSHAENGINE_H
#define FDSHAENGINE_H

#include "Enums.h"
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

namespace FDSHA {

    struct FuzzyRule {
        MagnitudeTerm Mmax;
        DistanceTerm R;
        FaultTypeTerm F;
        PGATerm PGA; // Consequent

        // Constructor for easy initialization
        FuzzyRule(MagnitudeTerm m, DistanceTerm r, FaultTypeTerm f, PGATerm p) : Mmax(m), R(r), F(f), PGA(p) {}

        // Calculates rule's firing strength (alpha-cut) using MIN operator
        double getFiringStrength(double mmaxDeg, double rDeg, double fDeg) const {
            return std::min({mmaxDeg, rDeg, fDeg});
        }
    };

    class FuzzySet {
    public:
        std::string Name;
        // The core method to calculate degree of membership.
        virtual double getMembershipDegree(double x) const = 0;
        virtual ~FuzzySet() = default;
    };

    class FDSHAEngine {
    private:
        std::map<std::string, FuzzySet*> MmaxSets;
        std::map<std::string, FuzzySet*> RSets;
        std::map<std::string, FuzzySet*> FSets;
        std::map<std::string, FuzzySet*> PGASets;
        std::vector<FuzzyRule> Rules;
        
        void initializeFuzzySets();
        void initializeRules();

        // Helper to convert enums to strings
        std::string enumToString(MagnitudeTerm t) const;
        std::string enumToString(DistanceTerm t) const;
        std::string enumToString(FaultTypeTerm t) const;
        std::string enumToString(PGATerm t) const;

        // Defuzzification (to get the final crisp PGA)
        double defuzzifyCenterOfGravity(const std::map<PGATerm, double>& aggregatedConsequents) const;

    public:
        FDSHAEngine();
        ~FDSHAEngine();

        // Main function to run the entire process and return the final PGA
        double findPGA(double mmaxInput, double rInput, double fInput);
    };

} 

#endif // FDSHAENGINE_H