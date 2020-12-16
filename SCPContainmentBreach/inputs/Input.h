#ifndef HF_INPUTS
#define HF_INPUTS

struct tagRAWINPUT;
class Input {
public:
	Input();

	void UpdateInputs();
	void UpdateRaw(const tagRAWINPUT* raw);

	//Keyboard
	bool KeysDown[256];
	bool KeysPressed[256];

	//Mouse
	bool MouseButtonsDown[3];
	bool MouseButtonsPressed[3];
	float mouse_dx;
	float mouse_dy;
	float mouse_ddx;
	float mouse_ddy;

	float MouseSmoothing = 0.5f;
};

#endif // !HF_INPUTS