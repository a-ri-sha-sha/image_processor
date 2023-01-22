#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    std::string str_new;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != ' ') {
            str_new += str[i];
        }
    }
    unsigned int n = str_new.size();
    for (int i = 0; i < n / 2; ++i) {
        if (str_new[i] != str_new[n - 1 - i]) {
            return false;
        }
    }
    return true;
}
