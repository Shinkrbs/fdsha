// File: FDSHAEngine.cpp

#include "FDSHAEngine.h"
#include <iostream>
#include <sstream>
#include <algorithm> // Required for std::min, std::max

namespace FDSHA {

    // I. CONCRETE FUZZY SET IMPLEMENTATIONS
    class TriangularFuzzySet : public FuzzySet {
    private:
        double a, b, c;

    public:
        TriangularFuzzySet(std::string name, double a_val, double b_val, double c_val) {
            Name = name; a = a_val; b = b_val; c = c_val;
        }

        double getMembershipDegree(double x) const override {
            if (x <= a || x >= c) return 0.0;
            if (x == b) return 1.0;
            if (x > a && x < b) return (x - a) / (b - a);
            if (x > b && x < c) return (c - x) / (c - b);
            return 0.0;
        }
    };

    class TrapezoidalFuzzySet : public FuzzySet {
    private:
        double a, b, c, d;

    public:
        TrapezoidalFuzzySet(std::string name, double a_val, double b_val, double c_val, double d_val) {
            Name = name; a = a_val; b = b_val; c = c_val; d = d_val;
        }

        double getMembershipDegree(double x) const override {
            if (x <= a || x >= d) return 0.0;
            if (x >= b && x <= c) return 1.0;
            if (x > a && x < b) return (x - a) / (b - a);
            if (x > c && x < d) return (d - x) / (d - c);
            return 0.0;
        }
    };

    // II. ENUM TO STRING HELPERS
    std::string FDSHAEngine::enumToString(MagnitudeTerm t) const {
        switch (t) {
            case MagnitudeTerm::Short: return "Short";
            case MagnitudeTerm::Medium: return "Medium";
            case MagnitudeTerm::Large: return "Large";
            case MagnitudeTerm::VeryLarge: return "VeryLarge";
            case MagnitudeTerm::VeryVeryLarge: return "VeryVeryLarge";
            default: return "";
        }
    }
    
    std::string FDSHAEngine::enumToString(DistanceTerm t) const {
        switch (t) {
            case DistanceTerm::Near: return "Near";
            case DistanceTerm::Medium: return "Medium";
            case DistanceTerm::Far: return "Far";
            case DistanceTerm::VeryFar: return "VeryFar";
            default: return "";
        }
    }
    
    std::string FDSHAEngine::enumToString(FaultTypeTerm t) const {
        switch (t) {
            case FaultTypeTerm::Normal: return "Normal";
            case FaultTypeTerm::Oblique: return "Oblique";
            case FaultTypeTerm::Thrust: return "Thrust";
            default: return "";
        }
    }
    
    std::string FDSHAEngine::enumToString(PGATerm t) const {
        switch (t) {
            case PGATerm::VeryLow: return "VeryLow";
            case PGATerm::Low: return "Low";
            case PGATerm::Medium: return "Medium";
            case PGATerm::Much: return "Much";
            case PGATerm::VeryMuch: return "VeryMuch";
            case PGATerm::VeryVeryMuch: return "VeryVeryMuch";
            default: return "";
        }
    }

    // III. ENGINE SETUP (Constructors/Destructor)
    FDSHAEngine::FDSHAEngine() {
        initializeFuzzySets();
        initializeRules();
    }

    FDSHAEngine::~FDSHAEngine() {
        for (auto const& [key, val] : MmaxSets) delete val;
        for (auto const& [key, val] : RSets) delete val;
        for (auto const& [key, val] : FSets) delete val;
        for (auto const& [key, val] : PGASets) delete val;
    }

    // IV. INITIALIZATION LOGIC
    void FDSHAEngine::initializeFuzzySets() {
        // 1. Mmax Sets [4.5, 8.5]
        MmaxSets["Short"]           = new TrapezoidalFuzzySet("Short", 4.5, 4.5, 5.0, 5.5);
        MmaxSets["Medium"]          = new TriangularFuzzySet("Medium", 5.0, 5.7, 6.4);
        MmaxSets["Large"]           = new TriangularFuzzySet("Large", 6.0, 6.9, 7.8);
        MmaxSets["VeryLarge"]       = new TriangularFuzzySet("VeryLarge", 7.5, 8.0, 8.5);
        MmaxSets["VeryVeryLarge"]   = new TrapezoidalFuzzySet("VeryVeryLarge", 8.1, 8.5, 8.5, 8.5);

        // 2. R Sets [0, 200] km
        RSets["Near"]               = new TrapezoidalFuzzySet("Near", 0.0, 0.0, 10.0, 30.0);
        RSets["Medium"]             = new TriangularFuzzySet("Medium", 10.0, 40.0, 70.0);
        RSets["Far"]                = new TriangularFuzzySet("Far", 50.0, 100.0, 150.0);
        RSets["VeryFar"]            = new TrapezoidalFuzzySet("VeryFar", 130.0, 170.0, 200.0, 200.0);

        // 3. F Sets [-0.1, 0.1]
        FSets["Normal"]             = new TrapezoidalFuzzySet("Normal", -0.1, -0.1, -0.05, 0.0);
        FSets["Oblique"]            = new TriangularFuzzySet("Oblique", -0.05, 0.0, 0.05);
        FSets["Thrust"]             = new TrapezoidalFuzzySet("Thrust", 0.0, 0.05, 0.1, 0.1);

        // 4. PGA Sets [0, 0.9]g
        PGASets["VeryLow"]          = new TrapezoidalFuzzySet("VeryLow", 0.0, 0.0, 0.05, 0.15);
        PGASets["Low"]              = new TriangularFuzzySet("Low", 0.05, 0.18, 0.30);
        PGASets["Medium"]           = new TriangularFuzzySet("Medium", 0.20, 0.35, 0.50);
        PGASets["Much"]             = new TriangularFuzzySet("Much", 0.40, 0.58, 0.75);
        PGASets["VeryMuch"]         = new TriangularFuzzySet("VeryMuch", 0.60, 0.78, 0.90);
        PGASets["VeryVeryMuch"]     = new TrapezoidalFuzzySet("VeryVeryMuch", 0.80, 0.9, 0.9, 0.9);
    }

    void FDSHAEngine::initializeRules() {
        // Total: 60 Rules (3 Fault Types * 4 Distances * 5 Magnitudes)

        // I. IF Fault Type (F) is NORMAL
        // R is Near (N)
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Near, FaultTypeTerm::Normal, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Near, FaultTypeTerm::Normal, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Near, FaultTypeTerm::Normal, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Near, FaultTypeTerm::Normal, PGATerm::VeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Near, FaultTypeTerm::Normal, PGATerm::VeryMuch);

        // R is Medium (M)
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Medium, FaultTypeTerm::Normal, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Medium, FaultTypeTerm::Normal, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Medium, FaultTypeTerm::Normal, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Medium, FaultTypeTerm::Normal, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Medium, FaultTypeTerm::Normal, PGATerm::VeryMuch);

        // R is Far (F)
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Far, FaultTypeTerm::Normal, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Far, FaultTypeTerm::Normal, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Far, FaultTypeTerm::Normal, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Far, FaultTypeTerm::Normal, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Far, FaultTypeTerm::Normal, PGATerm::Much);

        // R is Very Far (VF)
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::VeryFar, FaultTypeTerm::Normal, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::VeryFar, FaultTypeTerm::Normal, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::VeryFar, FaultTypeTerm::Normal, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::VeryFar, FaultTypeTerm::Normal, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::VeryFar, FaultTypeTerm::Normal, PGATerm::Medium);

        // II. IF Fault Type (F) is OBLIQUE
        // R is Near (N)
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Near, FaultTypeTerm::Oblique, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Near, FaultTypeTerm::Oblique, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Near, FaultTypeTerm::Oblique, PGATerm::VeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Near, FaultTypeTerm::Oblique, PGATerm::VeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Near, FaultTypeTerm::Oblique, PGATerm::VeryVeryMuch);

        // R is Medium (M)
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Medium, FaultTypeTerm::Oblique, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Medium, FaultTypeTerm::Oblique, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Medium, FaultTypeTerm::Oblique, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Medium, FaultTypeTerm::Oblique, PGATerm::VeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Medium, FaultTypeTerm::Oblique, PGATerm::VeryMuch);

        // R is Far (F)
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Far, FaultTypeTerm::Oblique, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Far, FaultTypeTerm::Oblique, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Far, FaultTypeTerm::Oblique, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Far, FaultTypeTerm::Oblique, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Far, FaultTypeTerm::Oblique, PGATerm::VeryMuch);

        // R is Very Far (VF)
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::VeryFar, FaultTypeTerm::Oblique, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::VeryFar, FaultTypeTerm::Oblique, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::VeryFar, FaultTypeTerm::Oblique, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::VeryFar, FaultTypeTerm::Oblique, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::VeryFar, FaultTypeTerm::Oblique, PGATerm::Much);

        // III. IF Fault Type (F) is THRUST
        // R is Near (N)
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Near, FaultTypeTerm::Thrust, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Near, FaultTypeTerm::Thrust, PGATerm::VeryMuch);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Near, FaultTypeTerm::Thrust, PGATerm::VeryVeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Near, FaultTypeTerm::Thrust, PGATerm::VeryVeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Near, FaultTypeTerm::Thrust, PGATerm::VeryVeryMuch);

        // R is Medium (M)
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Medium, FaultTypeTerm::Thrust, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Medium, FaultTypeTerm::Thrust, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Medium, FaultTypeTerm::Thrust, PGATerm::VeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Medium, FaultTypeTerm::Thrust, PGATerm::VeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Medium, FaultTypeTerm::Thrust, PGATerm::VeryVeryMuch);

        // R is Far (F)
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Far, FaultTypeTerm::Thrust, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Far, FaultTypeTerm::Thrust, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Far, FaultTypeTerm::Thrust, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Far, FaultTypeTerm::Thrust, PGATerm::VeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Far, FaultTypeTerm::Thrust, PGATerm::VeryMuch);

        // R is Very Far (VF)
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::VeryFar, FaultTypeTerm::Thrust, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::VeryFar, FaultTypeTerm::Thrust, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::VeryFar, FaultTypeTerm::Thrust, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::VeryFar, FaultTypeTerm::Thrust, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::VeryFar, FaultTypeTerm::Thrust, PGATerm::VeryMuch);
    }

    // V. CORE INFERENCE AND DEFUZZIFICATION LOGIC 
    double FDSHAEngine::findPGA(double mmaxInput, double rInput, double fInput) {
        // 1. FUZZIFICATION
        std::map<std::string, double> mmaxMemberships;
        for (auto const& [name, set] : MmaxSets) mmaxMemberships[name] = set->getMembershipDegree(mmaxInput);
        
        std::map<std::string, double> rMemberships;
        for (auto const& [name, set] : RSets) rMemberships[name] = set->getMembershipDegree(rInput);
        
        std::map<std::string, double> fMemberships;
        for (auto const& [name, set] : FSets) fMemberships[name] = set->getMembershipDegree(fInput);

        // 2. INFERENCE & AGGREGATION (Max-Min Method)
        std::map<PGATerm, double> aggregatedConsequents;

        for (const auto& rule : Rules) {
            double mmaxDeg = mmaxMemberships.at(enumToString(rule.Mmax));
            double rDeg = rMemberships.at(enumToString(rule.R));
            double fDeg = fMemberships.at(enumToString(rule.F));

            double alpha = rule.getFiringStrength(mmaxDeg, rDeg, fDeg);

            PGATerm term = rule.PGA;
            if (aggregatedConsequents.find(term) == aggregatedConsequents.end() || alpha > aggregatedConsequents[term]) {
                aggregatedConsequents[term] = alpha; 
            }
        }

        // 3. DEFUZZIFICATION
        return defuzzifyCenterOfGravity(aggregatedConsequents);
    }
    
    double FDSHAEngine::defuzzifyCenterOfGravity(const std::map<PGATerm, double>& aggregatedConsequents) const {
        
        const double PGA_MIN = 0.0;
        const double PGA_MAX = 0.9;
        const int NUM_POINTS = 1000;
        const double STEP_SIZE = (PGA_MAX - PGA_MIN) / NUM_POINTS;
        
        double numerator = 0.0;
        double denominator = 0.0;

        for (int i = 0; i <= NUM_POINTS; ++i) {
            double x = PGA_MIN + i * STEP_SIZE;
            double aggregatedMembership = 0.0;

            for (auto const& [term, alpha] : aggregatedConsequents) {
                double baseMembership = PGASets.at(enumToString(term))->getMembershipDegree(x);
                double clippedMembership = std::min(baseMembership, alpha);
                aggregatedMembership = std::max(aggregatedMembership, clippedMembership);
            }

            numerator += x * aggregatedMembership;
            denominator += aggregatedMembership;
        }

        if (denominator == 0.0) {
            return (PGA_MIN + PGA_MAX) / 2.0; 
        }

        return numerator / denominator;
    }

} // namespace FDSHA