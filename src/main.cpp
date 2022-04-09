#include "Game.hpp"
#include <filesystem>

static void modifyCurrentWorkingDirectory();

int main()
{
    modifyCurrentWorkingDirectory();

    Game game;
    game.Run();
    return 0;
}

void modifyCurrentWorkingDirectory()
{
    while (!std::filesystem::exists("resources"))
    {
        std::filesystem::current_path(std::filesystem::current_path().parent_path());
    }
    auto cwd = std::filesystem::current_path();
}
