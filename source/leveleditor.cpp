#include "leveleditor.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& Out, const MonsterType& Type);

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
    std::vector<std::pair<MonsterType, std::string>> Temp{};
    std::string Color{};
    std::string Spawn{};
    while (FileStream)
    {
        FileStream >> Color;
        if (Color.starts_with("Enemy="))
        {
            FileStream >> Color;
            FileStream >> Spawn;
            Temp.emplace_back(std::move(std::make_pair(ConvertToType(Color), Spawn)));
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

MonsterType LevelEditor::ConvertToType(std::string_view Color)
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

const std::vector<std::pair<MonsterType, std::string>>& LevelEditor::GetLevel(int Level)
{
    return Levels.at(Level-1);
}

std::ostream& operator<<(std::ostream& Out, const MonsterType& Type) 
{
    switch (Type)
    {
        case MonsterType::Aqua:
            Out << "MonsterType[Aqua]";
            break;
        case MonsterType::Blue:
            Out << "MonsterType[Blue]";
            break;
        case MonsterType::Green:
            Out << "MonsterType[Green]";
            break;
        case MonsterType::Orange:
            Out << "MonsterType[Orange]";
            break;
        case MonsterType::Pink:
            Out << "MonsterType[Pink]";
            break;
        case MonsterType::Purple:
            Out << "MonsterType[Purple]";
            break;
        case MonsterType::Red:
            Out << "MonsterType[Red]";
            break;
        case MonsterType::Yellow:
            Out << "MonsterType[Yellow]";
            break;
    }
    return Out;
}