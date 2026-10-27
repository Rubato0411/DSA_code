#include "../include/InputHandler.h"
#include <cctype>
#include <cstdio>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace {

int readSingleCharacter() {
#ifdef _WIN32
    return _getch();
#else
    termios oldSettings{};
    if (tcgetattr(STDIN_FILENO, &oldSettings) == -1) {
        return std::getchar();
    }

    termios newSettings = oldSettings;
    newSettings.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newSettings) == -1) {
        return std::getchar();
    }

    const int input = std::getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
    return input;
#endif
}

} // namespace

InputType InputHandler::handleInput() {
    while (true) {
        int input = readSingleCharacter();

        if (input == EOF) {
            return InputType::QUIT_GAME;
        }

        // Filter out unwanted characters like new line or space
        if (input == '\n' || input == '\r' || input == ' ') {
            continue; // Skip unwanted characters
        }

        // Cast input to unsigned char and convert to uppercase
        input = std::toupper(static_cast<unsigned char>(input));

        switch (input) {
            case 'W':
                return InputType::UP;
            case 'S':
                return InputType::DOWN;
            case 'A':
                return InputType::LEFT;
            case 'D':
                return InputType::RIGHT;
            case 'E':
                return InputType::START_GAME;
            case 'Q':
                return InputType::QUIT_GAME;
            case 'U':
                return InputType::UNDO;
            default:
                return InputType::INVALID;
        }
    }
}
