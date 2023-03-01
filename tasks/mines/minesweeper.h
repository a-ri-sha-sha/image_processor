#pragma once

#include <string>
#include <vector>

class Minesweeper {
public:
    struct Cell {
        size_t x = 0;
        size_t y = 0;
    };

    enum class GameStatus {
        NOT_STARTED,
        IN_PROGRESS,
        VICTORY,
        DEFEAT,
    };

    enum class ClosedCellType {
        Mine,
        Neighbour,
        Empty,
    };

    enum class OpenCellType {
        Mine,
        Flag,
        Neighbour,
        Closed,
    };

    using RenderedField = std::vector<std::string>;
    using VectorNeighbour = std::vector<Cell>;

    Minesweeper(size_t width, size_t height, size_t mines_count);
    Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void NearbyMine(size_t x, size_t y);

    void StartNewGame(size_t width, size_t height);
    void NewGame(size_t width, size_t height, size_t mines_count);
    void NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void OpenCell(const Cell& cell);
    void MarkCell(const Cell& cell);

    VectorNeighbour MakeVectorNeig(size_t x, size_t y);
    GameStatus GetGameStatus() const;
    time_t GetGameTime() const;

    RenderedField RenderField() const;

private:
    std::vector<std::vector<ClosedCellType>> closed_cell_;
    std::vector<std::vector<OpenCellType>> open_cell_;
    std::vector<std::vector<int>> neighbour_;
    time_t start_time_;
    GameStatus game_status_ = GameStatus::NOT_STARTED;
    int count_of_mines_;
    int count_of_open_;
};
