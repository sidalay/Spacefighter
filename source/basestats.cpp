#include "basestats.hpp"

BaseStats::BaseStats(const GameTexture& Textures,
                     const GameAudio& Audio,
                     const Randomizer& RandomEngine,
                     Projectile& Projectiles,
                     const raylib::Window& Window,
                     const raylib::Vector2 ScreenPos)
    : Textures{Textures}, 
      Audio{Audio}, 
      RandomEngine{RandomEngine}, 
      Projectiles{Projectiles}, 
      Window{Window}, 
      ScreenPos{ScreenPos} {};

BaseStats::BaseStats(BaseStats&& Object)
    : Textures{std::move(Object.Textures)},
      Audio{std::move(Object.Audio)},
      RandomEngine{std::move(Object.RandomEngine)},
      Projectiles{Object.Projectiles},
      Window{std::move(Object.Window)},
      ScreenPos{std::move(Object.ScreenPos)},
      Speed{std::move(Object.Speed)},
      Alive{std::move(Object.Alive)},
      Dying{std::move(Object.Dying)},
      TakingDamage{std::move(Object.TakingDamage)},
      UpdateTime{std::move(Object.UpdateTime)},
      RunningTime{std::move(Object.RunningTime)},
      AttackTime{std::move(Object.AttackTime)},
      CooldownTime{std::move(Object.CooldownTime)},
      Health{std::move(Object.Health)},
      MaxSpeed{std::move(Object.MaxSpeed)},
      BrakeSpeed{std::move(Object.BrakeSpeed)},
      Scale{std::move(Object.Scale)} {}

BaseStats& BaseStats::operator=(BaseStats&& Object)
{
    if (this == &Object)
    {
        return *this;
    }

    this->Projectiles = std::move(Object.Projectiles);
    this->ScreenPos = std::move(Object.ScreenPos);
    this->Speed = std::move(Object.Speed);
    this->Alive = std::move(Object.Alive);
    this->Dying = std::move(Object.Dying);
    this->TakingDamage = std::move(Object.TakingDamage);
    this->UpdateTime = std::move(Object.UpdateTime);
    this->RunningTime = std::move(Object.RunningTime);
    this->AttackTime = std::move(Object.AttackTime);
    this->CooldownTime = std::move(Object.CooldownTime);
    this->Health = std::move(Object.Health);
    this->MaxSpeed = std::move(Object.MaxSpeed);
    this->BrakeSpeed = std::move(Object.BrakeSpeed);
    this->Scale = std::move(Object.Scale);

    return *this;
}