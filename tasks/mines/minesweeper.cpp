#include "minesweeper.h"

#include <algorithm>
#include <ctime>
#include <queue>
#include <random>
#include <string>
#include <vector>

Minesweeper::VectorNeighbour Minesweeper::MakeVectorNeig(size_t x, size_t y) {
    VectorNeighbour ans;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (y + i >= 0 && y + i < closed_cell_.size() && x + j >= 0 && x + j < closed_cell_[0].size()) {
                ans.push_back(Cell{x + j, y + i});
            }
        }
    }
    return ans;
}

void Minesweeper::NearbyMine(size_t x, size_t y) {
    for (Cell cell : MakeVectorNeig(x, y)) {
        if (closed_cell_[cell.y][cell.x] != ClosedCellType::Mine) {
            closed_cell_[cell.y][cell.x] = ClosedCellType::Neighbour;
            neighbour_[cell.y][cell.x] += 1;
        }
    }
}

void Minesweeper::OpenCell(const Minesweeper::Cell& cell) {
    if (game_status_ == GameStatus::VICTORY || game_status_ == GameStatus::DEFEAT ||
        open_cell_[cell.y][cell.x] == OpenCellType::Flag) {
        return;
    }
    if (closed_cell_[cell.y][cell.x] == ClosedCellType::Mine) {
        game_status_ = GameStatus::DEFEAT;
        for (size_t y = 0; y < closed_cell_.size(); ++y) {
            for (size_t x = 0; x < closed_cell_[0].size(); ++x) {
                switch (closed_cell_[y][x]) {
                    case ClosedCellType::Mine:
                        open_cell_[y][x] = OpenCellType::Mine;
                        game_status_ = GameStatus::DEFEAT;
                        break;
                    case ClosedCellType::Empty:
                        open_cell_[y][x] = OpenCellType::Neighbour;
                        break;
                    case ClosedCellType::Neighbour:
                        open_cell_[y][x] = OpenCellType::Neighbour;
                        break;
                }
            }
        }
    } else if (closed_cell_[cell.y][cell.x] == ClosedCellType::Neighbour) {
        open_cell_[cell.y][cell.x] = OpenCellType::Neighbour;
        count_of_open_ += 1;
    } else {
        std::queue<Cell> need_to_open;
        open_cell_[cell.y][cell.x] = OpenCellType::Neighbour;
        count_of_open_ += 1;
        VectorNeighbour neig = MakeVectorNeig(cell.x, cell.y);
        for (Cell cell1 : neig) {
            need_to_open.push(Cell{cell1.x, cell1.y});
        }
        while (!need_to_open.empty()) {
            size_t x = need_to_open.front().x;
            size_t y = need_to_open.front().y;
            if (open_cell_[y][x] == OpenCellType::Closed) {
                if (closed_cell_[y][x] == ClosedCellType::Neighbour) {
                    open_cell_[y][x] = OpenCellType::Neighbour;
                    count_of_open_ += 1;
                } else {
                    neig = MakeVectorNeig(x, y);
                    for (Cell cell1 : neig) {
                        need_to_open.push(Cell{cell1.x, cell1.y});
                    }
                    open_cell_[y][x] = OpenCellType::Neighbour;
                    count_of_open_ += 1;
                }
            }
            need_to_open.pop();
        }
    }
    if (count_of_open_ == open_cell_.size() * open_cell_[0].size() - count_of_mines_ &&
        game_status_ != GameStatus::DEFEAT) {
        game_status_ = GameStatus::VICTORY;
    }
}

Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) {
    NewGame(width, height, mines_count);
}

Minesweeper::Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    NewGame(width, height, cells_with_mines);
}

void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    closed_cell_.clear();
    open_cell_.clear();
    neighbour_.clear();
    count_of_open_ = 0;
    count_of_mines_ = static_cast<int>(mines_count);
    std::vector<std::pair<size_t, size_t>> random_cells;
    for (size_t i = 0; i < height; ++i) {
        closed_cell_.push_back(std::vector<ClosedCellType>());
        open_cell_.push_back(std::vector<OpenCellType>());
        neighbour_.push_back(std::vector<int>());
        for (size_t j = 0; j < width; ++j) {
            closed_cell_[i].push_back(ClosedCellType::Empty);
            open_cell_[i].push_back(OpenCellType::Closed);
            neighbour_[i].push_back(0);
            random_cells.push_back(std::make_pair(i, j));
        }
    }
    shuffle(random_cells.begin(), random_cells.end(), std::mt19937(std::random_device()()));
    for (size_t i = 0; i < mines_count; ++i) {
        size_t y = random_cells[i].first;
        size_t x = random_cells[i].second;
        closed_cell_[y][x] = ClosedCellType::Mine;
        NearbyMine(x, y);
    }
    start_time_ = std::time(nullptr);
    game_status_ = GameStatus::IN_PROGRESS;
}

void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    closed_cell_.clear();
    open_cell_.clear();
    neighbour_.clear();
    count_of_mines_ = static_cast<int>(cells_with_mines.size());
    count_of_open_ = 0;
    for (size_t i = 0; i < height; ++i) {
        closed_cell_.push_back(std::vector<ClosedCellType>());
        open_cell_.push_back(std::vector<OpenCellType>());
        neighbour_.push_back(std::vector<int>());
        for (size_t j = 0; j < width; ++j) {
            closed_cell_[i].push_back(ClosedCellType::Empty);
            open_cell_[i].push_back(OpenCellType::Closed);
            neighbour_[i].push_back(0);
        }
    }
    for (size_t i = 0; i < cells_with_mines.size(); ++i) {
        size_t x = cells_with_mines[i].x;
        size_t y = cells_with_mines[i].y;
        closed_cell_[y][x] = ClosedCellType::Mine;
        NearbyMine(x, y);
    }
    start_time_ = std::time(nullptr);
    game_status_ = GameStatus::IN_PROGRESS;
}

void Minesweeper::MarkCell(const Minesweeper::Cell& cell) {
    if (game_status_ == GameStatus::VICTORY || game_status_ == GameStatus::DEFEAT) {
        return;
    }
    if (open_cell_[cell.y][cell.x] == OpenCellType::Flag) {
        open_cell_[cell.y][cell.x] = OpenCellType::Closed;
    } else {
        open_cell_[cell.y][cell.x] = OpenCellType::Flag;
    }
}

Minesweeper::GameStatus Minesweeper::GetGameStatus() const {
    return game_status_;
}

time_t Minesweeper::GetGameTime() const {
    time_t time_now = std::time(nullptr);
    return start_time_ - time_now;
}

Minesweeper::RenderedField Minesweeper::RenderField() const {
    Minesweeper::RenderedField field;
    for (size_t y = 0; y < open_cell_.size(); ++y) {
        field.push_back(std::string());
        for (size_t x = 0; x < open_cell_[0].size(); ++x) {
            if (open_cell_[y][x] == OpenCellType::Closed) {
                field[y] += "-";
            } else if (open_cell_[y][x] == OpenCellType::Mine) {
                field[y] += "*";
            } else if (open_cell_[y][x] == OpenCellType::Flag) {
                field[y] += "?";
            } else if (neighbour_[y][x] == 0) {
                field[y] += ".";
            } else {
                field[y] += std::to_string(neighbour_[y][x]);
            }
        }
    }
    return field;
}
