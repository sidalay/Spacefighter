#include "leveleditor.hpp"
#include <iostream>

LevelEditor::LevelEditor(std::string_view FilePath)
{
    Open(FilePath);
    Parse();
    // Print();
}

LevelEditor::~LevelEditor()
{
    FileStream.close();
}

void LevelEditor::Open(std::string_view FilePath)
{
    FileStream.open(FilePath.data());
    if (!FileStream) 
    {
        std::cerr << "\nfile could not be found\n";
    }
}

void LevelEditor::Parse()
{
    std::vector<std::pair<Spawn, MonsterType>> Temp{};
    std::string Color{};
    std::string Spawn{};
    while (FileStream)
    {
        FileStream >> Color;
        if (Color.starts_with("Enemy="))
        {
            FileStream >> Color;
            FileStream >> Spawn;
            Temp.emplace_back(ConvertToSpawn(Spawn), ConvertToMonster(Color));
        }
        else if (Color.starts_with("ENDLEVEL"))
        {
            Levels.push_back(std::move(Temp));
            Temp.clear();
        }
        Color.clear();
        Spawn.clear();
    }
}

void LevelEditor::Print()
{
    int LevelCounter{1};
    for (const auto& Level:Levels) {
        std::cout << "\nLevel " << LevelCounter << "\n\n";
        for (const auto& Enemy:Level) {
            std::cout << Enemy.second << " " << Enemy.first << '\n';
        }
        ++LevelCounter;
    }
}

MonsterType LevelEditor::ConvertToMonster(std::string_view Color)
{
    
    if (Color == "Orange") {
        return MonsterType::Orange;
    }
    else if (Color == "Pink") {
        return MonsterType::Pink;
    }
    else if (Color == "Purple") {
        return MonsterType::Purple;
    }
    else if (Color == "Aqua") {
        return MonsterType::Aqua;
    }
    else if (Color == "Blue") {
        return MonsterType::Blue;
    }
    else if (Color == "Green") {
        return MonsterType::Green;
    }
    else if (Color == "Red") {
        return MonsterType::Red;
    }
    else if (Color == "Yellow") {
        return MonsterType::Yellow;
    }
    else {
        std::cerr << "\nInvalid Color input. Check level.txt.\n";
        return MonsterType::Aqua;
    }
}

Spawn LevelEditor::ConvertToSpawn(std::string_view SpawnPoint)
{
    if (SpawnPoint == "Quadrant1") {
        return Spawn::Quadrant1;
    }
    else if (SpawnPoint == "Quadrant2") {
        return Spawn::Quadrant2;
    }
    else if (SpawnPoint == "Quadrant3") {
        return Spawn::Quadrant3;
    }
    else if (SpawnPoint == "Quadrant4") {
        return Spawn::Quadrant4;
    }
    else if (SpawnPoint == "Mid") {
        return Spawn::Mid;
    }
    else {
        std::cerr << "\nInvalid Spawn input. Check level.txt.\n";
        return Spawn::Mid;
    }
}

std::vector<std::pair<Spawn, MonsterType>>& LevelEditor::GetLevel(int Level)
{
    return Levels.at(Level-1);
}

std::ostream& operator<<(std::ostream& Out, const MonsterType& Type) 
{
    switch (Type)
    {
        case MonsterType::Aqua:
            Out << "MonsterType: [Aqua]";
            break;
        case MonsterType::Blue:
            Out << "MonsterType: [Blue]";
            break;
        case MonsterType::Green:
            Out << "MonsterType: [Gren]";
            break;
        case MonsterType::Orange:
            Out << "MonsterType: [Orng]";
            break;
        case MonsterType::Pink:
            Out << "MonsterType: [Pink]";
            break;
        case MonsterType::Purple:
            Out << "MonsterType: [Purp]";
            break;
        case MonsterType::Red:
            Out << "MonsterType: [Red]";
            break;
        case MonsterType::Yellow:
            Out << "MonsterType: [Yell]";
            break;
    }
    return Out;
}

std::ostream& operator<<(std::ostream& Out, const Spawn& Type)
{
    switch (Type)
    {
        case Spawn::Mid:
            Out << "SpawnPoint: [Mid]";
            break;
        case Spawn::Quadrant1:
            Out << "SpawnPoint: [Quadrant 1]";
            break;
        case Spawn::Quadrant2:
            Out << "SpawnPoint: [Quadrant 2]";
            break;
        case Spawn::Quadrant3:
            Out << "SpawnPoint: [Quadrant 3]";
            break;
        case Spawn::Quadrant4:
            Out << "SpawnPoint: [Quadrant 4]";
            break;
    }
    return Out;
}