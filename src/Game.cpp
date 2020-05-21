#include "Game.hpp"
#include "Input.hpp"
#include "ResourceManager.hpp"
#include "Mask.hpp"
#include "FileUtil.hpp"

#include <SDL.h>

#include <iostream>
#include <random>

Game::Game(uint_t width, uint_t height) : _state(GAME_ACTIVE), _renderer(nullptr) {}

Game::~Game() { delete _renderer; }

#include "ObjectHUD.hpp"

void Game::Init() {
  // Load shaders
  ResourceManager::LoadShader(getResPath("/shaders/default.vs").c_str(), getResPath("/shaders/default.frag").c_str(), nullptr, "default");
  ResourceManager::LoadShader(getResPath("/shaders/blur.vs").c_str(), getResPath("/shaders/blur.frag").c_str(), nullptr, "blur");
  ResourceManager::LoadShader(getResPath("/shaders/scale.vs").c_str(), getResPath("/shaders/scale.frag").c_str(), nullptr, "scale");

  // Load textures
  ResourceManager::LoadAtlas(getResPath("/textures/Atlas.xml").c_str(), GL_TRUE, "test");

  ResourceManager::LoadSprite(getResPath("/animations/ani_mapIcon.xml").c_str());
  ResourceManager::LoadSprite(getResPath("/animations/ani_mapArrow.xml").c_str());
  ResourceManager::LoadSprite(getResPath("/animations/ani_selectName.xml").c_str());

  ResourceManager::LoadMask(getResPath("/masks/block.svg").c_str(), "block");
  ResourceManager::LoadMask(getResPath("/masks/block_half.svg").c_str(), "block_half");
  ResourceManager::LoadMask(getResPath("/masks/hill_1.svg").c_str(), "hill_1");
  ResourceManager::LoadMask(getResPath("/masks/hill_2.svg").c_str(), "hill_2");
  ResourceManager::LoadMask(getResPath("/masks/hill_3.svg").c_str(), "hill_3");
  ResourceManager::LoadMask(getResPath("/masks/mask_greg.svg").c_str(), "mask_greg");

  // Set render-specific controls
  _renderer = new BatchRenderer();

  //ResourceManager::CreateLevel("playerselect", CAMERAMODE::CAMERA_SINGLE);
  //ResourceManager::GetLevel("playerselect").AddInstance("PlayerSelect", Transformation<float_type>());

  //ResourceManager::LoadLevel(getResPath("/maps/sutton.tmx", "sutton", CAMERAMODE::CAMERA_SINGLE);
  //ResourceManager::GetLevel("sutton").AddInstance("HUD", Transformation<float_type>());

  ResourceManager::LoadLevel(getResPath("/maps/collect1.tmx").c_str(), "collect1", CAMERAMODE::CAMERA_GROUP);

  //ResourceManager::SetCurrentLevel("playerselect");
  ResourceManager::SetCurrentLevel("collect1");

  ResourceManager::GetLevel("collect1").AddInstance("mask_greg", Transformation<float_type>());
  ResourceManager::GetLevel("collect1").AddInstance("mask_greg", Transformation<float_type>());
  //ResourceManager::AddInstance("HUD", ENGINE::Vector2<float_t>(0,0));
}

void Game::Update(float_type dt) {
  /*for (auto &obj : ResourceManager::GetCurrentLevel()->GetInstances())
	{
		//obj->PostCollision(dt);
	}*/

  for (auto instA : ResourceManager::GetCurrentLevel()->GetInstances()) {
    if (!instA->IsStatic()) {
      unsigned step = 4;

      ENGINE::Vector2<float_type> t(instA->hSpeed, instA->vSpeed);
      t /= step;

      for (unsigned i = 0; i < step; i++) {
        if (instA->_mask.GetShape() != nullptr) {
          instA->_mask.Translate(t);
          instA->_mask.Transform();
        }

        for (auto instB : ResourceManager::GetCurrentLevel()->GetInstances()) {
          if (instA != instB) {
            Crash2D::Collision collision = instA->GetCollision(instB);

            if (collision.Overlaps()) {
              instA->AddCollision(CollisionInfo(instB, collision));
              instA->Collision(CollisionInfo(instB, collision));
            }
          }
        }
      }
    }
  }

  for (auto& obj : ResourceManager::GetCurrentLevel()->GetInstances()) {
    obj->PostCollision(dt);
    obj->ClearCollisions();
  }

  //Input::ResetButtons();
}

void Game::ProcessInput(float_type dt) {}

void Game::Render() {
  _renderer->Clear();

  for (auto& spr : ResourceManager::GetCurrentLevel()->GetTiles()) {
    _renderer->DrawSprite(spr, ResourceManager::GetCurrentLevel()->GetView());
  }

  for (auto& obj : ResourceManager::GetCurrentLevel()->GetInstances()) {
    obj->Draw(_renderer, ResourceManager::GetCurrentLevel()->GetView());
  }

  /// split ///
  _renderer->SetCoordSplit();

  for (auto& obj : ResourceManager::GetCurrentLevel()->GetInstances()) {
    obj->DrawGUI(_renderer, ResourceManager::GetCurrentLevel()->GetGUIview());
  }

  _renderer->MapData();
  _renderer->Draw();
}

void Game::SetRenderer(BatchRenderer* _renderer) { this->_renderer = _renderer; }

void Game::SetState(const GameState& _state) { this->_state = _state; }

BatchRenderer* Game::GetRenderer() { return _renderer; }

const GameState& Game::GetState() const { return _state; }

ENGINE::Vector2<int_t> Game::_windowSize(1280, 720);

void Game::SetWindowSize(const ENGINE::Vector2<int_t> _windowSize) {
  Game::_windowSize = _windowSize;
}

const ENGINE::Vector2<int_t> Game::GetWindowSize() { return Game::_windowSize; }
