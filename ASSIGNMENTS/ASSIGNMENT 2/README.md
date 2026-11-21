# DSA0107 – Object Oriented Programming with C++ (CO2)
## Assignment Submission Repository

* **Student Name:** Tharika S
* **Register Number:** 192521140
* **Course Code:** DSA0107
* **Submission Date:** 21/11/2026
* **GitHub Repository Link:** https://github.com/TharikaS/DSA0107/tree/assignments
* **Bloom's Level Assessed:** K5 – Evaluate (Total Marks: 50)

---

## Compiler & Environment Details

* **Compiler:** `g++` (GNU C++ Compiler)
* **Compiler Version:** `g++ (Debian 12.2.0-14+deb12u1) 12.2.0`
* **Standard:** C++17 (`-std=c++17`)
* **Compile Commands Used:**
  * Standard build & warnings check: `g++ -std=c++17 -Wall -Wextra <source.cpp> -o <executable>`
  * Optimised build for benchmarks (Q4/Q6/Q7): `g++ -std=c++17 -O2 -Wall -Wextra <source.cpp> -o <executable>`
  * Unoptimised baseline build for inline study (Q6): `g++ -std=c++17 -O0 -Wall -Wextra <source.cpp> -o <executable>`

---

## Steps to Compile and Run Each Task

1. Navigate to a task directory (e.g., `Task01_Call_By_Value_Ref_Pointer`).
2. Compile the desired `.cpp` file using `g++ -std=c++17 -Wall -Wextra <file.cpp> -o prog`.
3. Run the compiled binary (`./prog`) and compare against `input.txt` and `output.txt`.
4. Inspect `compiler_log.txt` and `screenshot.png` for exact compiler diagnostics and terminal output.

---

## Repository Folder Structure & Task Result Notes

* **`Task01_Call_By_Value_Ref_Pointer/`** — Implements Hostel Fee Concession Updater via pass-by-value, pass-by-reference, and pass-by-pointer; includes pre-execution output prediction (`1 12 13`, `1 100`, `16 13 6`), `TODO 1` completion (`45000` after value, `40500` after reference), and `Student` struct size comparison (`sizeof(Student)` vs pointer/reference).
* **`Task02_Return_By_Reference/`** — Demonstrates returning `int&` for `+2` moderation and left-hand assignment (`highestMarkRef() = 99`), captures GCC `-Wreturn-local-addr` warning on returning a local stack variable reference, explains `std::vector` reallocation invalidation, and compares `int` index and `int*` pointer alternatives.
* **`Task03_Default_Args_Overloading/`** — Demonstrates overload ambiguity in the initial design (`charge(2.5)`), provides an unambiguous overloaded design with default arguments across `double` kg, `int` grams, and `Parcel`, and compares struct-based / template alternatives.
* **`Task04_Class_With_Array/`** — Specifies `SavingsAccount` with private `accountNumber`, `balance`, `transactions[10]`, and `count`, with `deposit()` inline and `withdraw()` / `miniStatement()` defined out-of-line via `::`, alongside circular buffer vs `std::deque` analysis.
* **`Task05_Static_Members_Object_Array/`** — Evaluates `Token` (`101 103 104 4`), completes `BusTicket` (`TODO 1` & `TODO 2`) for capacity `3` across an array of `4` passengers (`Asha`, `Bala`, `Chitra`, `Dev`) and two function calls, and compares global counter vs per-bus `TicketOffice` objects.
* **`Task06_Friend_And_Inline/`** — Completes `minutesBetween` and `earlier` as `friend` functions on `Time`, validates same-time and cross-noon test cases (`205 false`), benchmarks `10,000,000` calls with and without `inline` at `-O0` and `-O2`, and compares member functions and getters.
* **`Task07_Day4_Design_Challenge/`** — Diagnoses `O(k)` shift overhead and fixed 10-slot limit in `SavingsAccount`, defines measurable latency/capacity objectives, implements a configurable circular ring buffer (`RedesignedSavingsAccount`), and validates side-by-side over `500,000` deposits.
