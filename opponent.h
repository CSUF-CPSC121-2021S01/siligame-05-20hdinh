#ifndef OPPONENT_H
#define OPPONENT_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "cpputils/graphics/image.h"
#include "game_element.h"

class Opponent : public GameElement {
 public:
  Opponent(const int& x = 0, const int& y = 0, const int& width = 50,
           const int& height = 50);
  void Draw(graphics::Image& screen) override;
  void Move(const graphics::Image& screen) override;
  std::unique_ptr<OpponentProjectile> LaunchProjectile();

 private:
  int launch_projectile_timer_ = 0;
};

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile(const int& x = 0, const int& y = 0, const int& width = 5,
                     const int& height = 5);
  void Draw(graphics::Image& screen) override;
  void Move(const graphics::Image& screen) override;
};

#endif
