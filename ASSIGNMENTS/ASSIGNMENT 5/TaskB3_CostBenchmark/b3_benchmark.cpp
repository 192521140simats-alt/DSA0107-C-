#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <variant>
#include <chrono>
#include <stdexcept>
#include <cmath>

struct VBill {
    virtual ~VBill() = default;
    virtual double total() const = 0;
};
struct VOP : VBill {
    double c, t;
    VOP(double c, double t) : c(c), t(t) {}
    double total() const override { return c + t; }
};
struct VIP : VBill {
    int d; double r, s;
    VIP(int d, double r, double s) : d(d), r(r), s(s) {}
    double total() const override { return d * r + s; }
};
struct VDC : VBill {
    double pkg;
    explicit VDC(double p) : pkg(p) {}
    double total() const override { return pkg; }
};
struct VEM : VBill {
    double base, hr; int h;
    VEM(double b, double hr, int h) : base(b), hr(hr), h(h) {}
    double total() const override { return base + hr * h; }
};

enum class BillTag { OP, IP, DC, EM };
struct SBill {
    BillTag tag;
    double a, b, c;
    int n;
    double total() const {
        switch (tag) {
            case BillTag::OP: return a + b;
            case BillTag::IP: return n * a + b;
            case BillTag::DC: return a;
            case BillTag::EM: return a + b * n;
        }
        return 0.0;
    }
};

struct VarOP { double c, t; };
struct VarIP { int d; double r, s; };
struct VarDC { double pkg; };
struct VarEM { double base, hr; int h; };
using VarBill = std::variant<VarOP, VarIP, VarDC, VarEM>;

inline double visitTotal(const VarBill& vb) {
    return std::visit([](const auto& b) -> double {
        using T = std::decay_t<decltype(b)>;
        if constexpr (std::is_same_v<T, VarOP>) return b.c + b.t;
        else if constexpr (std::is_same_v<T, VarIP>) return b.d * b.r + b.s;
        else if constexpr (std::is_same_v<T, VarDC>) return b.pkg;
        else return b.base + b.hr * b.h;
    }, vb);
}

enum class Status { OK, NEGATIVE_AMOUNT };

Status validateReturnCode(double val, double& out) {
    if (val < 0.0) return Status::NEGATIVE_AMOUNT;
    out = val * 1.05;
    return Status::OK;
}

double validateException(double val) {
    if (val < 0.0) throw std::invalid_argument("negative");
    return val * 1.05;
}

int main() {
    using Clock = std::chrono::high_resolution_clock;

    std::vector<std::unique_ptr<VBill>> v10;
    std::vector<SBill> s10;
    std::vector<VarBill> var10;

    for (int i = 0; i < 10; ++i) {
        int kind = i % 4;
        if (kind == 0) {
            v10.push_back(std::make_unique<VOP>(500 + i, 1200));
            s10.push_back({BillTag::OP, 500.0 + i, 1200.0, 0.0, 0});
            var10.emplace_back(VarOP{500.0 + i, 1200.0});
        } else if (kind == 1) {
            v10.push_back(std::make_unique<VIP>(3, 2500, 40000 + i));
            s10.push_back({BillTag::IP, 2500.0, 40000.0 + i, 0.0, 3});
            var10.emplace_back(VarIP{3, 2500.0, 40000.0 + i});
        } else if (kind == 2) {
            v10.push_back(std::make_unique<VDC>(22000 + i));
            s10.push_back({BillTag::DC, 22000.0 + i, 0.0, 0.0, 0});
            var10.emplace_back(VarDC{22000.0 + i});
        } else {
            v10.push_back(std::make_unique<VEM>(3000, 1500, 4 + (i % 3)));
            s10.push_back({BillTag::EM, 3000.0, 1500.0, 0.0, 4 + (i % 3)});
            var10.emplace_back(VarEM{3000.0, 1500.0, 4 + (i % 3)});
        }
    }

    double sumV = 0, sumS = 0, sumVar = 0;
    for (const auto& b : v10) sumV += b->total();
    for (const auto& b : s10) sumS += b.total();
    for (const auto& b : var10) sumVar += visitTotal(b);

    std::cout << "=== B3.1 CORRECTNESS CHECK (10 BILLS) ===\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Virtual Hierarchy Total : " << sumV << "\n";
    std::cout << "Struct + Switch Total   : " << sumS << "\n";
    std::cout << "std::variant Total      : " << sumVar << "\n";
    std::cout << "Match Status            : " << ((std::abs(sumV - sumS) < 1e-6 && std::abs(sumV - sumVar) < 1e-6) ? "EXACT MATCH" : "MISMATCH") << "\n\n";

    std::cout << "=== B3.2 DISPATCH SCALING BENCHMARK ===\n";
    std::cout << "Object Sizes -> sizeof(VIP)=" << sizeof(VIP) << "B (+8B ptr), sizeof(SBill)=" << sizeof(SBill) << "B, sizeof(VarBill)=" << sizeof(VarBill) << "B\n";

    for (std::size_t N : {1000ULL, 1000000ULL, 10000000ULL}) {
        std::vector<std::unique_ptr<VBill>> vb;
        std::vector<SBill> sb;
        std::vector<VarBill> varb;
        vb.reserve(N);
        sb.reserve(N);
        varb.reserve(N);

        for (std::size_t i = 0; i < N; ++i) {
            int kind = i & 3;
            if (kind == 0) {
                vb.push_back(std::make_unique<VOP>(500.0, 1200.0));
                sb.push_back({BillTag::OP, 500.0, 1200.0, 0.0, 0});
                varb.emplace_back(VarOP{500.0, 1200.0});
            } else if (kind == 1) {
                vb.push_back(std::make_unique<VIP>(3, 2500.0, 40000.0));
                sb.push_back({BillTag::IP, 2500.0, 40000.0, 0.0, 3});
                varb.emplace_back(VarIP{3, 2500.0, 40000.0});
            } else if (kind == 2) {
                vb.push_back(std::make_unique<VDC>(22000.0));
                sb.push_back({BillTag::DC, 22000.0, 0.0, 0.0, 0});
                varb.emplace_back(VarDC{22000.0});
            } else {
                vb.push_back(std::make_unique<VEM>(3000.0, 1500.0, 4));
                sb.push_back({BillTag::EM, 3000.0, 1500.0, 0.0, 4});
                varb.emplace_back(VarEM{3000.0, 1500.0, 4});
            }
        }

        volatile double sink = 0.0;

        auto t0 = Clock::now();
        double accV = 0.0;
        for (const auto& p : vb) accV += p->total();
        auto t1 = Clock::now();
        sink = accV;

        auto t2 = Clock::now();
        double accS = 0.0;
        for (const auto& s : sb) accS += s.total();
        auto t3 = Clock::now();
        sink = accS;

        auto t4 = Clock::now();
        double accVar = 0.0;
        for (const auto& v : varb) accVar += visitTotal(v);
        auto t5 = Clock::now();
        sink = accVar;
        (void)sink;

        double msV = std::chrono::duration<double, std::milli>(t1 - t0).count();
        double msS = std::chrono::duration<double, std::milli>(t3 - t2).count();
        double msVar = std::chrono::duration<double, std::milli>(t5 - t4).count();

        std::cout << "N = " << std::setw(8) << N
                  << " | Virtual: " << std::setw(7) << std::setprecision(3) << msV << " ms"
                  << " | Switch: " << std::setw(7) << msS << " ms"
                  << " | Variant: " << std::setw(7) << msVar << " ms\n";
    }

    std::cout << "\n=== B3.3 EXCEPTION vs RETURN CODE COST (N = 1,000,000) ===\n";
    const std::size_t M = 1000000;
    for (int invalidPct : {0, 1, 50}) {
        std::vector<double> inputs(M);
        for (std::size_t i = 0; i < M; ++i) {
            bool isInvalid = (invalidPct == 0) ? false : ((i % 100) < static_cast<std::size_t>(invalidPct));
            inputs[i] = isInvalid ? -100.0 : 1000.0;
        }

        auto r0 = Clock::now();
        double validSumRC = 0.0;
        std::size_t errCountRC = 0;
        for (double x : inputs) {
            double res = 0.0;
            if (validateReturnCode(x, res) == Status::OK) validSumRC += res;
            else ++errCountRC;
        }
        auto r1 = Clock::now();

        auto e0 = Clock::now();
        double validSumEX = 0.0;
        std::size_t errCountEX = 0;
        for (double x : inputs) {
            try {
                validSumEX += validateException(x);
            } catch (const std::invalid_argument&) {
                ++errCountEX;
            }
        }
        auto e1 = Clock::now();

        double msRC = std::chrono::duration<double, std::milli>(r1 - r0).count();
        double msEX = std::chrono::duration<double, std::milli>(e1 - e0).count();
        (void)validSumRC; (void)validSumEX;

        std::cout << "Invalid Rate = " << std::setw(2) << invalidPct << "%"
                  << " | Errors = " << std::setw(6) << errCountRC
                  << " | ReturnCode: " << std::setw(7) << std::setprecision(3) << msRC << " ms"
                  << " | Exception: " << std::setw(8) << msEX << " ms"
                  << " | Ratio (EX/RC): " << std::setprecision(1) << (msEX / (msRC > 1e-6 ? msRC : 1e-6)) << "x\n";
    }
    return 0;
}
