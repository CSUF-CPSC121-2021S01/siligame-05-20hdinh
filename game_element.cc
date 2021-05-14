#include "game_element.h"

// GameElement class functions
GameElement::GameElement(const int& x, const int& y, const int& width,
                         const int& height)
    : x_(x), y_(y), width_(width), height_(height) {}

int GameElement::GetX() const { return x_; }

void GameElement::SetX(const int& x) { x_ = x; }

int GameElement::GetY() const { return y_; }

void GameElement::SetY(const int& y) { y_ = y; }

int GameElement::GetWidth() const { return width_; }

int GameElement::GetHeight() const { return height_; }

bool GameElement::GetIsActive() const { return is_active_; }

void GameElement::SetIsActive(const bool& is_active) { is_active_ = is_active; }

bool GameElement::IntersectsWith(const GameElement& object) {
  return !(GetX() > object.GetX() + object.GetWidth() ||
           object.GetX() > GetX() + GetWidth() ||
           GetY() > object.GetY() + object.GetHeight() ||
           object.GetY() > GetY() + GetHeight());
}

bool GameElement::IsOutOfBounds(const graphics::Image& screen) {
  return (GetX() + GetWidth() > screen.GetWidth() || 0 > GetX() ||
          GetY() + GetHeight() > screen.GetHeight() || 0 > GetY());
}
