#include <deque>
#include "tests_checking.h"

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> deq;
    for (auto& action : student_actions) {
        if (action.side == Side::Top) {
            deq.push_front(action.name);
        } else {
            deq.push_back(action.name);
        }
    }
    std::vector<std::string> ans;
    for (size_t i : queries) {
        ans.push_back(deq.at(i - 1));
    }
    return ans;
}