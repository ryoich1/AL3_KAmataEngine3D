#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;

class MapChipField;
class Player {

public:

	void Update();

	void Draw();

	void Initialize(Model* model, Camera* camera, Vector3& position);

	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }

	const KamataEngine::Vector3& GetVelocity() const { return Velocity_; }

	void SetmapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	void InputMove();

	void AnimateTurn();

	struct CollisionMapInfo {

		bool ceiling = false;
		bool landing = false;
		bool hitWall = false;
		Vector3 move;
	};

	void CheckMapCollision(CollisionMapInfo& Info);

	void CheckMapCollisionUp(CollisionMapInfo& Info);

	void CheckMapCollisionDown(CollisionMapInfo& Info);

	void CheckMapCollisionRight(CollisionMapInfo& Info);

	void CheckMapCollisionLeft(CollisionMapInfo& Info);

	void CheckMapMove(const CollisionMapInfo& Info);

	void CheckMapCeiling(const CollisionMapInfo& Info);

	void CheckMapLanding(const CollisionMapInfo& Info);

	void CheckMapWall(const CollisionMapInfo& Info);

private:

	MapChipField* mapChipField_ = nullptr;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::WorldTransform worldTransform_;

	Camera* camera_ = nullptr;

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	Vector3 Velocity_ = {};

	static inline const float kAcceleration = 0.05f;
	static inline const float kAttenuation = 0.05f;
	static inline const float kLimitRunSpeed = 0.5f;

	enum class LRDirection {

		kRight,
		kLeft,

	};
	LRDirection lrDirection_ = LRDirection::kRight;

	float turnFirstRotationY_ = 0.0f;
	float turnTimer_ = 0.0f;
	static inline const float kTimeTurn = 0.3f;

	bool onGround_ = true;

	static inline const float kGravityAcceleration = 0.25;
	static inline const float kLimitFallSpeed = 1.0f;
	static inline const float kJumpAcceleration = 1.5f;
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	enum Corner {

		kRightBottom,
		kLeftBottom,
		kRightTop,
		kLeftTop,

		kNumCorner
	};

	Vector3 CornerPosition(const Vector3& center, Corner corner);

	static inline const float kBlank = 5.0f;

	static inline const float kGroundSerchHeight = 0.1f;

	static inline const float kAttenuationLanding = 0.1f;

	static inline const float kAttenuationWall = 0.1f;

};