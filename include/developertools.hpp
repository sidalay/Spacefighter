#ifndef DEVELOPERTOOLS_HPP
#define DEVELOPERTOOLS_HPP

struct DeveloperTools
{
    DeveloperTools() = default;
    ~DeveloperTools() = default;
    DeveloperTools(const DeveloperTools&) = delete;
    DeveloperTools(DeveloperTools&&) = default;
    DeveloperTools& operator=(const DeveloperTools&) = delete;
    DeveloperTools& operator=(DeveloperTools&&) = default;

    void Tick();
    void DrawTools();
    template <typename Type>
    void DrawCollision(Type& Object);

private:
    bool ShowPos{false};
    bool ShowFPS{false};
    bool NoClipOn{false};
    bool ToggleAll{false};
    bool DevToolsOn{false};
    bool ShowDevTools{true};
    bool DrawRectanglesOn{false};
};

#endif // DEVELOPERTOOLS_HPP