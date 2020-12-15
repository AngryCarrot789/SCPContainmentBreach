#ifndef HF_PLAYER
#define HF_PLAYER

#include "../../../math/Matrix4.h"
#include "../../objects/PhysicalGameObject.h"

class Player : public PhysicalGameObject {
public:
	Player();
	virtual ~Player() override {}

	virtual void Reset() override;
	virtual void Update() override;

	void Look(float mouseDx, float mouseDy);
	void Move(float moveF, float moveL, float moveUp);

	float WalkAcceleration = 10.0f;
	float WalkSpeed = 2.7f;

	float cam_rx;
	float cam_ry;
private:
	float move_f;
	float move_l;
	float move_up;


	float bob_mag;
	float bob_phi;

	bool onGround;
};
#endif // !HF_PLAYER