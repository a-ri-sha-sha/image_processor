#include "poly.h"

Poly::Poly(std::initializer_list<int64_t> list) {
    size_t i = 0;
    for (int64_t elem : list) {
        if (elem != 0) {
            coef_[i] = elem;
        }
        ++i;
    }
}

Poly::Poly(std::initializer_list<std::pair<int64_t, int64_t>> list) {
    for (std::pair pair : list) {
        coef_[pair.first] = pair.second;
    }
}

int64_t Poly::operator()(int64_t val) const {
    int64_t ans = 0;
    size_t degree = 0;
    int64_t pow_x = 1;
    for (auto pair : coef_) {
        for (size_t i = degree; i < pair.first; ++i) {
            pow_x *= val;
        }
        degree = pair.first;
        ans += pair.second * pow_x;
    }
    return ans;
}

bool Poly::operator==(Poly poly) const {
    if (coef_.size() != poly.coef_.size()) {
        return false;
    }
    for (auto pair : coef_) {
        if (poly.coef_.find(pair.first) == poly.coef_.end() && poly.coef_.at(pair.first) != pair.second) {
            return false;
        }
    }
    return true;
}

Poly Poly::operator-(Poly poly) const {
    Poly ans;
    ans.coef_ = coef_;
    for (auto pair : poly.coef_) {
        ans.coef_[pair.first] -= pair.second;
        if (ans.coef_[pair.first] == 0) {
            ans.coef_.erase(ans.coef_.find(pair.first));
        }
    }
    return ans;
}

Poly Poly::operator+(Poly poly) const {
    Poly ans;
    ans.coef_ = coef_;
    for (auto pair : poly.coef_) {
        ans.coef_[pair.first] += pair.second;
    }
    return ans;
}

void Poly::operator+=(Poly poly) {
    for (auto pair : poly.coef_) {
        coef_[pair.first] += pair.second;
    }
}

void Poly::operator-=(Poly poly) {
    for (auto pair : poly.coef_) {
        coef_[pair.first] -= pair.second;
    }
}

void Poly::operator*=(Poly poly) {
    Poly ans;
    for (auto pair_poly : poly.coef_) {
        for (auto pair : coef_) {
            ans.coef_[pair_poly.first + pair.first] += pair.second * pair_poly.second;
        }
    }
    coef_ = ans.coef_;
}

Poly Poly::operator-() const {
    Poly ans;
    for (auto pair : coef_) {
        ans.coef_[pair.first] = -pair.second;
    }
    return ans;
}

Poly Poly::operator*(Poly poly) const {
    Poly ans;
    for (auto pair_poly : poly.coef_) {
        for (auto pair : coef_) {
            ans.coef_[pair_poly.first + pair.first] += pair.second * pair_poly.second;
        }
    }
    return ans;
}

std::ostream& operator<<(std::ostream& out, const Poly& poly) {
    std::string ans = "y = ";
    if (poly.coef_.empty()) {
        return out << ans + "0";
    }
    bool f = false;
    for (auto it = poly.coef_.rbegin(); it != poly.coef_.rend(); ++it) {
        size_t i = it->first;
        if (i == 0) {
            if (poly.coef_.at(i) > 0 && f) {
                ans += " + " + std::to_string(poly.coef_.at(i));
            } else if (poly.coef_.at(i) > 0) {
                ans += std::to_string(poly.coef_.at(i));
            } else if (poly.coef_.at(i) < 0 && f) {
                ans += " - " + std::to_string(-poly.coef_.at(i));
            } else if (poly.coef_.at(i) < 0) {
                ans += std::to_string(poly.coef_.at(i));
            }
        } else if (i == 1) {
            if (poly.coef_.at(i) > 0 && f) {
                ans += " + " + std::to_string(poly.coef_.at(i)) + "x";
            } else if (poly.coef_.at(i) > 0) {
                ans += std::to_string(poly.coef_.at(i)) + "x";
                f = true;
            } else if (poly.coef_.at(i) < 0 && f) {
                ans += " - " + std::to_string(-poly.coef_.at(i)) + "x";
            } else if (poly.coef_.at(i) < 0) {
                ans += std::to_string(poly.coef_.at(i)) + "x";
                f = true;
            }
        } else {
            if (poly.coef_.at(i) > 0 && f) {
                ans += " + " + std::to_string(poly.coef_.at(i)) + "x^" + std::to_string(i);
            } else if (poly.coef_.at(i) > 0) {
                ans += std::to_string(poly.coef_.at(i)) + "x^" + std::to_string(i);
                f = true;
            } else if (poly.coef_.at(i) < 0 && f) {
                ans += " - " + std::to_string(-poly.coef_.at(i)) + "x^" + std::to_string(i);
            } else if (poly.coef_.at(i) < 0) {
                ans += std::to_string(poly.coef_.at(i)) + "x^" + std::to_string(i);
                f = true;
            }
        }
    }
    return out << ans;
}
