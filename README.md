# Fuzzy Deterministic Seismic Hazard Analysis (FDSHA)

[cite_start]This project is a C++ implementation of a Fuzzy Logic Expert System created for the CSci 141 - Intelligent Systems course[cite: 2].

## About The Project

Fuzzy Deterministic Seismic Hazard Analysis (FDSHA) is a method that uses human-like, IF-THEN rules and fuzzy logic to calculate the Peak Ground Acceleration (PGA) at a site.

[cite_start]Instead of relying on complex, rigid formulas, the program takes general, descriptive information about a fault's magnitude, its distance to a site, and its type to calculate a precise measure of ground shaking (PGA)[cite: 7].


---

## How It Works

The system uses a fuzzy logic engine to process inputs and determine the final hazard level.

### Input Variables
[cite_start]The program accepts three numerical (crisp) inputs from the user[cite: 176]:
* [cite_start]**Maximum Magnitude (Mmax):** The earthquake's magnitude on the Richter Scale (e.g., `4.5` to `8.5`)[cite: 10].
* [cite_start]**Source-to-Site Distance (R):** The distance from the fault in kilometers (e.g., `0` to `200`)[cite: 10].
* [cite_start]**Fault Type (F):** A normalized index representing the fault type (e.g., Normal `≈ -0.08`, Thrust `≈ 0.08`)[cite: 10, 188].

### Output Variable
[cite_start]Based on the inputs and its rule base, the system calculates one output[cite: 176]:
* [cite_start]**Peak Ground Acceleration (PGA):** The final measure of the seismic hazard, expressed in units of g (acceleration of gravity)[cite: 12].

[cite_start]The program flow involves **fuzzification** (converting numbers to fuzzy terms), **inference** (applying rules), **aggregation** (combining results), and **defuzzification** (converting the fuzzy result back to a number)[cite: 176].

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

Once running, the program will prompt you to enter the three input values. [cite_start]For example, using the data from the "Low Hazard" test case[cite: 180]:

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

[cite_start][cite: 190, 191, 192, 193, 194, 195, 196]

---

## Reference

This work is based on the methods described in the following paper:

* Afsari, N., Abdipour, M. S., & Taghizadeh-Farahmand, F. (2022). Seismic hazard analysis from deterministic method using fuzzy logic in Anzali Port. [cite_start]*Earth Science Informatics, 15*(2), 793-806. [cite: 250, 251]
