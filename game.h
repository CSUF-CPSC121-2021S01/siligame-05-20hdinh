#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game(const int& width = 800, const int& height = 600);
  graphics::Image& GetGameScreen();
  std::vector<std::unique_ptr<Opponent>>& GetOpponents();
  std::vector<std::unique_ptr<OpponentProjectile>>& GetOpponentProjectiles();
  std::vector<std::unique_ptr<PlayerProjectile>>& GetPlayerProjectiles();
  Player& GetPlayer();
  void CreateOpponents();
  void Init();
  void UpdateScreen();
  void Start();
  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep() override;
  void OnMouseEvent(const graphics::MouseEvent& event) override;
  int GetScore() const;
  bool HasLost() const;
  void LaunchProjectiles();
  void RemoveInactive();

 private:
  graphics::Image screen;
  std::vector<std::unique_ptr<Opponent>> OpponentsList;
  std::vector<std::unique_ptr<OpponentProjectile>> OpponentProjectilesList;
  std::vector<std::unique_ptr<PlayerProjectile>> PlayerProjectilesList;
  Player player = Player();
  int score_ = 0;
  bool has_lost_ = false;
};

#endif
