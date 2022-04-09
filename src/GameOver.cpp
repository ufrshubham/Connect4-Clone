#include "GameOver.hpp"
#include "GamePlay.hpp"
#include "Strings.hpp"

#include <SFML/Window/Event.hpp>

GameOver::GameOver(std::shared_ptr<Context> &context, WinStatus winStatus)
    : m_context(context), m_isRetryButtonSelected(true),
      m_isRetryButtonPressed(false), m_isExitButtonSelected(false),
      m_isExitButtonPressed(false), m_winStatus(winStatus)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
    // Title
    m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));

    switch (m_winStatus)
    {
    case WinStatus::NoWin:
        m_gameOverTitle.setString(GAME_OVER_DRAW_TITLE);
        break;
    case WinStatus::RedWin:
        m_gameOverTitle.setString(GAME_OVER_RED_WIN_TITLE);
        break;
    case WinStatus::BlueWin:
        m_gameOverTitle.setString(GAME_OVER_BLUE_WIN_TITLE);
        break;
    }

    m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2.f,
                              m_gameOverTitle.getLocalBounds().height / 2.f);
    m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2.f,
                                m_context->m_window->getSize().y / 2.f - 150.f);

    // Play Button
    m_retryButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_retryButton.setString(RETRY_BUTTON_TITLE);
    m_retryButton.setOrigin(m_retryButton.getLocalBounds().width / 2.f,
                            m_retryButton.getLocalBounds().height / 2.f);
    m_retryButton.setPosition(m_context->m_window->getSize().x / 2.f,
                              m_context->m_window->getSize().y / 2.f - 25.f);
    m_retryButton.setCharacterSize(20);

    // Exit Button
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString(EXIT_BUTTON_TITLE);
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2.f,
                           m_exitButton.getLocalBounds().height / 2.f);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2.f,
                             m_context->m_window->getSize().y / 2.f + 25.f);
    m_exitButton.setCharacterSize(20);
}

void GameOver::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
            {
                if (!m_isRetryButtonSelected)
                {
                    m_isRetryButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!m_isExitButtonSelected)
                {
                    m_isRetryButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                m_isRetryButtonPressed = false;
                m_isExitButtonPressed = false;

                if (m_isRetryButtonSelected)
                {
                    m_isRetryButtonPressed = true;
                }
                else
                {
                    m_isExitButtonPressed = true;
                }

                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
}

void GameOver::Update(sf::Time deltaTime)
{
    if (m_isRetryButtonSelected)
    {
        m_retryButton.setFillColor(sf::Color::Black);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else
    {
        m_exitButton.setFillColor(sf::Color::Black);
        m_retryButton.setFillColor(sf::Color::White);
    }

    if (m_isRetryButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    }
    else if (m_isExitButtonPressed)
    {
        m_context->m_window->close();
    }
}

void GameOver::Draw()
{
    m_context->m_window->clear(sf::Color(155, 201, 149, 255));
    m_context->m_window->draw(m_gameOverTitle);
    m_context->m_window->draw(m_retryButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}