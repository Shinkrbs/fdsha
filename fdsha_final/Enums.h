#ifndef ENUMS_H_INCLUDED
#define ENUMS_H_INCLUDED

namespace FDSHA {

    // Input Variable: Maximum Magnitude (Mmax)
    enum class MagnitudeTerm { Short, Medium, Large, VeryLarge, VeryVeryLarge };

    // Input Variable: Source-to-Site Distance (R)
    enum class DistanceTerm { Near, Medium, Far, VeryFar };

    // Input Variable: Fault Type (F)
    enum class FaultTypeTerm { Normal, Oblique, Thrust };

    // Output Variable: Peak Ground Acceleration (PGA)
    enum class PGATerm { VeryLow, Low, Medium, Much, VeryMuch, VeryVeryMuch };

} // namespace FDSHA

#endif // ENUMS_H_INCLUDED
