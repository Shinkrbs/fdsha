#include "FDSHAEngine.h"
#include <iostream>
#include <limits>

int main() {
    using namespace FDSHA;

    std::cout << "  Fuzzy Deterministic Seismic Hazard Analysis (FDSHA)  " << std::endl;

    // --- 1. Get User Inputs ---
    double Mmax_Input, R_Input, F_Input;

    std::cout << "\nPlease enter the required seismic parameters:\n" << std::endl;

    // Prompt for Maximum Magnitude (Mmax)
    std::cout << "Enter Maximum Magnitude (Mmax, typically 4.5 to 8.5): ";
    while (!(std::cin >> Mmax_Input)) {
        std::cout << "Invalid input. Please enter a number for Mmax: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Prompt for Source-to-Site Distance (R)
    std::cout << "Enter Source-to-Site Distance (R, in km, typically 0 to 200): ";
    while (!(std::cin >> R_Input)) {
        std::cout << "Invalid input. Please enter a number for R: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Prompt for Fault Type Index (F)
    std::cout << "Enter Fault Type Index (F, e.g., Thrust: 0.08, Normal: -0.08): ";
    while (!(std::cin >> F_Input)) {
        std::cout << "Invalid input. Please enter a number for F: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "\nInitializing FDSHA Fuzzy Engine..." << std::endl;
    FDSHAEngine engine;

    // --- 2. Run the Fuzzy Inference System ---
    double PGA_Output = engine.findPGA(Mmax_Input, R_Input, F_Input);

    // --- 3. Display Results ---
    std::cout << "\n--- Seismic Hazard Analysis Results ---" << std::endl;
    std::cout << "Inputs Used:" << std::endl;
    std::cout << "  - Mmax (Magnitude): " << Mmax_Input << std::endl;
    std::cout << "  - R (Distance):     " << R_Input << " km" << std::endl;
    std::cout << "  - F (Fault Index):  " << F_Input << std::endl;

    std::cout << "\nCalculated Peak Ground Acceleration (PGA): "
              << PGA_Output << " g" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    return 0;
}
