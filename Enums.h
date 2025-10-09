#ifndef ENUMS_H
#define ENUMS_H

namespace FDSHA {
    enum class MagnitudeTerm { Short, Medium, Large, VeryLarge, VeryVeryLarge };
    enum class DistanceTerm { Near, Medium, Far, VeryFar };
    enum class FaultTypeTerm { Normal, Oblique, Thrust };
    enum class PGATerm { VeryLow, Low, Medium, Much, VeryMuch, VeryVeryMuch };
} 

#endif // ENUMS_H