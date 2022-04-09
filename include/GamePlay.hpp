#pragma once

#include <memory>

#include "Game.hpp"
#include "State.hpp"
#include "Board.hpp"

class GamePlay : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    std::unique_ptr<Board> m_board;

    bool m_redTurn;
    bool m_isPaused;
    sf::Time m_timeElapsed;
    float m_screenSwitchDelay;
    WinStatus m_winStatus;
    bool m_startDelayTimer;

public:
    GamePlay(std::shared_ptr<Context> &context);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
    void Pause() override;
    void Start() override;
};