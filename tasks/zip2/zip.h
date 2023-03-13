#pragma once

#include <iterator>

template <typename It_seq1, typename It_seq2>
class Zipped {
public:
    class Iter {
    public:
        Iter(It_seq1 it1, It_seq2 it2) {
            it1_ = it1;
            it2_ = it2;
        }
        Iter(const Iter& i) {
            it1_ = i.it1_;
            it2_ = i.it2_;
        }

    public:
        auto operator*() {
            return std::make_pair(*it1_, *it2_);
        }
        Iter& operator++(int) {
            ++it1_;
            ++it2_;
            return *this;
        }
        Iter operator++() {
            Iter old = *this;
            ++it1_;
            ++it2_;
            return old;
        };
        bool operator!=(const Iter& i) {
            return (it1_ != i.it1_ || it2_ != i.it2_);
        }

    private:
        It_seq1 it1_;
        It_seq2 it2_;
    };

public:
    Zipped(const It_seq1& begin1, const It_seq1& end1, const It_seq2& begin2, const It_seq2& end2) {
        begin1_ = begin1;
        end1_ = end1;
        begin2_ = begin2;
        end2_ = end2;
    }

public:
    auto begin() {
        return Iter(begin1_, begin2_);
    }
    auto end() {
        return Iter(end1_, end2_);
    };

private:
    It_seq1 begin1_;
    It_seq1 end1_;
    It_seq2 begin2_;
    It_seq2 end2_;
};

template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {
    auto it1 = std::begin(sequence1);
    auto it2 = std::begin(sequence2);
    for (auto it = std::begin(sequence1); it != std::end(sequence1); ++it) {
        if (it2 != std::end(sequence2)) {
            ++it2;
        } else {
            break;
        }
        ++it1;
    }
    return Zipped(std::begin(sequence1), it1, std::begin(sequence2), it2);
}