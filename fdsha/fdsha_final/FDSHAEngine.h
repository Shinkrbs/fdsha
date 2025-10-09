#ifndef FDSHAENGINE_H
#define FDSHAENGINE_H

#include "Enums.h"
#include "FuzzySet.h"
#include "FuzzyRule.h"
#include <map>
#include <vector>
#include <string>

namespace FDSHA {

    /**
     * @brief Engine class to perform the Mamdani Fuzzy Inference for FDSHA.
     */
    class FDSHAEngine {
    private:
        // Maps to hold fuzzy sets
        std::map<std::string, FuzzySet*> MmaxSets;
        std::map<std::string, FuzzySet*> RSets;
        std::map<std::string, FuzzySet*> FSets;
        std::map<std::string, FuzzySet*> PGASets;
        std::vector<FuzzyRule> Rules;

        // Initialization functions
        void initializeFuzzySets();
        void initializeRules();

        // Helper functions
        std::string enumToString(MagnitudeTerm t) const;
        std::string enumToString(DistanceTerm t) const;
        std::string enumToString(FaultTypeTerm t) const;
        std::string enumToString(PGATerm t) const;

        // Defuzzification
        double defuzzifyCenterOfGravity(const std::map<PGATerm, double>& aggregatedConsequents) const;

    public:
        FDSHAEngine();
        ~FDSHAEngine();

        /**
         * @brief Runs the fuzzy inference process to find the crisp PGA.
         */
        double findPGA(double mmaxInput, double rInput, double fInput);
    };

} // namespace FDSHA

#endif // FDSHAENGINE_H
