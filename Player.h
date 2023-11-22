#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player {
public:
	// 初期化
	void Initialize(Model* model);

	// 更新
	void Update();

	void Move();

	void Draw(const ViewProjection& viewProjection);
	
	float GetY() {return worldTransform_.translation_.y;}
 
	float GetX() { return worldTransform_.translation_.x; }
	float GetS() { return worldTransform_.scale_.x;}

private:
	// ワールド変換
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;

	int count_ = 0;
	float PlayerSpeed_ = 0.1f; 
	float DashSpeed_ = 1.0f;
	Input* input_ = nullptr;
};
