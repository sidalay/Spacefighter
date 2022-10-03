#include "leveleditor.hpp"
#include <iostream>

LevelEditor::LevelEditor(std::string_view FilePath)
{
    Open(FilePath);
    Parse();
    Print();
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
    std::vector<std::pair<std::string, std::string>> Temp{};
    std::string Color{};
    std::string Spawn{};
    while (FileStream)
    {
        FileStream >> Color;
        if (Color.starts_with("Enemy="))
        {
            FileStream >> Color;
            FileStream >> Spawn;
            Temp.emplace_back(std::move(std::make_pair(Color, Spawn)));
        }
        else if (Color.starts_with("ENDLEVEL"))
        {
            Levels.emplace_back(std::move(Temp));
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
            std::cout << Enemy.first << " " << Enemy.second << '\n';
        }
        ++LevelCounter;
    }
}

const std::vector<std::pair<std::string, std::string>>& LevelEditor::GetLevel(int Level)
{
    return Levels.at(Level-1);
}