#include "scorer.h"

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    std::get<0>(table_[student_name][task_name]) = false;
    students_.insert(student_name);
    task_.insert(task_name);
}
void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    std::get<0>(table_[student_name][task_name]) = true;
    students_.insert(student_name);
    task_.insert(task_name);
}
void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    std::get<1>(table_[student_name][task_name]) = true;
    students_.insert(student_name);
    task_.insert(task_name);
}
void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    std::get<1>(table_[student_name][task_name]) = false;
    students_.insert(student_name);
    task_.insert(task_name);
}
void Scorer::Reset() {
    table_.clear();
    students_.clear();
    task_.clear();
}
ScoreTable Scorer::GetScoreTable() const {
    ScoreTable ans;
    for (auto& [stu, val] : table_) {
        for (auto& [task_name, pair_bool] : val) {
            if (pair_bool.first and !pair_bool.second) {
                ans[stu].insert(task_name);
            }
        }
    }
    return ans;
}
