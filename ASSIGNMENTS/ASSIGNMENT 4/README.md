# DSA01 – Object Oriented Programming with C++ (CO4)
## Assignment 4: Designing Reusable Class Hierarchies

* **Student Name:** Tharika S
* **Register Number:** 192521140
* **Course Code:** DSA01 (Course Outcome: CO4)
* **Submission Date:** 21/11/2026
* **GitHub Repository:** `DSA01-192521140-Assignment4` (`https://github.com/TharikaS/DSA01-192521140-Assignment4`)
* **Bloom's Level Assessed:** K5 – Evaluate (Total Marks: 50)

---

## Compiler & Build Environment

* **Compiler:** `g++` (GNU C++ Compiler)
* **Version:** `g++ (Debian 12.2.0-14+deb12u1) 12.2.0`
* **Standard & Flags:** `g++ -std=c++17 -Wall -Wextra <source.cpp> -o <executable>`
* **AddressSanitizer Forensics (Task 4):** `g++ -std=c++17 -g -fsanitize=address -Wall -Wextra <source.cpp> -o <executable>`

---

## Steps to Compile and Run Each Task

1. Open a terminal inside any task folder (e.g., `cd Task01_Class_Design_Review`).
2. Compile with `g++ -std=c++17 -Wall -Wextra <filename.cpp> -o prog` (add `-g -fsanitize=address` for Task 4 leak forensics).
3. Run `./prog` and verify output against `output.txt` and `screenshot.png`.

---

## Folder Structure & Task Result Summary

* **`Task01_Class_Design_Review/`** — Diagnoses duplicated payroll classes, refactors into `Staff -> SalariedStaff -> {Professor, LabAssistant, VisitingResearcher}` and `Staff -> GuestFaculty` with virtual `pay()`, and compares against a monolithic `switch` struct.
* **`Task02_University_Hierarchy_Diamond/`** — Models `Person`, `Student`, `Staff`, `TeachingAssistant` (virtual inheritance resolving the diamond problem), and `ResearchScholar`; verifies `Person Student Staff TA` output and compares `sizeof` against composition (`ComposedTA`).
* **`Task03_Constructors_Member_Classes/`** — Traces base-class, member-class (`Address`, `Course`), and derived-class construction/destruction order (`Vehicle Engine Car | ~Car ~Engine ~Vehicle`), completes `TODO 1` (`192311001 Kavya (19) Salem-636001`), captures `-Wreorder` warning when initializer order is swapped, and compares virtual vs non-virtual `sizeof`.
* **`Task04_Derived_Pointers_Forensics/`** — Captures AddressSanitizer leak report caused by missing `virtual ~Account()`, proves non-virtual dispatch (`3.5`) and object slicing (`copy.vrate() == 3.5`), and repairs with `virtual`, `override`, `virtual ~Account()`, and `std::unique_ptr<Account>`.
* **`Task05_Object_Pointers_This/`** — Completes `Cart::add` and `Cart::setDiscount` using `this` and `*this` (`324.00`), demonstrates all four ways to access objects, and finds the highest-total cart across an array of `Cart*` pointers via pointer arithmetic.
* **`Task06_Design_Challenge_Fleet/`** — Implements extensible `Vehicle` hierarchy (`Bicycle`, `MotorVehicle -> {TwoWheeler, Car, ElectricCar, ElectricBus}`) with `ServiceDate` composition, polymorphic `computeCharge()`, and open-closed extension (`ElectricBus`) without modifying existing classes.
