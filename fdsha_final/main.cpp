#include "FDSHAEngine.h"
#include <iostream>
#include <limits>
#include <cctype>
#include <string>

using namespace FDSHA;

// Helper function to handle input validation
void safeInput(double& value, const std::string& prompt) {
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cout << "Invalid input. Please enter a number." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << prompt;
    }
}

// provide a qualitative verdict based on the crisp PGA value
std::string getPGAVerdict(double pga) {
    if (pga < 0.10) {
        return "Negligible (Very Low Hazard)";
    } else if (pga < 0.25) {
        return "Low (Minor Structural Risk)";
    } else if (pga < 0.45) {
        return "Moderate (Significant Damage Likely)";
    } else if (pga < 0.65) {
        return "High (Major Structural Damage Expected)";
    } else if (pga < 0.80) {
        return "Very High (Severe Damage, Near Collapse)";
    } else {
        return "Extreme (Maximum Hazard, Catastrophic Damage)";
    }
}

int main() {

    std::cout << " Fuzzy Deterministic Seismic Hazard Analysis (FDSHA)  " << std::endl;
    FDSHAEngine engine;
    char continue_choice;

    do {
        // --- 1. Get User Inputs ---
        double Mmax_Input, R_Input, F_Input;
        // Prompt for Maximum Magnitude (Mmax)
        safeInput(Mmax_Input, "Enter Maximum Magnitude (Mmax, typically 4.5 to 8.5): ");

        // Prompt for Source-to-Site Distance (R)
        safeInput(R_Input, "Enter Source-to-Site Distance (R, in km, typically 0 to 200): ");

        // Prompt for Fault Type Index (F)
        safeInput(F_Input, "Enter Fault Type Index (F, e.g., Thrust: 0.08, Normal: -0.08): ");

        // --- 2. Run the Fuzzy Inference System ---
        double PGA_Output = engine.findPGA(Mmax_Input, R_Input, F_Input);
        std::string verdict = getPGAVerdict(PGA_Output); // Get the qualitative verdict

        // --- 3. Display Results ---
        std::cout << "\n--- ANALYSIS RESULT ---" << std::endl;
        std::cout << "Inputs Used:" << std::endl;
        std::cout << "  - Mmax (Magnitude): " << Mmax_Input << std::endl;
        std::cout << "  - R (Distance):     " << R_Input << " km" << std::endl;
        std::cout << "  - F (Fault Index):  " << F_Input << std::endl;

        std::cout << "\nCalculated Peak Ground Acceleration (PGA): "
                  << PGA_Output << " g" << std::endl;
        std::cout << "Final Hazard Verdict: " << verdict << std::endl;
        std::cout << "-----------------------" << std::endl;

        // --- 4. Prompt to continue ---
        std::cout << "\nDo you want to run another analysis? (Enter 'y' to continue, any other key to end): ";
        // Clear previous newline characters before reading the choice
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Read only the first character
        if (!(std::cin >> continue_choice)) {
            continue_choice = 'n'; // Default to exit on read failure
        }

        // Convert to lowercase for comparison
        continue_choice = std::tolower(static_cast<unsigned char>(continue_choice));

    } while (continue_choice == 'y');

    std::cout << "\nProgram ended." << std::endl;
    return 0;
}
