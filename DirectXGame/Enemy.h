#pragma once
#include <KamataEngine.h>
#include "MyMath.h"

using namespace KamataEngine;
using namespace MathUtility;

class Player;
class MapChipField;
class Enemy {

public:

	void Initialize(Model* model,Camera* camera, Vector3& position);

	void Update();

	void Draw();

	void SetmapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	void OnCollision(const Player* player);

	AABB GetAABB();

private:

	MapChipField* mapChipField_ = nullptr;

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	Enemy* enemy_ = nullptr;

	enum class LRDirection {

		kRight,
		kLeft,

	};
	LRDirection lrDirection_ = LRDirection::kLeft;

	float turnFirstRotationY_ = 0.0f;
	float turnTimer_ = 0.0f;
	static inline const float kTimeTurn = 0.3f;

	static inline const float kwalkSpeed = 0.01f;

	Vector3 velocity_ = {};

	float walkTimer_ = 0.0f;

	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	Vector3 GetWorldPosition();

};
