#include "unixpath.h"

void Split(const std::string_view& dir, std::deque<std::string>& dir_deq) {
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

UnixPath::UnixPath(std::string_view initial_dir) {
    Split(initial_dir, dir_deq_);
    path_deq_ = dir_deq_;
}

void UnixPath::PathDeqAns(std::string_view path) {
    if (path[0] == '/') {
        path_deq_.clear();
        Split(path, path_deq_);
    } else {
        std::string add;
        for (size_t i = 0; i < path.size(); ++i) {
            if (path[i] == '/' && !add.empty()) {
                if (add == ".") {
                    add.clear();
                } else if (add == "..") {
                    if (!path_deq_.empty()) {
                        path_deq_.pop_back();
                    }
                    add.clear();
                } else {
                    path_deq_.push_back(add);
                    add.clear();
                }
            } else if (path[i] != '/') {
                add += path[i];
            }
            if (i == path.size() - 1 && !add.empty()) {
                if (add == ".") {
                    continue;
                } else if (add == "..") {
                    if (!path_deq_.empty()) {
                        path_deq_.pop_back();
                    }
                } else {
                    path_deq_.push_back(add);
                }
            }
        }
    }
}

void UnixPath::ChangeDirectory(std::string_view path) {
    PathDeqAns(path);
}
std::string UnixPath::GetAbsolutePath() const {
    return (DeqToStr(path_deq_));
}
std::string UnixPath::GetRelativePath() const {
    std::string ans;
    for (size_t i = 0; i < dir_deq_.size(); ++i) {
        if (i < path_deq_.size()) {
            if (dir_deq_[i] == path_deq_[i]) {
                if (i == dir_deq_.size() - 1 && dir_deq_.size() < path_deq_.size()) {
                    ans = ".";
                    std::deque<std::string> copy_deq = path_deq_;
                    copy_deq.assign(path_deq_.begin() + static_cast<int>(i) + 1, path_deq_.end());
                    const std::deque<std::string>& new_deq = copy_deq;
                    ans += DeqToStr(new_deq);
                } else if (i == dir_deq_.size() - 1 && dir_deq_.size() == path_deq_.size()) {
                    ans = ".";
                }
            } else {
                for (int j = 0; j < dir_deq_.size() - i - 1; ++j) {
                    ans += "../";
                }
                ans += "..";
                std::deque<std::string> copy_deq = path_deq_;
                copy_deq.assign(path_deq_.begin() + static_cast<int>(i), path_deq_.end());
                const std::deque<std::string>& new_deq = copy_deq;
                ans += DeqToStr(new_deq);
                break;
            }
        } else {
            for (int j = 0; j < dir_deq_.size() - i; ++j) {
                ans += "../";
            }
            ans += "..";
            break;
        }
    }
    return ans;
}
