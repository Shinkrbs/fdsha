#ifndef FUZZYSET_H_INCLUDED
#define FUZZYSET_H_INCLUDED
#include <string>

namespace FDSHA {

    /**
     * @brief Abstract base class for a Fuzzy Set and its Membership Function.
     */
    class FuzzySet {
    public:
        std::string Name;
        virtual double getMembershipDegree(double crispValue) const = 0;
        virtual ~FuzzySet() = default;
    };

    /**
     * @brief Implementation for a Triangular Membership Function.
     */
    class TriangularFuzzySet : public FuzzySet {
    private:
        double a, b, c;

    public:
        TriangularFuzzySet(std::string name, double a_val, double b_val, double c_val);
        double getMembershipDegree(double x) const override;
    };

    /**
     * @brief Implementation for a Trapezoidal Membership Function.
     */
    class TrapezoidalFuzzySet : public FuzzySet {
    private:
        double a, b, c, d;

    public:
        TrapezoidalFuzzySet(std::string name, double a_val, double b_val, double c_val, double d_val);
        double getMembershipDegree(double x) const override;
    };

} // namespace FDSHA

#endif // FUZZYSET_H_INCLUDED
