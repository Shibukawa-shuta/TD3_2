#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

// きゅうり
class Block {
public:
	// 初期化
	void Initialize(Model* model);

	// 更新
	void Update();

	void Draw(const ViewProjection& viewProjection);

	void Start();

	void Move();
	
private:
	// ワールド変換
	WorldTransform worldTransform_[100];
	// モデル
	Model* model_ = nullptr;

	Input* input_ = nullptr;

	int alive_[100] = {};
};
