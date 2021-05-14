#include "game.h"

Game::Game(const int& width, const int& height) : screen(width, height) {}

graphics::Image& Game::GetGameScreen() { return screen; }

std::vector<Opponent>& Game::GetOpponents() { return OpponentsList; }

std::vector<OpponentProjectile>& Game::GetOpponentProjectiles() {
  return OpponentProjectilesList;
}

std::vector<PlayerProjectile>& Game::GetPlayerProjectiles() {
  return PlayerProjectilesList;
}

Player& Game::GetPlayer() { return player; }

void Game::CreateOpponents() {
  // Would be easily scalable with vector to store coordinates
  // Just like with drawing the sprites
  Opponent opponent1 = Opponent(50, 50);
  OpponentsList.push_back(opponent1);
  Opponent opponent2 = Opponent(150, 50);
  OpponentsList.push_back(opponent2);
}

void Game::CreateOpponentProjectiles() {
  OpponentProjectile opponent_projectile1 = OpponentProjectile(50, 150);
  OpponentProjectilesList.push_back(opponent_projectile1);
  OpponentProjectile opponent_projectile2 = OpponentProjectile(150, 150);
  OpponentProjectilesList.push_back(opponent_projectile2);
}

void Game::CreatePlayerProjectiles() {
  PlayerProjectile player_projectile1 = PlayerProjectile(50, 200);
  PlayerProjectilesList.push_back(player_projectile1);
  PlayerProjectile player_projectile2 = PlayerProjectile(150, 200);
  PlayerProjectilesList.push_back(player_projectile2);
}

void Game::Init() {
  CreateOpponents();
  CreateOpponentProjectiles();
  CreatePlayerProjectiles();
  player.SetX(50);
  player.SetY(350);
  screen.AddMouseEventListener(*this);
  screen.AddAnimationEventListener(*this);
}

void Game::UpdateScreen() {
  screen.DrawRectangle(0, 0, 800, 600, 0, 0, 0);
  for (int i = 0; i < OpponentsList.size(); i++) {
    if (OpponentsList[i].GetIsActive()) {
      OpponentsList[i].Draw(screen);
    }
  }
  for (int i = 0; i < OpponentProjectilesList.size(); i++) {
    if (OpponentProjectilesList[i].GetIsActive()) {
      OpponentProjectilesList[i].Draw(screen);
    }
  }
  for (int i = 0; i < PlayerProjectilesList.size(); i++) {
    if (PlayerProjectilesList[i].GetIsActive()) {
      PlayerProjectilesList[i].Draw(screen);
    }
  }
  if (player.GetIsActive()) {
    player.Draw(screen);
  }
}

void Game::Start() { screen.ShowUntilClosed(); }

void Game::MoveGameElements() {
  for (int i = 0; i < OpponentsList.size(); i++) {
    if (OpponentsList[i].GetIsActive()) {
      OpponentsList[i].Move(screen);
    }
  }
  for (int i = 0; i < OpponentProjectilesList.size(); i++) {
    if (OpponentProjectilesList[i].GetIsActive()) {
      OpponentProjectilesList[i].Move(screen);
    }
  }
  for (int i = 0; i < PlayerProjectilesList.size(); i++) {
    if (PlayerProjectilesList[i].GetIsActive()) {
      PlayerProjectilesList[i].Move(screen);
    }
  }
}

void Game::FilterIntersections() {
  // Collision between Player and Opponents
  for (int i = 0; i < OpponentsList.size(); i++) {
    if (OpponentsList[i].GetIsActive()) {
      if (player.IntersectsWith(OpponentsList[i])) {
        player.SetIsActive(false);
        OpponentsList[i].SetIsActive(false);
      }
    }
  }
  // Collision between Player and OpponentProjectiles
  for (int i = 0; i < OpponentProjectilesList.size(); i++) {
    if (OpponentProjectilesList[i].GetIsActive()) {
      if (player.IntersectsWith(OpponentProjectilesList[i])) {
        player.SetIsActive(false);
        OpponentProjectilesList[i].SetIsActive(false);
      }
    }
  }
  // Collision between PlayerProjectiles and Opponents
  for (int i = 0; i < PlayerProjectilesList.size(); i++) {
    if (PlayerProjectilesList[i].GetIsActive()) {
      for (int j = 0; j < OpponentsList.size(); j++) {
        if (OpponentsList[j].GetIsActive()) {
          if (PlayerProjectilesList[i].IntersectsWith(OpponentsList[j])) {
            PlayerProjectilesList[i].SetIsActive(false);
            OpponentsList[j].SetIsActive(false);
          }
        }
      }
    }
  }
}

void Game::OnAnimationStep() {
  MoveGameElements();
  FilterIntersections();
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
}
