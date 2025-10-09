#include "FDSHAEngine.h"
#include <iostream>

int main() {
    using namespace FDSHA;

    std::cout << "Initializing FDSHA Fuzzy Engine..." << std::endl;
    FDSHAEngine engine;

    // Scenario: A major earthquake close to the site on a high-stress fault.
    // Mmax (Maximum Magnitude): Large (7.2)
    // R (Source-to-Site Distance): Near (15 km)
    // F (Fault Type Index): Thrust (0.08)
    double Mmax_Input = 7.2;
    double R_Input = 15.0;
    double F_Input = 0.08;

    // Run the fuzzy inference system
    double PGA_Output = engine.findPGA(Mmax_Input, R_Input, F_Input);

    std::cout << "\n--- Seismic Hazard Analysis Results ---" << std::endl;
    std::cout << "Inputs: Mmax = " << Mmax_Input
              << ", R = " << R_Input << " km"
              << ", F (Thrust Index) = " << F_Input << std::endl;

    // The PGA value is a numerical representation of the seismic hazard level.
    std::cout << "\nCalculated Peak Ground Acceleration (PGA): "
              << PGA_Output << " g" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    return 0;
}
