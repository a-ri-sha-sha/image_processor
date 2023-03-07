#pragma once

#include <vector>
#include <iostream>
#include <tuple>
#include <map>

class Poly {
public:
    Poly(){};
    Poly(std::initializer_list<int64_t> list);
    Poly(std::initializer_list<std::pair<int64_t, int64_t>> list);

    int64_t operator()(int64_t val) const;
    bool operator==(Poly poly) const;
    Poly operator-(Poly poly) const;
    Poly operator+(Poly poly) const;
    void operator+=(Poly poly);
    void operator-=(Poly poly);
    void operator*=(Poly poly);
    Poly operator*(Poly poly) const;
    Poly operator-() const;

    friend std::ostream& operator<<(std::ostream& out, const Poly& poly);

private:
    std::map<size_t, int64_t> coef_;
};
