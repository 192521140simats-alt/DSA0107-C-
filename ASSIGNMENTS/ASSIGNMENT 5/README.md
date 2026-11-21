# DSA01-192521140-Assignment5 — DSA0107: Object Oriented Programming with C++

## Student & Submission Details
| Field | Value |
| :--- | :--- |
| **Student Name** | Tharika S |
| **Register Number** | 192521140 |
| **Course Code & Title** | DSA0107 — Object Oriented Programming with C++ |
| **Assignment** | Assignment 5 – CO5 (Reliable Software with Runtime Polymorphism and Exceptions) |
| **Submission Date** | 21/11/2026 |
| **GitHub Repository Link** | [https://github.com/TharikaS/DSA0107/tree/assignments](https://github.com/TharikaS/DSA0107/tree/assignments) |
| **Compiler & Version** | `g++ (Debian 12.2.0-14+deb12u1) 12.2.0` |
| **Standard Build Command** | `g++ -std=c++17 -Wall -Wextra <source.cpp> -o <executable>` |

---

## Complete Task Directory (Part A: A1–A5 & Part B: B1–B4)

### Part A — Architectural Design & Verification
1. **`TaskA1_PolymorphicBillHierarchy/`**
   - **Files:** `a1_bill_hierarchy.cpp`, `a1_design_pseudocode.txt`, `a1_uml_bill_hierarchy.png`, `input.txt`, `a1_bill_hierarchy_output.txt`, `a1_bill_hierarchy_output.png`
   - **Compile & Run:** `g++ -std=c++17 -Wall -Wextra a1_bill_hierarchy.cpp -o a1 && ./a1`
   - **Result:** Demonstrates abstract `Bill` interface and polymorphic daily aggregation across all 4 bill types (`Rs. 80200.00`).
2. **`TaskA2_RuntimeBinding/`**
   - **Files:** `a2_predict_virtual.cpp`, `a2_no_virtual_dtor.cpp`, `a2_vtable_layout.png`, `input.txt`, output texts & PNG screenshots
   - **Compile & Run:** `g++ -std=c++17 -Wall -Wextra a2_predict_virtual.cpp -o a2 && ./a2`
   - **Result:** Proves dynamic dispatch through `show()` (`500 ~OPBill ~Bill`) and captures AddressSanitizer leak report when `virtual` is removed from `~Bill()`.
3. **`TaskA3_AbstractPayerDesign/`**
   - **Files:** `a3_abstract_payers.cpp`, `a3_uml_payer_hierarchy.png`, `input.txt`, `a3_abstract_payers_output.txt`, `a3_abstract_payers_output.png`
   - **Compile & Run:** `g++ -std=c++17 -Wall -Wextra a3_abstract_payers.cpp -o a3 && ./a3`
   - **Result:** Validates `SelfPay`, `Insurance`, `GovernmentScheme`, and Open-Closed extension `CorporateTieUpPayer` without modifying existing classes.
4. **`TaskA4_ExceptionStrategy/`**
   - **Files:** `a4_exception_hierarchy.cpp`, `a4_exception_hierarchy.png`, `input.txt`, `a4_exception_hierarchy_output.txt`, `a4_exception_hierarchy_output.png`
   - **Compile & Run:** `g++ -std=c++17 -Wall -Wextra a4_exception_hierarchy.cpp -o a4 && ./a4`
   - **Result:** Tests custom `BillingError` subclasses (`PatientRecordMissingError`, `NegativeChargeError`, `UnknownPackageError`, `ClaimError`) and `noexcept` traits.
5. **`TaskA5_StackUnwinding/`**
   - **Files:** `a5_predict_unwinding.cpp`, `input.txt`, `a5_predict_unwinding_output.txt`, `a5_predict_unwinding_output.png`
   - **Compile & Run:** `g++ -std=c++17 -Wall -Wextra a5_predict_unwinding.cpp -o a5 && ./a5`
   - **Result:** Confirms LIFO RAII destruction order during stack unwinding (`~f ~main caught 42`).

### Part B — Implementation & Experimental Investigation
6. **`TaskB1_PolymorphicBilling/`** — Completed `TODO 1–3`, full 4-bill × 3-payer settlement matrix, and non-virtual `total()` demonstration.
7. **`TaskB2_ErrorConditions/`** — Rethrow prediction, completed `approve`/`settle` TODOs, `throw;` vs `throw e;` object-slicing proof, and 6 fault-injection tests including `std::bad_alloc` and `catch(...)`.
8. **`TaskB3_CostBenchmark/`** — `-O2` scaling benchmarks across 1,000, 1,000,000, and 10,000,000 bills (`Virtual` vs `Switch` vs `std::variant`) and 1,000,000 error checks (`ReturnCode` vs `Exception` at 0%, 1%, 50% fault rates).
9. **`TaskB4_ProductionExtension/`** — `TelemedicineBill` + `CorporateTieUpPayer` extension verified with clean AddressSanitizer (`-fsanitize=address`) output.
