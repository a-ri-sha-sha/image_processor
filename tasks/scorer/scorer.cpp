#include "scorer.h"
#include <tuple>

bool Comp(const Event* lhv, const Event* rhv) {
    return lhv->time < rhv->time;
}

using Table = std::map<StudentName, std::map<TaskName, std::pair<bool, bool>>>;

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    ScoreTable ans;
    std::vector<const Event*> event;
    Table table;
    std::set<StudentName> students;
    std::set<TaskName> task;
    for (const Event& ev : events) {
        if (ev.time <= score_time) {
            event.push_back(&ev);
            students.insert(ev.student_name);
            task.insert(ev.task_name);
        }
    }
    std::sort(event.begin(), event.end(), Comp);
    for (const Event* ev : event) {
        if (ev->event_type == EventType::CheckSuccess) {
            std::get<0>(table[ev->student_name][ev->task_name]) = true;
        }
        if (ev->event_type == EventType::CheckFailed) {
            std::get<0>(table[ev->student_name][ev->task_name]) = false;
        }
        if (ev->event_type == EventType::MergeRequestOpen) {
            std::get<1>(table[ev->student_name][ev->task_name]) = true;
        }
        if (ev->event_type == EventType::MergeRequestClosed) {
            std::get<1>(table[ev->student_name][ev->task_name]) = false;
        }
    }
    for (const StudentName& stu : students) {
        for (const TaskName& task_name : task) {
            if (std::get<0>(table[stu][task_name]) and !(std::get<1>(table[stu][task_name]))) {
                ans[stu].insert(task_name);
            }
        }
    }

    return ans;
}
