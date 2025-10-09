// File: FDSHAEngine.cpp

#include "FDSHAEngine.h"
#include <algorithm>
#include <cmath>
#include <iostream>

namespace FDSHA {

    // --- Constructor and Destructor ---
    FDSHAEngine::FDSHAEngine() {
        initializeFuzzySets();
        initializeRules();
    }

    FDSHAEngine::~FDSHAEngine() {
        // Cleanup dynamically allocated memory for all fuzzy sets
        for (auto const& [key, val] : MmaxSets) delete val;
        for (auto const& [key, val] : RSets) delete val;
        for (auto const& [key, val] : FSets) delete val;
        for (auto const& [key, val] : PGASets) delete val;
    }

    // --- Helper Functions (Implementation of Enum-to-String) ---
    // (Implementation for all four enumToString functions as provided in the single file solution)
    // ...

    // --- Initialization (Implementation of Fuzzy Sets) ---
    void FDSHAEngine::initializeFuzzySets() {
        // Mmax Sets [4.5, 8.5]
        MmaxSets["Short"] = new TrapezoidalFuzzySet("Short", 4.5, 4.5, 5.0, 5.5);
        MmaxSets["Medium"] = new TriangularFuzzySet("Medium", 5.0, 5.7, 6.4);
        MmaxSets["Large"] = new TriangularFuzzySet("Large", 6.0, 6.7, 7.4);
        MmaxSets["VeryLarge"] = new TriangularFuzzySet("VeryLarge", 7.0, 7.7, 8.1);
        MmaxSets["VeryVeryLarge"] = new TrapezoidalFuzzySet("VeryVeryLarge", 7.8, 8.3, 8.5, 8.5);

        // R Sets [0, 200]
        RSets["Near"] = new TrapezoidalFuzzySet("Near", 0.0, 0.0, 20.0, 40.0);
        RSets["Medium"] = new TriangularFuzzySet("Medium", 20.0, 50.0, 80.0);
        RSets["Far"] = new TriangularFuzzySet("Far", 60.0, 100.0, 140.0);
        RSets["VeryFar"] = new TrapezoidalFuzzySet("VeryFar", 120.0, 160.0, 200.0, 200.0);

        // F Sets [-0.1, 0.1]
        FSets["Normal"] = new TrapezoidalFuzzySet("Normal", -0.1, -0.1, -0.05, 0.0);
        FSets["Oblique"] = new TriangularFuzzySet("Oblique", -0.05, 0.0, 0.05);
        FSets["Thrust"] = new TrapezoidalFuzzySet("Thrust", 0.0, 0.05, 0.1, 0.1);

        // PGA Sets [0, 0.9]g
        PGASets["VeryLow"] = new TrapezoidalFuzzySet("VeryLow", 0.0, 0.0, 0.05, 0.15);
        PGASets["Low"] = new TriangularFuzzySet("Low", 0.05, 0.15, 0.25);
        PGASets["Medium"] = new TriangularFuzzySet("Medium", 0.15, 0.30, 0.45);
        PGASets["Much"] = new TriangularFuzzySet("Much", 0.35, 0.50, 0.65);
        PGASets["VeryMuch"] = new TriangularFuzzySet("VeryMuch", 0.55, 0.70, 0.85);
        PGASets["VeryVeryMuch"] = new TrapezoidalFuzzySet("VeryVeryMuch", 0.75, 0.85, 0.9, 0.9);
    }

     void FDSHAEngine::initializeRules() {
        // IF Fault Type (F) is NORMAL
        // R is Near (N):
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Near, FaultTypeTerm::Normal, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Near, FaultTypeTerm::Normal, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Near, FaultTypeTerm::Normal, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Near, FaultTypeTerm::Normal, PGATerm::VeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Near, FaultTypeTerm::Normal, PGATerm::VeryMuch);

        // R is Medium (M):
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Medium, FaultTypeTerm::Normal, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Medium, FaultTypeTerm::Normal, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Medium, FaultTypeTerm::Normal, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Medium, FaultTypeTerm::Normal, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Medium, FaultTypeTerm::Normal, PGATerm::VeryMuch);

        // R is Far (F):
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Far, FaultTypeTerm::Normal, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Far, FaultTypeTerm::Normal, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Far, FaultTypeTerm::Normal, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Far, FaultTypeTerm::Normal, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Far, FaultTypeTerm::Normal, PGATerm::Much);

        // R is Very Far (VF):
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::VeryFar, FaultTypeTerm::Normal, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::VeryFar, FaultTypeTerm::Normal, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::VeryFar, FaultTypeTerm::Normal, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::VeryFar, FaultTypeTerm::Normal, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::VeryFar, FaultTypeTerm::Normal, PGATerm::Medium);

        // IF Fault Type (F) is OBLIQUE
        // R is Near (N):
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Near, FaultTypeTerm::Oblique, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Near, FaultTypeTerm::Oblique, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Near, FaultTypeTerm::Oblique, PGATerm::VeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Near, FaultTypeTerm::Oblique, PGATerm::VeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Near, FaultTypeTerm::Oblique, PGATerm::VeryVeryMuch);

        // R is Medium (M):
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Medium, FaultTypeTerm::Oblique, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Medium, FaultTypeTerm::Oblique, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Medium, FaultTypeTerm::Oblique, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Medium, FaultTypeTerm::Oblique, PGATerm::VeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Medium, FaultTypeTerm::Oblique, PGATerm::VeryMuch);

        // R is Far (F):
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Far, FaultTypeTerm::Oblique, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Far, FaultTypeTerm::Oblique, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Far, FaultTypeTerm::Oblique, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Far, FaultTypeTerm::Oblique, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Far, FaultTypeTerm::Oblique, PGATerm::VeryMuch);

        // R is Very Far (VF):
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::VeryFar, FaultTypeTerm::Oblique, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::VeryFar, FaultTypeTerm::Oblique, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::VeryFar, FaultTypeTerm::Oblique, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::VeryFar, FaultTypeTerm::Oblique, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::VeryFar, FaultTypeTerm::Oblique, PGATerm::Much);

        // IF Fault Type (F) is THRUST
        // R is Near (N):
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Near, FaultTypeTerm::Thrust, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Near, FaultTypeTerm::Thrust, PGATerm::VeryMuch);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Near, FaultTypeTerm::Thrust, PGATerm::VeryVeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Near, FaultTypeTerm::Thrust, PGATerm::VeryVeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Near, FaultTypeTerm::Thrust, PGATerm::VeryVeryMuch);

        // R is Medium (M):
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Medium, FaultTypeTerm::Thrust, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Medium, FaultTypeTerm::Thrust, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Medium, FaultTypeTerm::Thrust, PGATerm::VeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Medium, FaultTypeTerm::Thrust, PGATerm::VeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Medium, FaultTypeTerm::Thrust, PGATerm::VeryVeryMuch);

        // R is Far (F):
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::Far, FaultTypeTerm::Thrust, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::Far, FaultTypeTerm::Thrust, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::Far, FaultTypeTerm::Thrust, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::Far, FaultTypeTerm::Thrust, PGATerm::VeryMuch);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::Far, FaultTypeTerm::Thrust, PGATerm::VeryMuch);

        // R is Very Far (VF):
        Rules.emplace_back(MagnitudeTerm::Short, DistanceTerm::VeryFar, FaultTypeTerm::Thrust, PGATerm::VeryLow);
        Rules.emplace_back(MagnitudeTerm::Medium, DistanceTerm::VeryFar, FaultTypeTerm::Thrust, PGATerm::Low);
        Rules.emplace_back(MagnitudeTerm::Large, DistanceTerm::VeryFar, FaultTypeTerm::Thrust, PGATerm::Medium);
        Rules.emplace_back(MagnitudeTerm::VeryLarge, DistanceTerm::VeryFar, FaultTypeTerm::Thrust, PGATerm::Much);
        Rules.emplace_back(MagnitudeTerm::VeryVeryLarge, DistanceTerm::VeryFar, FaultTypeTerm::Thrust, PGATerm::VeryMuch);
    }

    // --- Defuzzification ---
    double FDSHAEngine::defuzzifyCenterOfGravity(const std::map<PGATerm, double>& aggregatedConsequents) const {
        // The detailed COG numerical integration logic from the single-file solution
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

        if (denominator == 0.0) return (PGA_MIN + PGA_MAX) / 2.0;
        return numerator / denominator;
    }

    // --- Core Inference Process ---
    double FDSHAEngine::findPGA(double mmaxInput, double rInput, double fInput) {
        // 1. FUZZIFICATION
        std::map<std::string, double> mmaxMemberships;
        for (auto const& [name, set] : MmaxSets) mmaxMemberships[name] = set->getMembershipDegree(mmaxInput);
        
        std::map<std::string, double> rMemberships;
        for (auto const& [name, set] : RSets) rMemberships[name] = set->getMembershipDegree(rInput);
        
        std::map<std::string, double> fMemberships;
        for (auto const& [name, set] : FSets) fMemberships[name] = set->getMembershipDegree(fInput);

        // 2. INFERENCE & AGGREGATION (Max-Min)
        std::map<PGATerm, double> aggregatedConsequents;

        for (const auto& rule : Rules) {
            // Retrieve degrees
            double mmaxDeg = mmaxMemberships.at(enumToString(rule.Mmax));
            double rDeg = rMemberships.at(enumToString(rule.R));
            double fDeg = fMemberships.at(enumToString(rule.F));

            double alpha = rule.getFiringStrength(mmaxDeg, rDeg, fDeg); 
            PGATerm term = rule.PGA;
            
            // Aggregation (MAX)
            if (aggregatedConsequents.find(term) == aggregatedConsequents.end() || alpha > aggregatedConsequents[term]) {
                aggregatedConsequents[term] = alpha; 
            }
        }

        // 3. DEFUZZIFICATION
        return defuzzifyCenterOfGravity(aggregatedConsequents);
    }
} // namespace FDSHA