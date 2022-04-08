#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <array>

enum class WinStatus
{
    NoWin,
    RedWin,
    BlueWin
};

class Board : public sf::Drawable
{
public:
    Board(int cellSize);
    ~Board() = default;

    enum CellType
    {
        Red = -1,
        Empty = 0,
        Blue = 1
    };

    bool PlaceInColumn(std::size_t col, const CellType &cellType);
    WinStatus WinCheck() const;
    bool IsGameOver() const;

    sf::Vector2i GetSize() const;
    int GetCellSide() const;

#ifdef DEBUG
    void Print() const;
#endif

private:
    Board::CellType GetCellType(std::size_t row, std::size_t col) const;
    bool SetCellType(std::size_t row, std::size_t col, const CellType &cellType);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override final;

private:
    const int CELL_SIDE;
    static const int NUMBER_OF_ROWS = 6;
    static const int NUMBER_OF_COLUMNS = 7;
    mutable std::array<sf::Vertex, 2> m_winLine;
    mutable bool m_shouldDrawWinLine = false;

    std::array<Board::CellType, NUMBER_OF_ROWS * NUMBER_OF_COLUMNS> m_state;
};
