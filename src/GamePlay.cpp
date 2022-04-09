#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"
#include "Board.hpp"

#include <SFML/Window/Event.hpp>

GamePlay::GamePlay(std::shared_ptr<Context> &context)
    : m_context(context),
      m_board(std::make_unique<Board>(100)),
      m_redTurn(true),
      m_isPaused(false),
      m_timeElapsed(),
      m_screenSwitchDelay(2),
      m_winStatus(WinStatus::NoWin),
      m_startDelayTimer(false)
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
}

void GamePlay::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
        {
            m_context->m_window->close();
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if ((!m_isPaused) && (!m_startDelayTimer))
            {
                const int column = event.mouseButton.x / m_board->GetCellSide();

                if (m_board->PlaceInColumn(column, m_redTurn ? Board::CellType::Red : Board::CellType::Blue))
                {
                    if (m_board->IsGameOver())
                    {
                        m_winStatus = WinStatus::NoWin;
                        m_startDelayTimer = true;
                        break;
                    }
                    else
                    {
                        m_winStatus = m_board->WinCheck();
                        if (m_winStatus != WinStatus::NoWin)
                        {
                            m_startDelayTimer = true;
                            break;
                        }

                        m_redTurn = !m_redTurn;
                    }
                }
            }
            break;
        }
        case sf::Event::KeyPressed:
        {
            if (event.key.code == sf::Keyboard::Key::Escape)
            {
                m_context->m_states->Add(std::make_unique<PauseGame>(m_context));
            }
            break;
        }
        }
    }
}

void GamePlay::Update(sf::Time deltaTime)
{
    if (m_startDelayTimer)
    {
        m_timeElapsed += deltaTime;
    }
    if (m_timeElapsed.asSeconds() > m_screenSwitchDelay)
    {
        m_context->m_states->Add(std::make_unique<GameOver>(m_context, m_winStatus), true);
    }
}

void GamePlay::Draw()
{
    if (m_context->m_window->hasFocus())
    {
        m_context->m_window->clear();
        m_context->m_window->draw(*m_board);
        m_context->m_window->display();
    }
}

void GamePlay::Pause()
{
    m_isPaused = true;
}

void GamePlay::Start()
{
    m_isPaused = false;
}