#ifndef LEVELEDITOR_HPP
#define LEVELEDITOR_HPP

#include <fstream>
#include <string>
#include "enemy.hpp"

class LevelEditor
{
public:
    const std::vector<std::pair<Spawn, MonsterType>>& GetLevel(int Level);

private:
    std::ifstream FileStream{};
    std::vector<std::vector<std::pair<Spawn, MonsterType>>> Levels{};

    void Open(std::string_view FilePath);
    void Parse();
    void Print();
    MonsterType ConvertToMonster(std::string_view Color);
    Spawn ConvertToSpawn(std::string_view SpawnPoint);
public:
    LevelEditor(std::string_view FilePath);
    ~LevelEditor();
};

#endif // LEVELEDITOR_HPP