#ifndef FUZZYSET_H
#define FUZZYSET_H

#include <string>

namespace FDSHA {

    class FuzzySet {
    public:
        std::string Name;
        virtual double getMembershipDegree(double crispValue) const = 0;
        virtual ~FuzzySet() = default;
    };

    class TriangularFuzzySet : public FuzzySet {
    private:
        double a, b, c;

    public:
        TriangularFuzzySet(std::string name, double a_val, double b_val, double c_val);
        double getMembershipDegree(double x) const override;
    };


    class TrapezoidalFuzzySet : public FuzzySet {
    private:
        double a, b, c, d;

    public:
        TrapezoidalFuzzySet(std::string name, double a_val, double b_val, double c_val, double d_val);
        double getMembershipDegree(double x) const override;
    };

} // namespace FDSHA

#endif // FUZZYSET_H