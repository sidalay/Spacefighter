#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <raylib.h>

struct GameAudio
{
    constexpr GameAudio() = default;
    ~GameAudio();
    GameAudio(const GameAudio&) = delete;
    GameAudio(GameAudio&&) = default;
    GameAudio& operator=(const GameAudio&) = delete;
    GameAudio& operator=(GameAudio&&) = default;
};

#endif // AUDIO_HPP