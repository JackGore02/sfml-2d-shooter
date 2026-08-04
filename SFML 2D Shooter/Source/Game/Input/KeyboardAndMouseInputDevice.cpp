#include "KeyboardAndMouseInputDevice.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>


KeyboardAndMouseInputDevice::KeyboardAndMouseInputDevice()
{
	prevMousePos = mousePos;
}

KeyboardAndMouseInputDevice::~KeyboardAndMouseInputDevice()
{
	
}

void KeyboardAndMouseInputDevice::ProcessInputs()
{
	//Set up keyboard presses
	isWKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	isSKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	isAKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	isDKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	isXKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::X);
	isCKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::C);

	isUpArrowKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	isDownArrowKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	isLeftArrowKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	isRightArrowKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	isLShiftKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
	isRKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
	isVKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::V);
	is1KeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);

	//Debug keys
	isF1KeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F1);
	isF2KeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F2);
	isF3KeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F3);
	isF4KeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F4);
	isF5KeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F5);
	isF6KeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F6);
	isF7KeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F7);

	//Map to virtual gamepad DPAD
	//Movement - Digital (Dpad), simply set the Dpad pressed to the WASD pressed
	this->m_DigitalInputs[E_DigitalInput_DpadUp].SetPressed(isWKeyPressed || isUpArrowKeyPressed);
	this->m_DigitalInputs[E_DigitalInput_DpadDown].SetPressed(isSKeyPressed || isDownArrowKeyPressed);
	this->m_DigitalInputs[E_DigitalInput_DpadLeft].SetPressed(isAKeyPressed || isLeftArrowKeyPressed);
	this->m_DigitalInputs[E_DigitalInput_DpadRight].SetPressed(isDKeyPressed || isRightArrowKeyPressed);
	this->m_DigitalInputs[E_DigitalInput_B].SetPressed(isLShiftKeyPressed);
	this->m_DigitalInputs[E_DigitalInput_X].SetPressed(isRKeyPressed);
	this->m_DigitalInputs[E_DigitalInput_RightShoulder].SetPressed(isVKeyPressed);
	this->m_DigitalInputs[E_DigitalInput_LeftShoulder].SetPressed(is1KeyPressed);

	////Movement - Analogue (Left thumbstick), Y axis - W = -1, S = 1, X axis - A = 1, D = -1
	//if (isWKeyPressed || isUpArrowKeyPressed)
	//	this->m_AnalogueInputs[E_AnalogueInput_ThumbLY].SetValue(-1);
	//if (isSKeyPressed || isDownArrowKeyPressed)
	//	this->m_AnalogueInputs[E_AnalogueInput_ThumbLY].SetValue(1);
	//if (isAKeyPressed || isLeftArrowKeyPressed)
	//	this->m_AnalogueInputs[E_AnalogueInput_ThumbLX].SetValue(-1);
	//if(isDKeyPressed || isRightArrowKeyPressed)
	//	this->m_AnalogueInputs[E_AnalogueInput_ThumbLX].SetValue(1);
	//if (!isWKeyPressed && !isSKeyPressed && !isUpArrowKeyPressed && !isDownArrowKeyPressed)
	//	this->m_AnalogueInputs[E_AnalogueInput_ThumbLY].SetValue(0);
	//if (!isAKeyPressed && !isDKeyPressed && !isLeftArrowKeyPressed && !isRightArrowKeyPressed)
	//	this->m_AnalogueInputs[E_AnalogueInput_ThumbLX].SetValue(0);

	//Start and Back keys
	this->m_DigitalInputs[E_DigitalInput_Start].SetPressed(isXKeyPressed);
	this->m_DigitalInputs[E_DigitalInput_Back].SetPressed(isCKeyPressed);
	
	//Debug Keys
	this->m_DigitalInputs[E_DigitalInput_DebugChangeGameState].SetPressed(isF1KeyPressed);
	this->m_DigitalInputs[E_DigitalInput_DebugIncreaseHealth].SetPressed(isF2KeyPressed);
	this->m_DigitalInputs[E_DigitalInput_DebugDecreaseHealth].SetPressed(isF3KeyPressed);
	this->m_DigitalInputs[E_DigitalInput_DebugIncreaseScore].SetPressed(isF4KeyPressed);
	this->m_DigitalInputs[E_DigitalInput_DebugDecreaseScore].SetPressed(isF5KeyPressed);
	this->m_DigitalInputs[E_DigitalInput_DebugIncreaseMaxHealth].SetPressed(isF6KeyPressed);
	this->m_DigitalInputs[E_DigitalInput_DebugDecreaseMaxHealth].SetPressed(isF7KeyPressed);

	//Set up Mouse movement;
	sf::Window* w = pWindowManager->GetWindow();
	//Screen position
	mousePos = sf::Vector2f(sf::Mouse::getPosition(*w));
	m_pointerPos = mousePos;

	//If the x value of the current mouse pos is less than/greater than the previous mouse x pos, the mouse is moving left/right respectively
	//If the y value of the current mouse pos is less than/greater than the previous mouse y pos, the mouse is moving up/down respectively
	mouseMovingDown = (mousePos.y > prevMousePos.y);
	mouseMovingUp = (mousePos.y < prevMousePos.y);
	mouseMovingLeft = (mousePos.x < prevMousePos.x);
	mouseMovingRight = (mousePos.x > prevMousePos.x);

	float diff;
	float mouseMovementSpeed = 0.1f;
	//Map to virtual gamepad Rstick
	if (mouseMovingLeft)
	{
		//Calculate the difference
		diff = (mousePos.x - prevMousePos.x) * mouseMovementSpeed;
		//Set the value of the thumbstick to this difference
		this->m_AnalogueInputs[E_AnalogueInput_ThumbRX].SetValue(diff);
	}
	else if (mouseMovingRight)
	{
		//Calculate the difference
		diff = (mousePos.x - prevMousePos.x) * mouseMovementSpeed;
		//Set the value of the thumbstick to this difference
		this->m_AnalogueInputs[E_AnalogueInput_ThumbRX].SetValue(diff);
	}
	else
		this->m_AnalogueInputs[E_AnalogueInput_ThumbRX].SetValue(0);

	if (mouseMovingUp)
	{
		//Calculate the difference
		diff = (mousePos.y - prevMousePos.y) * mouseMovementSpeed;
		//Set the value of the thumbstick to this difference
		this->m_AnalogueInputs[E_AnalogueInput_ThumbRY].SetValue(diff);
	}
	else if (mouseMovingDown)
	{
		//Calculate the difference
		diff = (mousePos.y - prevMousePos.y) * mouseMovementSpeed;
		//Set the value of the thumbstick to this difference
		this->m_AnalogueInputs[E_AnalogueInput_ThumbRY].SetValue(diff);
	}
	else
		this->m_AnalogueInputs[E_AnalogueInput_ThumbRY].SetValue(0);		

	//Set the previous mouse pos to the current mouse pos
	prevMousePos = mousePos;

	//Mouse buttons
	isLMBpressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	isRMBpressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);

	//Map to virtual gamepad triggers
	if (isLMBpressed && !wasLMBpressed)
		this->m_AnalogueInputs[E_AnalogueInput_LeftTrigger].SetValue(1);
	else
		this->m_AnalogueInputs[E_AnalogueInput_LeftTrigger].SetValue(0);

	if (isRMBpressed && !wasRMBpressed)
		this->m_AnalogueInputs[E_AnalogueInput_RightTrigger].SetValue(1);
	else
		this->m_AnalogueInputs[E_AnalogueInput_RightTrigger].SetValue(0);

	wasLMBpressed = isLMBpressed;
	wasRMBpressed = isRMBpressed;
}


