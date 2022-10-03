#ifndef LEVELEDITOR_HPP
#define LEVELEDITOR_HPP

#include <fstream>
#include <vector>
#include <string>
#include <string_view>

class LevelEditor
{
public:
    const std::vector<std::pair<std::string, std::string>>& GetLevel(int Level);

private:
    std::ifstream FileStream{};
    std::vector<std::vector<std::pair<std::string, std::string>>> Levels{};

    void Open(std::string_view FilePath);
    void Parse();
    void Print();

public:
    LevelEditor(std::string_view FilePath);
    ~LevelEditor();
};

#endif // LEVELEDITOR_HPP