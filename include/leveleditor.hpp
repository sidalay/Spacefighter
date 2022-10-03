#ifndef LEVELEDITOR_HPP
#define LEVELEDITOR_HPP

#include <fstream>
#include <string>
#include "enemy.hpp"

class LevelEditor
{
public:
    const std::vector<std::pair<std::string, MonsterType>>& GetLevel(int Level);

private:
    std::ifstream FileStream{};
    std::vector<std::vector<std::pair<std::string, MonsterType>>> Levels{};

    void Open(std::string_view FilePath);
    void Parse();
    void Print();
    MonsterType ConvertToType(std::string_view Color);
public:
    LevelEditor(std::string_view FilePath);
    ~LevelEditor();
};

#endif // LEVELEDITOR_HPP