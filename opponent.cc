#include "opponent.h"

// Opponent class functions
Opponent::Opponent(const int& x, const int& y, const int& width,
                   const int& height)
    : GameElement(x, y, width, height) {}

void Opponent::Draw(graphics::Image& screen) {
  screen.DrawRectangle(x_ + 10, y_ + 10, 30, 6, 255, 85, 35);
  screen.DrawRectangle(x_, y_ + 15, 50, 25, 128, 55, 20);
  screen.DrawRectangle(x_, y_ + 23, 50, 8, 200, 0, 0);
  screen.DrawRectangle(x_ + 15, y_ + 40, 20, 4, 255, 85, 35);
  screen.DrawLine(x_ + 15, y_ + 40, x_ + 8, y_ + 47, 255, 85, 35, 2);
  screen.DrawLine(x_ + 35, y_ + 40, x_ + 42, y_ + 47, 255, 85, 35, 2);
}

void Opponent::Move(const graphics::Image& screen) {
  SetX(GetX() + 1);
  SetY(GetY() + 1);
  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  if (launch_projectile_timer_ == 20) {
    launch_projectile_timer_ = 0;
    return std::make_unique<OpponentProjectile>(GetX(), GetY());
  } else if (launch_projectile_timer_ == 19) {
    launch_projectile_timer_++;
    return std::make_unique<OpponentProjectile>(GetX(), GetY());
  } else if (launch_projectile_timer_ < 19) {
    launch_projectile_timer_++;
  }
  return nullptr;
}

// OpponentProjectile class functions
OpponentProjectile::OpponentProjectile(const int& x, const int& y,
                                       const int& width, const int& height)
    : GameElement(x, y, width, height) {}

void OpponentProjectile::Draw(graphics::Image& screen) {
  screen.DrawCircle(x_ + 2, y_ + 2, 2, 200, 100, 0);
}

void OpponentProjectile::Move(const graphics::Image& screen) {
  SetX(GetX() + 3);
  SetY(GetY() + 3);
  if (IsOutOfBounds(screen)) {
    SetIsActive(false);
  }
}
