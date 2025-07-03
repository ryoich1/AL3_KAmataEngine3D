#pragma once
#include <stdio.h>
#include <KamataEngine.h>
#include <vector>

using namespace KamataEngine;

enum class MapChipType {
	kBlank, // 空白
	kBlock, // ブロック
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

class MapChipField {

public:

	void ResetMapChipData();

	void LoadMapChipCsv(const std::string& filePath);

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);	

	KamataEngine::Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	uint32_t GetNumBlockVirtical() const { return kNumBlockVirtical; }
	uint32_t GetNumBlockHorizontal() const { return kNumBlockHorizontal; }

	struct IndexSet {

		uint32_t xIndex;
		uint32_t yIndex;

	};

	IndexSet GetMapChipIndexSetByPosition(const Vector3& position);

	struct Rect {

		float left;
		float right;
		float bottom;
		float top;
	};

	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);

private:

	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;

	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipData mapChipData_;

};


