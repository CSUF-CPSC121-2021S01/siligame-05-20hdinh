#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include <iostream>
#include <string>
#include <vector>

#include "cpputils/graphics/image.h"

class GameElement {
 public:
  GameElement(const int& x = 0, const int& y = 0, const int& width = 50,
              const int& height = 50);
  int GetX() const;
  void SetX(const int& x);
  int GetY() const;
  void SetY(const int& y);
  int GetWidth() const;
  int GetHeight() const;
  bool GetIsActive() const;
  void SetIsActive(const bool& is_active);
  virtual void Draw(graphics::Image& screen) = 0;
  virtual void Move(const graphics::Image& screen) = 0;
  bool IntersectsWith(GameElement* object);
  bool IsOutOfBounds(const graphics::Image& screen);

 protected:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active_ = true;
};

#endif
