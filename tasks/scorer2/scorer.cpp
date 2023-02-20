#include "scorer.h"

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    std::get<0>(table[student_name][task_name]) = false;
    students.insert(student_name);
    task.insert(task_name);
}
void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    std::get<0>(table[student_name][task_name]) = true;
    students.insert(student_name);
    task.insert(task_name);
}
void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    std::get<1>(table[student_name][task_name]) = true;
    students.insert(student_name);
    task.insert(task_name);
}
void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    std::get<1>(table[student_name][task_name]) = false;
    students.insert(student_name);
    task.insert(task_name);
}
void Scorer::Reset() {
    table.clear();
    students.clear();
    task.clear();
}
ScoreTable Scorer::GetScoreTable() const {
    ScoreTable ans;
    for (auto& [stu, val]:table) {
        for (auto& [task_name, pair_bool]:val) {
            if (pair_bool.first and !pair_bool.second){
                ans[stu].insert(task_name);
            }
        }
    }
    return ans;
}
