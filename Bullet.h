#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Bullet {
public:
	// 初期化
	void Initialize(Model* model);

	// 更新
	void Update();

	void Move();

	void Space();

	void Draw(const ViewProjection& viewProjection);

	void SetY(float y) { PlayerY_ = y;}
	void SetX(float x) { PlayerX_ = x; }
	void SetS(float s) { PlayerS_ = s; }


private:
	// ワールド変換
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;

	int count_ = 0;
	float BulletSpeedX_ = 0.1f;
	float BulletSpeedY_ = 0.1f;
	float rotSpeed_ = 0.25f;

	float PlayerX_ = 0.0f;
	float PlayerY_ = 0.0f;
	float PlayerS_ = 0.0f;
	Input* input_ = nullptr;
};
