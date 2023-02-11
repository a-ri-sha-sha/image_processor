#include "admission.h"
#include <tuple>
#include <map>
bool Comp(const Applicant* lhv, const Applicant* rhv) {
    return std::tie(rhv->points, lhv->student.birth_date.year, lhv->student.birth_date.month,
                    lhv->student.birth_date.day, lhv->student.name) <
           std::tie(lhv->points, rhv->student.birth_date.year, rhv->student.birth_date.month,
                    rhv->student.birth_date.day, rhv->student.name);
}
AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<const Applicant*> applicant;
    AdmissionTable table;
    for (const Applicant& app : applicants) {
        applicant.push_back(&app);
    }
    std::sort(applicant.begin(), applicant.end(), Comp);
    std::map<std::string, size_t> university;
    for (const University& uni : universities) {
        university[uni.name] = uni.max_students;
    }
    for (const Applicant* stu : applicant) {
        for (const std::string& wish : stu->wish_list) {
            if (university[wish] != 0) {
                table[wish].push_back(&stu->student);
                university[wish] -= 1;
                break;
            }
        }
    }
    return table;
}
