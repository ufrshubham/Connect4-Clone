#include "Board.hpp"
#include <cassert>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#ifdef DEBUG
#include <iostream>
#endif

Board::Board(int cellSize) : CELL_SIDE(cellSize)
{
    m_state.fill(Board::CellType::Empty);
}

bool Board::PlaceInColumn(std::size_t col, const CellType &cellType)
{
    bool placed = false;

    for (int row = NUMBER_OF_ROWS - 1; row >= 0; --row)
    {
        if (GetCellType(row, col) == CellType::Empty)
        {
            placed = SetCellType(row, col, cellType);
            break;
        }
    }

    return placed;
}

WinStatus Board::WinCheck() const
{
    WinStatus winStatus = WinStatus::NoWin;

    for (std::size_t row = 0; row < NUMBER_OF_ROWS; ++row)
    {
        for (std::size_t col = 0; col < NUMBER_OF_COLUMNS; ++col)
        {
            auto currentCellType = GetCellType(row, col);
            if (currentCellType != CellType::Empty)
            {
                // Horizontal check.
                if (col <= (NUMBER_OF_COLUMNS - 4))
                {
                    auto sum = std::abs(currentCellType + GetCellType(row, col + 1) + GetCellType(row, col + 2) + GetCellType(row, col + 3));
                    if (sum == 4)
                    {
                        winStatus = currentCellType == CellType::Red ? WinStatus::RedWin : WinStatus::BlueWin;

                        m_winLine[0] = sf::Vertex({col * (float)CELL_SIDE + (CELL_SIDE / 2.f), row * (float)CELL_SIDE + (CELL_SIDE / 2.f)}, sf::Color::Yellow);
                        m_winLine[1] = sf::Vertex({(col + 3) * (float)CELL_SIDE + (CELL_SIDE / 2.f), row * (float)CELL_SIDE + (CELL_SIDE / 2.f)}, sf::Color::Yellow);
                        m_shouldDrawWinLine = true;
                        break;
                    }
                }

                // Vertical check.
                if (row <= (NUMBER_OF_ROWS - 4))
                {
                    auto sum = std::abs(currentCellType + GetCellType(row + 1, col) + GetCellType(row + 2, col) + GetCellType(row + 3, col));
                    if (sum == 4)
                    {
                        winStatus = currentCellType == CellType::Red ? WinStatus::RedWin : WinStatus::BlueWin;

                        m_winLine[0] = sf::Vertex({col * (float)CELL_SIDE + (CELL_SIDE / 2.f), row * (float)CELL_SIDE + (CELL_SIDE / 2.f)}, sf::Color::Yellow);
                        m_winLine[1] = sf::Vertex({col * (float)CELL_SIDE + (CELL_SIDE / 2.f), (row + 3) * (float)CELL_SIDE + (CELL_SIDE / 2.f)}, sf::Color::Yellow);
                        m_shouldDrawWinLine = true;
                        break;
                    }
                }

                // Diagonal (-45) check.
                if ((col <= (NUMBER_OF_COLUMNS - 4)) && (row <= (NUMBER_OF_ROWS - 4)))
                {
                    auto sum = std::abs(currentCellType + GetCellType(row + 1, col + 1) + GetCellType(row + 2, col + 2) + GetCellType(row + 3, col + 3));
                    if (sum == 4)
                    {
                        winStatus = currentCellType == CellType::Red ? WinStatus::RedWin : WinStatus::BlueWin;

                        m_winLine[0] = sf::Vertex({col * (float)CELL_SIDE + (CELL_SIDE / 2.f), row * (float)CELL_SIDE + (CELL_SIDE / 2.f)}, sf::Color::Yellow);
                        m_winLine[1] = sf::Vertex({(col + 3) * (float)CELL_SIDE + (CELL_SIDE / 2.f), (row + 3) * (float)CELL_SIDE + (CELL_SIDE / 2.f)}, sf::Color::Yellow);
                        m_shouldDrawWinLine = true;
                        break;
                    }
                }

                // Diagonal (45) check.
                if (((col <= (NUMBER_OF_COLUMNS - 4)) && (row >= 3)))
                {
                    auto sum = std::abs(currentCellType + GetCellType(row - 1, col + 1) + GetCellType(row - 2, col + 2) + GetCellType(row - 3, col + 3));
                    if (sum == 4)
                    {
                        winStatus = currentCellType == CellType::Red ? WinStatus::RedWin : WinStatus::BlueWin;

                        m_winLine[0] = sf::Vertex({col * (float)CELL_SIDE + (CELL_SIDE / 2.f), row * (float)CELL_SIDE + (CELL_SIDE / 2.f)}, sf::Color::Yellow);
                        m_winLine[1] = sf::Vertex({(col + 3) * (float)CELL_SIDE + (CELL_SIDE / 2.f), (row - 3) * (float)CELL_SIDE + (CELL_SIDE / 2.f)}, sf::Color::Yellow);
                        m_shouldDrawWinLine = true;
                        break;
                    }
                }
            }
        }
        if (winStatus != WinStatus::NoWin)
        {
            break;
        }
    }

    return winStatus;
}

bool Board::IsGameOver() const
{
    return std::all_of(m_state.begin(), m_state.end(), [](const auto &cellType)
                       { return cellType; });
}

sf::Vector2i Board::GetSize() const
{
    return {Board::CELL_SIDE * Board::NUMBER_OF_COLUMNS, Board::CELL_SIDE * Board::NUMBER_OF_ROWS};
}

int Board::GetCellSide() const
{
    return CELL_SIDE;
}

#ifdef DEBUG
void Board::Print() const
{
    for (std::size_t row = 0; row < NUMBER_OF_ROWS; ++row)
    {
        for (std::size_t col = 0; col < NUMBER_OF_COLUMNS; ++col)
        {
            std::cout << GetCellType(row, col) << " ";
        }
        std::cout << std::endl;
    }
}
#endif

Board::CellType Board::GetCellType(std::size_t row, std::size_t col) const
{
    bool isInputValid = (row >= 0 && row < NUMBER_OF_ROWS && col >= 0 && col < NUMBER_OF_COLUMNS);
    assert(isInputValid);

    CellType cellType = CellType::Empty;
    if (isInputValid)
    {
        cellType = m_state[row * NUMBER_OF_COLUMNS + col];
    }

    return cellType;
}

bool Board::SetCellType(std::size_t row, std::size_t col, const CellType &cellType)
{
    bool isInputValid = (row >= 0 && row < NUMBER_OF_ROWS && col >= 0 && col < NUMBER_OF_COLUMNS);
    assert(isInputValid);

    bool placed = false;

    if (isInputValid && (GetCellType(row, col) == CellType::Empty))
    {
        m_state[row * NUMBER_OF_COLUMNS + col] = cellType;
        placed = true;
    }

    return placed;
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

    for (std::size_t row = 0; row < NUMBER_OF_ROWS; ++row)
    {
        for (std::size_t col = 0; col < NUMBER_OF_COLUMNS; ++col)
        {
            sf::RectangleShape rect({(float)CELL_SIDE, (float)CELL_SIDE});
            rect.setPosition({(float)col * CELL_SIDE, (float)row * CELL_SIDE});
            rect.setFillColor(sf::Color::Black);
            rect.setOutlineThickness(2);
            rect.setOutlineColor(sf::Color::White);

            target.draw(rect);

            switch (GetCellType(row, col))
            {
            case CellType::Empty:
            {
                break;
            }
            case CellType::Red:
            {
                sf::CircleShape circle(40);
                circle.setFillColor(sf::Color::Red);
                circle.setOutlineThickness(2);
                circle.setOutlineColor(sf::Color::White);
                auto localBoundingBox = circle.getLocalBounds();
                circle.setOrigin(localBoundingBox.width / 2, localBoundingBox.height / 2);
                circle.setPosition(sf::Vector2f{(float)col * CELL_SIDE, (float)row * CELL_SIDE} + sf::Vector2f{CELL_SIDE / 2.f, CELL_SIDE / 2.f});
                target.draw(circle);
                break;
            }
            case CellType::Blue:
            {
                sf::CircleShape circle(40);
                circle.setFillColor(sf::Color::Blue);
                circle.setOutlineThickness(2);
                circle.setOutlineColor(sf::Color::White);
                auto localBoundingBox = circle.getLocalBounds();
                circle.setOrigin(localBoundingBox.width / 2, localBoundingBox.height / 2);
                circle.setPosition(sf::Vector2f{(float)col * CELL_SIDE, (float)row * CELL_SIDE} + sf::Vector2f{CELL_SIDE / 2.f, CELL_SIDE / 2.f});
                target.draw(circle);
                break;
            }
            }
        }
    }

    if (m_shouldDrawWinLine)
    {
        target.draw(m_winLine.data(), 2, sf::Lines);
    }
}
