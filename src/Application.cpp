#include "Application.hpp"
#include "Board.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

void Application::Run()
{
    Board board(100);
    bool redTurn = true;

    auto size = board.GetSize();
    sf::RenderWindow window(sf::VideoMode(size.x, size.y), "Connect4", sf::Style::Close);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                const int column = event.mouseButton.x / board.GetCellSide();

                if (board.PlaceInColumn(column, redTurn ? Board::CellType::Red : Board::CellType::Blue))
                {
                    if (board.IsGameOver())
                    {
                        // Show game over menu
                        window.close();
                    }
                    else
                    {
                        // Display retry menu
                        WinStatus status = board.WinCheck();
                        redTurn = !redTurn;
                    }
                }
            }
        }

        if (window.hasFocus())
        {
            window.clear();
            window.draw(board);
            window.display();
        }
    }
}
