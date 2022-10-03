#ifndef LEVELEDITOR_HPP
#define LEVELEDITOR_HPP

#include <fstream>
#include <string>
#include "enemy.hpp"

class LevelEditor
{
public:
    std::vector<std::pair<Spawn, MonsterType>>& GetLevel(int Level);
    int GetNumberOfLevels() {return static_cast<int>(Levels.size());}

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

std::ostream& operator<<(std::ostream& Out, const MonsterType& Type);
std::ostream& operator<<(std::ostream& Out, const Spawn& Type);

#endif // LEVELEDITOR_HPP