# Fuzzy Deterministic Seismic Hazard Analysis (FDSHA)

This project is a C++ implementation of a Fuzzy Logic Expert System created for the CSci 141 - Intelligent Systems course.

## About The Project

Fuzzy Deterministic Seismic Hazard Analysis (FDSHA) is a method that uses human-like, IF-THEN rules and fuzzy logic to calculate the Peak Ground Acceleration (PGA) at a site.

Instead of relying on complex, rigid formulas, the program takes general, descriptive information about a fault's magnitude, its distance to a site, and its type to calculate a precise measure of ground shaking (PGA).


---

## How It Works

The system uses a fuzzy logic engine to process inputs and determine the final hazard level.

### Input Variables
The program accepts three numerical (crisp) inputs from the user.
* **Maximum Magnitude (Mmax):** The earthquake's magnitude on the Richter Scale (e.g., `4.5` to `8.5`)
* **Source-to-Site Distance (R):** The distance from the fault in kilometers (e.g., `0` to `200`)
* **Fault Type (F):** A normalized index representing the fault type (e.g., Normal `≈ -0.08`, Thrust `≈ 0.08`)

### Output Variable
Based on the inputs and its rule base, the system calculates one output.
* **Peak Ground Acceleration (PGA):** The final measure of the seismic hazard, expressed in units of g (acceleration of gravity)

The program flow involves **fuzzification** (converting numbers to fuzzy terms), **inference** (applying rules), **aggregation** (combining results), and **defuzzification** (converting the fuzzy result back to a number).

---

## Getting Started

To get a local copy up and running, follow these simple steps.

### Prerequisites
You will need a C++ compiler, such as `g++`.

### Installation & Running
1.  Clone the repo:
    ```sh
    git clone [https://github.com/Shinkrbs/fdsha.git](https://github.com/Shinkrbs/fdsha.git)
    ```
2.  Navigate into the project directory:
    ```sh
    cd fdsha
    ```
3.  Compile the source code (replace `main.cpp` with your file's name):
    ```sh
    g++ main.cpp -o fdsha_final
    ```
4.  Run the program:
    ```sh
    ./fdsha_final
    ```

---

## Usage

Once running, the program will prompt you to enter the three input values. 

*For example, using the data from the "Low Hazard" test case.*

**Input:**

Enter Maximum Magnitude (Mmax, typically 4.5 to 8.5): 5

Enter Source-to-Site Distance (R, in km, typically 0 to 200): 180

Enter Fault Type Index (F, e.g., Thrust: 0.08, Normal: -0.08): -0.09

**Output:**

--- ANALYSIS RESULT ---

Inputs Used:

    Mmax (Magnitude): 5

    R (Distance):     180 km

    F (Fault Index):  -0.09
    
Calculated Peak Ground Acceleration (PGA): 0.0544111 g

Final Hazard Verdict: Negligible (Very Low Hazard)


---

## Reference

This work is based on the methods described in the following paper:

* Afsari, N., Abdipour, M. S., & Taghizadeh-Farahmand, F. (2022). Seismic hazard analysis from deterministic method using fuzzy logic in Anzali Port. *Earth Science Informatics, 15*(2), 793-806. 
