#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>

#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"

class Player : public GameElement {
 public:
  Player(const int& x = 0, const int& y = 0, const int& width = 50,
         const int& height = 50);
  void Draw(graphics::Image& screen) override;
  void Move(const graphics::Image& screen) override;
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile(const int& x = 0, const int& y = 0, const int& width = 5,
                   const int& height = 5);
  void Draw(graphics::Image& screen) override;
  void Move(const graphics::Image& screen) override;
};

#endif
