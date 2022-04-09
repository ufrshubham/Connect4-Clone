#include "PauseGame.hpp"
#include "Strings.hpp"

#include <SFML/Window/Event.hpp>

PauseGame::PauseGame(std::shared_ptr<Context> &context)
    : m_context(context), m_background()
{
    m_background.setSize({(float)context->m_window->getSize().x, (float)context->m_window->getSize().y});
    m_background.setFillColor(sf::Color(50, 50, 50, 200));
}

PauseGame::~PauseGame()
{
}

void PauseGame::Init()
{
    // Title
    m_pauseTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_pauseTitle.setString(PAUSE_TITLE);
    m_pauseTitle.setOrigin(m_pauseTitle.getLocalBounds().width / 2.f,
                           m_pauseTitle.getLocalBounds().height / 2.f);
    m_pauseTitle.setPosition(m_context->m_window->getSize().x / 2.f,
                             m_context->m_window->getSize().y / 2.f);
}

void PauseGame::ProcessInput()
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
            case sf::Keyboard::Escape:
            {
                m_context->m_states->PopCurrent();
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

void PauseGame::Update(sf::Time deltaTime)
{
}

void PauseGame::Draw()
{
    if (m_shouldDraw)
    {
        m_context->m_window->draw(m_background);
        m_context->m_window->draw(m_pauseTitle);
        m_context->m_window->display();
        m_shouldDraw = false;
    }
}
