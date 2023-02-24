#pragma once

#include <deque>
#include <string>
#include <string_view>

class UnixPath {
public:
    explicit UnixPath(std::string_view initial_dir);

    void ChangeDirectory(std::string_view path);
    void PathDeqAns(std::string_view path);
    std::string GetAbsolutePath() const;
    std::string GetRelativePath() const;

private:
    std::deque<std::string> path_deq_;
    std::deque<std::string> dir_deq_;
};
