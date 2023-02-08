#include "word2vec.h"

#include <vector>

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<std::string> ans;
    int64_t max_len = 0;
    int64_t len = 0;
    for (size_t i = 1; i < vectors.size(); ++i) {
        for (int coord : vectors[i]) {
            len += static_cast<int64_t>(coord) * static_cast<int64_t>(vectors[0][i]);
        }
        if (len == max_len) {
            ans.push_back(words[i]);
        }
        if (len > max_len) {
            max_len = len;
            ans.clear();
            ans.push_back(words[i]);
        }
        len = 0;
    }

    return ans;
}
