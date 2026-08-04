#pragma once
#include <SFML/System/Vector2.hpp>

#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Renderer/WindowManager.h"


class KeyboardAndMouseInputDevice : public InputDevice
{
public:
	KeyboardAndMouseInputDevice();
	~KeyboardAndMouseInputDevice();

	void ProcessInputs() override;

private:
	//Keypress
	bool isWKeyPressed;
	bool isSKeyPressed;
	bool isAKeyPressed;
	bool isDKeyPressed;
	bool isXKeyPressed;
	bool isCKeyPressed;

	bool isUpArrowKeyPressed;
	bool isDownArrowKeyPressed;
	bool isLeftArrowKeyPressed;
	bool isRightArrowKeyPressed;
	bool isLShiftKeyPressed;
	bool isRKeyPressed;
	bool isVKeyPressed;
	bool is1KeyPressed;

	//Debug Keys
	bool isF1KeyPressed;
	bool isF2KeyPressed;
	bool isF3KeyPressed;
	bool isF4KeyPressed;
	bool isF5KeyPressed;
	bool isF6KeyPressed;
	bool isF7KeyPressed;


	//Mouse movement
	sf::Vector2f mousePos;
	sf::Vector2f prevMousePos;
	bool mouseMovingLeft;
	bool mouseMovingRight;
	bool mouseMovingUp;
	bool mouseMovingDown;

	//Mouse buttons
	bool isLMBpressed;
	bool isRMBpressed;
	bool wasLMBpressed = false;
	bool wasRMBpressed = false;

	//Game State manager
	WindowManager* pWindowManager = C_SysContext::Get<WindowManager>();
};

