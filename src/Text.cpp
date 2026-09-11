//
// Created by Michael Adeyelure on 11/09/2026.
//

#include "Text.h"

Text::Text() = default;

Text::~Text() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }

    if (initialised) {
        TTF_Quit();
    }
}

bool Text::init() {
    if (!TTF_Init()) {
        std::cerr << "TTF_Init Error: " << SDL_GetError() << "\n";
        return false;
    }

    initialised = true;
    return true;
}

bool Text::loadFont(const std::string &font_path, float font_size) {
    if (!initialised) {
        std::cerr << "TTF is uninitialised. Font cannot be loaded." << "\n";
        return false;
    }

    font = TTF_OpenFont(font_path.c_str(), font_size);
    if (!font) {
        std::cerr << "Font could not be loaded." << "\n";
        return false;
    }

    return true;
}
