#ifndef DEVELOPERTOOLS_HPP
#define DEVELOPERTOOLS_HPP

#include "ship.hpp"
#include "mothership.hpp"

class DeveloperTools
{
public:
    DeveloperTools() = default;
    ~DeveloperTools() = default;
    DeveloperTools(const DeveloperTools&) = delete;
    DeveloperTools(DeveloperTools&&) = default;
    DeveloperTools& operator=(const DeveloperTools&) = delete;
    DeveloperTools& operator=(DeveloperTools&&) = default;

    void Tick();
    void DrawTools(const Ship& Spacefighter, const Projectile& Bullets, const Mothership& Mothership);
private:
    int Row{20};
    bool ShowPos{false};
    bool ShowFPS{false};
    bool ShowSpeed{false};
    bool NoClipOn{false};
    bool ToggleAll{false};
    bool DevToolsOn{false};
    bool ShowDevTools{true};
    bool DrawCollisions{false};

    void DrawScreenPos(const Ship& Spacefighter);
    void DrawShipSpeed(const Ship& Spacefighter);
    void DrawCollision(const Ship& Spacefighter);
    void DrawCollision(const Projectile& Bullet);
    void DrawCollision(const Mothership& Mothership);
};

#endif // DEVELOPERTOOLS_HPP