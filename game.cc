#include "game.h"

Game::Game(const int& width, const int& height) : screen(width, height) {}

graphics::Image& Game::GetGameScreen() { return screen; }

std::vector<std::unique_ptr<Opponent>>& Game::GetOpponents() {
  return OpponentsList;
}

std::vector<std::unique_ptr<OpponentProjectile>>&
Game::GetOpponentProjectiles() {
  return OpponentProjectilesList;
}

std::vector<std::unique_ptr<PlayerProjectile>>& Game::GetPlayerProjectiles() {
  return PlayerProjectilesList;
}

Player& Game::GetPlayer() { return player; }

void Game::CreateOpponents() {
  // Would be easily scalable with vector to store coordinates
  // Just like with drawing the sprites
  std::unique_ptr<Opponent> opponent1 = std::make_unique<Opponent>(50, 50);
  OpponentsList.push_back(std::move(opponent1));
  std::unique_ptr<Opponent> opponent2 = std::make_unique<Opponent>(150, 50);
  OpponentsList.push_back(std::move(opponent2));
  std::unique_ptr<Opponent> opponent3 = std::make_unique<Opponent>(250, 50);
  OpponentsList.push_back(std::move(opponent3));
  std::unique_ptr<Opponent> opponent4 = std::make_unique<Opponent>(350, 50);
  OpponentsList.push_back(std::move(opponent4));
}

void Game::Init() {
  CreateOpponents();
  player.SetX(50);
  player.SetY(350);
  screen.AddMouseEventListener(*this);
  screen.AddAnimationEventListener(*this);
}

void Game::UpdateScreen() {
  screen.DrawRectangle(0, 0, 800, 600, 0, 0, 0);
  screen.DrawText(0, 0, std::to_string(score_), 12, 0, 0, 0);
  for (int i = 0; i < OpponentsList.size(); i++) {
    if (OpponentsList[i]->GetIsActive()) {
      OpponentsList[i]->Draw(screen);
    }
  }
  for (int i = 0; i < OpponentProjectilesList.size(); i++) {
    if (OpponentProjectilesList[i]->GetIsActive()) {
      OpponentProjectilesList[i]->Draw(screen);
    }
  }
  for (int i = 0; i < PlayerProjectilesList.size(); i++) {
    if (PlayerProjectilesList[i]->GetIsActive()) {
      PlayerProjectilesList[i]->Draw(screen);
    }
  }
  if (player.GetIsActive()) {
    player.Draw(screen);
  }
  if (has_lost_) {
    screen.DrawText(375, 275, "Game Over", 25, 0, 0, 0);
  }
}

void Game::Start() { screen.ShowUntilClosed(); }

void Game::MoveGameElements() {
  for (int i = 0; i < OpponentsList.size(); i++) {
    if (OpponentsList[i]->GetIsActive()) {
      OpponentsList[i]->Move(screen);
    }
  }
  for (int i = 0; i < OpponentProjectilesList.size(); i++) {
    if (OpponentProjectilesList[i]->GetIsActive()) {
      OpponentProjectilesList[i]->Move(screen);
    }
  }
  for (int i = 0; i < PlayerProjectilesList.size(); i++) {
    if (PlayerProjectilesList[i]->GetIsActive()) {
      PlayerProjectilesList[i]->Move(screen);
    }
  }
}

void Game::FilterIntersections() {
  // Collision between Player and Opponents
  for (int i = 0; i < OpponentsList.size(); i++) {
    if (OpponentsList[i]->GetIsActive()) {
      if (player.IntersectsWith((OpponentsList[i].get()))) {
        player.SetIsActive(false);
        OpponentsList[i]->SetIsActive(false);
        has_lost_ = true;
      }
    }
  }
  // Collision between Player and OpponentProjectiles
  for (int i = 0; i < OpponentProjectilesList.size(); i++) {
    if (OpponentProjectilesList[i]->GetIsActive()) {
      if (player.IntersectsWith((OpponentProjectilesList[i].get()))) {
        player.SetIsActive(false);
        OpponentProjectilesList[i]->SetIsActive(false);
        has_lost_ = true;
      }
    }
  }
  // Collision between PlayerProjectiles and Opponents
  for (int i = 0; i < PlayerProjectilesList.size(); i++) {
    if (PlayerProjectilesList[i]->GetIsActive()) {
      for (int j = 0; j < OpponentsList.size(); j++) {
        if (OpponentsList[j]->GetIsActive()) {
          if (PlayerProjectilesList[i]->IntersectsWith(
                  (OpponentsList[j].get()))) {
            PlayerProjectilesList[i]->SetIsActive(false);
            OpponentsList[j]->SetIsActive(false);
            if (player.GetIsActive()) {
              score_++;
            }
          }
        }
      }
    }
  }
}

void Game::OnAnimationStep() {
  if (OpponentsList.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  screen.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent& event) {
  if (event.GetMouseAction() == graphics::MouseAction::kMoved ||
      event.GetMouseAction() == graphics::MouseAction::kDragged) {
    if (!(event.GetX() + (player.GetWidth() / 2) > screen.GetWidth() ||
          (player.GetWidth() / 2) > event.GetX() ||
          event.GetY() + (player.GetHeight() / 2) > screen.GetHeight() ||
          (player.GetHeight() / 2) > event.GetY())) {
      player.SetX(event.GetX() - (player.GetWidth() / 2));
      player.SetY(event.GetY() - (player.GetHeight() / 2));
    }
  }
  if (event.GetMouseAction() == graphics::MouseAction::kPressed) {
    if (!(event.GetX() + 5 > screen.GetWidth() || 5 > event.GetX() ||
          event.GetY() + 5 > screen.GetHeight() || 5 > event.GetY())) {
      std::unique_ptr<PlayerProjectile> projectile =
          std::make_unique<PlayerProjectile>(event.GetX(), event.GetY());
      PlayerProjectilesList.push_back(std::move(projectile));
    }
  }
}

int Game::GetScore() const { return score_; }

bool Game::HasLost() const { return has_lost_; }

void Game::LaunchProjectiles() {
  for (int i = 0; i < OpponentsList.size(); i++) {
    OpponentsList[i]->LaunchProjectile();
    if (OpponentsList[i]->LaunchProjectile() != nullptr) {
      // Potential error: creating 2 projectiles
      OpponentProjectilesList.push_back(
          std::move(OpponentsList[i]->LaunchProjectile()));
    }
  }
}

void Game::RemoveInactive() {
  for (int i = (OpponentsList.size() - 1); i >= 0; i--) {
    if (!(OpponentsList[i]->GetIsActive())) {
      OpponentsList.erase(OpponentsList.begin() + i);
    }
  }
  for (int i = (OpponentProjectilesList.size() - 1); i >= 0; i--) {
    if (!(OpponentProjectilesList[i]->GetIsActive())) {
      OpponentProjectilesList.erase(OpponentProjectilesList.begin() + i);
    }
  }
  for (int i = (PlayerProjectilesList.size() - 1); i >= 0; i--) {
    if (!(PlayerProjectilesList[i]->GetIsActive())) {
      PlayerProjectilesList.erase(PlayerProjectilesList.begin() + i);
    }
  }
}
