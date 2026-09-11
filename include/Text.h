//
// Created by Michael Adeyelure on 11/09/2026.
//

#ifndef OMINOUS_ORBITS_TEXT_H
#define OMINOUS_ORBITS_TEXT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

class Text {
public:
    Text();
    ~Text();

    Text(const Text &) = delete;
    Text &operator=(const Text &) = delete;

    bool init();
    bool loadFont(const std::string &font_path, float font_size);

    [[nodiscard]] TTF_Font *get_font() const { return font; }

private:
    TTF_Font *font = nullptr;
    bool initialised = false;
};

#endif // OMINOUS_ORBITS_TEXT_H
