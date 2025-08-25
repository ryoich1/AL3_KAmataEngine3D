#pragma once
#include <KamataEngine.h>
#include <vector>
#include "Skydome.h"
#include "MapChipField.h"
#include "Player.h"
#include "CameraController.h"
#include "Enemy.h"
#include "DeathParticles.h"
#include"Fade.h"
#include "TitleScene.h"

class GameScene 
{
public:

	enum class Phase {

		kFadeIn,
		kPlay,
		kDeath,
		kFadeOut,

	};


	~GameScene();

	void Initialize();

	void Update();

	void Draw();

	void GenerateBlocks();

	void CheckAllCollisions();

	void ChangePhase();

	bool IsFinished() const { return finished_; }

private:
	uint32_t textureHandle_ = 0;

	KamataEngine::Model* modelBlock_ = nullptr;

	KamataEngine::WorldTransform worldTransform_;

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	bool isDebugCameraActive_ = false;

	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	Skydome* skydome_ = nullptr;

	KamataEngine::Model* modelSkydome_ = nullptr;

	MapChipField* mapChipField_;

	Player* player_ = nullptr;

	Model* model_ = nullptr;

	Model* modelPlayer_ = nullptr;

	Model* modelDeathParticles_ = nullptr;

	Camera camera_;

	CameraController* cameraController_ = nullptr; 

	std::list<Enemy*> enemies_;

	DeathParticles* deathParticles_ = nullptr;

	Phase phase_;

	bool finished_ = false;

	Fade* fade_ = nullptr;

};
