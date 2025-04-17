#include "GameScene.h"

using namespace KamataEngine;

void GameScene::Initialize() {

	texturHandle_ = TextureManager::Load("sample.png");

	sprite_ = Sprite::Create(texturHandle_, {100, 50});

}

void GameScene::Update() {

}

void GameScene::Draw() {

}