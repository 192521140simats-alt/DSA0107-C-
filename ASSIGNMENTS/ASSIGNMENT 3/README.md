# OBJECT ORIENTED PROGRAMMING WITH C++ — ASSIGNMENT 3 (CO3)

- **Student Name:** Tharika S
- **Register Number:** 192521140
- **Course Code:** DSA0107
- **Submission Date:** 21/11/2026
- **GitHub Repository Link:** https://github.com/TharikaS/DSA0107/tree/assignments
- **Compiler & Version:** `g++ (Debian 12.2.0-14+deb12u1) 12.2.0`
- **Standard Compile Command:** `g++ -std=c++17 -Wall -Wextra <source>.cpp -o <executable>`
- **AddressSanitizer Command:** `g++ -std=c++17 -Wall -Wextra -fsanitize=address -g <source>.cpp -o <executable>`

## Task Folders & Execution Summary

| Folder | Source Files | Run Command | Result Summary |
| :--- | :--- | :--- | :--- |
| `Q1/` | `book_records.cpp`, `exp_no_default.cpp`, `exp_reorder.cpp` | `./book_records` | Verified default, 1-arg `explicit`, and 4-arg constructors using member initializer lists & delegation; validated negative copy rejection, array error without default constructor, and `-Wreorder` warning. |
| `Q2/` | `prescription_complete.cpp`, `prescription_shallow.cpp`, `prescription_experiments.cpp` | `./prescription_complete` | Completed `TODO 1-3` (Rule of Three). Output matched `Ibuprofen ORS | Paracetamol Cetirizine | Paracetamol ORS`. ASan confirmed 0 leaks on deep copy and caught `heap-use-after-free` on shallow copy. |
| `Q3/` | `auditorium_booking.cpp`, `predict_logger.cpp`, `leak_demo.cpp` | `./auditorium_booking` | Verified LIFO stack/block destruction and `delete` heap destruction on 2D `char**` seat map; matched exact `Logger` prediction `+A +B -B copyAc use -Ac +P -P end -A `; measured footprints for `10x20`, `100x200`, `1000x2000`. |
| `Q4/` | `money_complete.cpp`, `money_billing.cpp` | `./money_complete` | Completed `TODO 1-2` (`+`, `==`, `<<`). Verified paise carry (`Rs 1.25`), negative subtraction guard, and zero drift over `1,000,000` additions (`Rs 100000.00` vs `double` drift `0.0000013329`). |
| `Q5/` | `playlist_timer.cpp`, `predict_counter.cpp` | `./playlist_timer` | Implemented prefix/postfix `++`, `==`, `<`, and `const`/non-`const` `operator[]` with bounds checking; verified `0:59:59 -> 1:00:00` rollover, `Counter` prediction `5 7 7`, and `-O0` vs `-O2` timing across `10,000,000` increments. |
| `Q6/` | `sms_text.cpp` | `./sms_text` | Implemented Rule of Three `Text` class (`+`, `==`, `!=`, `<<`) with self-assignment guard; verified 0 leaks under `-fsanitize=address`, counted copies in `a + b + c`, and benchmarked concatenations against `std::string`. |
| `Q7/` | `ac_impedance.cpp` | `./ac_impedance` | Designed `Complex` class from first principles (`+`, `-`, `*`, `/`, `==`, `<<`, `magnitude()`); verified series (`10 + 10j`) and parallel (`5 - 15j`) RLC impedances against hand calculations and handled division by zero safely. |
