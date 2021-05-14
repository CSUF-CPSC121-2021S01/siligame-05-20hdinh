#ifndef GAME_H
#define GAME_H

#include <iostream>
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
  std::vector<Opponent>& GetOpponents();
  std::vector<OpponentProjectile>& GetOpponentProjectiles();
  std::vector<PlayerProjectile>& GetPlayerProjectiles();
  Player& GetPlayer();
  void CreateOpponents();
  void CreateOpponentProjectiles();
  void CreatePlayerProjectiles();
  void Init();
  void UpdateScreen();
  void Start();
  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep() override;
  void OnMouseEvent(const graphics::MouseEvent& event) override;

 private:
  graphics::Image screen;
  std::vector<Opponent> OpponentsList;
  std::vector<OpponentProjectile> OpponentProjectilesList;
  std::vector<PlayerProjectile> PlayerProjectilesList;
  Player player = Player();
};

#endif
