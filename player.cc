#include "player.h"

// Player class functions
Player::Player(const int& x, const int& y, const int& width, const int& height)
    : GameElement(x, y, width, height) {}

void Player::Draw(graphics::Image& screen) {
  screen.DrawRectangle(x_ + 17, y_ + 10, 16, 30, 50, 80, 255);
  screen.DrawRectangle(x_, y_ + 14, 50, 20, 25, 255, 255);
  screen.DrawRectangle(x_ + 5, y_, 11, 50, 80, 45, 170);
  screen.DrawRectangle(x_ + 34, y_, 11, 50, 80, 45, 170);
  screen.DrawLine(x_ + 21, y_ + 10, x_ + 21, y_ + 18, 50, 80, 255, 2);
  screen.DrawLine(x_ + 28, y_ + 10, x_ + 28, y_ + 18, 50, 80, 255, 2);
}

void Player::Move(const graphics::Image& screen) {
  // Intentionally left empty:: movement implemented in Game
  // Function exists so player.cc compiles
}

// PlayerProjectile class functions
PlayerProjectile::PlayerProjectile(const int& x, const int& y, const int& width,
                                   const int& height)
    : GameElement(x, y, width, height) {}

void PlayerProjectile::Draw(graphics::Image& screen) {
  screen.DrawCircle(x_ + 2, y_ + 2, 2, 0, 0, 200);
}

void PlayerProjectile::Move(const graphics::Image& screen) {
  // SetX(GetX() - 3);
  SetY(GetY() - 5);
  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  }
}
