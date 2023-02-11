#include <deque>
#include "unixpath.h"

std::deque<std::string> Split(const std::string_view& dir) {
    std::deque<std::string> dir_deq;
    std::string add;
    for (size_t i = 0; i < dir.size(); ++i) {
        char elem = dir[i];
        if (elem == '/' and !add.empty()) {
            dir_deq.push_back(add);
            add.clear();
        } else if (elem != '/') {
            add += elem;
        }
        if (i == dir.size() - 1 && elem != '/') {
            dir_deq.push_back(add);
        }
    }
    return dir_deq;
}

std::deque<std::string> PathDeqAns(std::deque<std::string> dir_deq, const std::string_view& path) {
    if (path[0] == '/') {
        dir_deq.clear();
    }
    std::string add;
    for (size_t i = 0; i < path.size(); ++i) {
        if (path[i] == '/' && !add.empty()) {
            if (add == ".") {
                add.clear();
            } else if (add == "..") {
                if (!dir_deq.empty()) {
                    dir_deq.pop_back();
                }
                add.clear();

            } else {
                dir_deq.push_back(add);
                add.clear();
            }
        } else if (path[i] != '/') {
            add += path[i];
        }
        if (i == path.size() - 1 && !add.empty()) {
            if (add == ".") {
                continue;
            } else if (add == "..") {
                if (!dir_deq.empty()) {
                    dir_deq.pop_back();
                }
            } else {
                dir_deq.push_back(add);
            }
        }
    }
    return dir_deq;
}

std::string DeqToStr(const std::deque<std::string>& path_deq) {
    std::string path = "/";
    for (size_t i = 0; i < path_deq.size(); ++i) {
        std::string elem = path_deq[i];
        path += elem;
        if (i != path_deq.size() - 1) {
            path += "/";
        }
    }
    return path;
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string ans;
    std::deque<std::string> dir_deq = Split(current_working_dir);
    std::deque<std::string> path_deq = PathDeqAns(dir_deq, path);
    ans = DeqToStr(path_deq);
    return ans;
}
