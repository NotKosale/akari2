#pragma once

#include "gameobject.h"
#include <sgg/graphics.h>
#include "box.h"

class Player : public Box, public GameObject
{
	// animated player
	std::vector<std::string> m_spritesidle;
	std::vector<std::string> m_spritesleft;
	std::vector<std::string> m_spritesright;
	std::vector<std::string> m_spritesjump;
	std::vector<std::string> m_spritesfall;
	std::vector<std::string> m_spritesfallleft;
	std::vector<std::string> m_spritesjumpleft;
	std::vector<std::string> m_spritesLightAttack;
	std::vector<std::string> m_spritesLightAttackleft;
	std::vector<std::string> m_spritesidleleft;
	std::vector<std::string> m_spritesHeavyAttack;
	std::vector<std::string> m_spritesHeavyAttackleft;

	graphics::Brush m_brush_player;

	const float m_accel_horizontal = 20.0f;
	const float m_accel_vertical = 250.1f;
	const float m_max_velocity = 5.0f;
	const float m_gravity = 10.0f;
public:

	//AnimationState
	enum AnimationState
	{
		IDLE,
		RUN,
		ATTACK,
		HEAVYATTACK
	};

	float playerWidth = 1.7f;
	float playerHeight = 1.7f;
	float playerCollisionWidth = 0.3f;
	float playerCollisionHeight = 0.51f;
	bool isCollidingSideways = false;
	bool isTouchingWall = false;
	bool isCollidingDown = false;
	float m_vx = 0.0f;
	float m_vy = 0.0f;
	float animationtime = 0.0f;
	int forwardDir = 1;
	AnimationState m_animation_state = IDLE;




public:
	void update(float dt) override;
	void draw() override;
	void init() override;
	void movePlayer(float dt); // move player
	Player(std::string name) : GameObject(name) {}


protected:
	void debugDraw();

	// dynamic motion control

};