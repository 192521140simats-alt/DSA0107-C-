# DSA01 – Object Oriented Programming with C++ (CO1)
## Assignment 1: Design, Implement and Validate the Fare Logic of a City Metro Smart-Card System

* **Student Name:** Tharika S
* **Register Number:** 192521140
* **Course & Outcome:** Object Oriented Programming with C++ (`DSA01` — `CO1`)
* **Submission Date:** 21/11/2026
* **GitHub Repository:** `DSA01-192521140-Assignment1` (`https://github.com/TharikaS/DSA01-192521140-Assignment1`)
* **Bloom's Level Assessed:** K5 – Evaluate (Total Marks: 50)

---

## Compiler & Build Environment

* **Compiler:** `g++` (GNU C++ Compiler)
* **Version:** `g++ (Debian 12.2.0-14+deb12u1) 12.2.0`
* **Standard & Flags:** `g++ -std=c++17 -Wall -Wextra <source.cpp> -o <executable>`

---

## Steps to Compile and Run Each Task

1. Navigate into any task folder (`Task01_OO_Analysis` through `Task12_Design_Challenge`).
2. Compile with `g++ -std=c++17 -Wall -Wextra <file.cpp> -o prog`.
3. Run `./prog` and compare results against `output.txt` and `screenshot.png`.

---

## Task Summaries

* **Task 1 (`Task01_OO_Analysis`)** — Models `SmartCard`, `FareTable`, and `Zone`/`ConcessionType` enums; enforces `Rs 50.00` minimum remaining balance and peak surcharge (`08:00–09:59`, `17:00–19:59`).
* **Task 2 (`Task02_Tokens_Constants`)** — Classifies C++ tokens, compares `#define`, `const`, `constexpr`, and `enum class`, and centralizes fare constants in one place.
* **Task 3 (`Task03_Data_Types`)** — Reports `sizeof` and `<climits>` bounds, demonstrates 32-bit `int` overflow at 3,000,000 journeys/day, and measures `double` rounding drift vs integer paise.
* **Task 4 (`Task04_Implicit_Conversions`)** — Predicts and verifies integer division (`7/2 == 3`), `char` promotion, `bool` conversion, and signed-vs-unsigned `-1 < 1u` trap, plus explicit `static_cast` + brace initialization.
* **Task 5 (`Task05_Operators_Precedence`)** — Predicts and traces precedence, associativity, postfix/prefix operators, `/`/`%` on negative numbers, and lookup table vs logical expression peak checks.
* **Task 6 (`Task06_Control_Structures`)** — Provides SIMATS-standard pseudocode, completes `TODO 1` and `TODO 2` with `switch` and integer paise, and tests exact boundary hours `10:00` and `20:00`.
* **Task 7 (`Task07_Procedural_vs_OO`)** — Contrasts procedural functions against encapsulated `SmartCard::canTravel()` and `SmartCard::deduct()`.
* **Task 8 (`Task08_Safe_IO`)** — Recovers from non-numeric `cin` failures using `clear()` and `ignore()`, and formats fare tables with `<iomanip>`.
* **Task 9 (`Task09_Implement_Test`)** — Executes boundary tests (`08:00`, `10:00`, `17:00`, `20:00`, exact Rs 50 remaining), invalid/negative inputs, and a 5-journey manual sum (`8500` paise).
* **Task 10 (`Task10_Expect_vs_Execute`)** — Compares 20,000, 500,000, and 3,000,000 journey totals in `int`, `long long` paise, and `double` rupees.
* **Task 11 (`Task11_Final_Recommendation`)** — Recommends `constexpr` paise constants, `enum class Zone`, and encapsulated `SmartCard` for network scale.
* **Task 12 (`Task12_Design_Challenge`)** — Adapts the design for Zone 4 (`Airport`, Rs 60), 10% non-stacking weekend discount, and two-zone `MonthlyPass`.
