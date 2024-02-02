#include "player.h"
#include "util.h"
#include <cmath>
#include <iostream>

void Player::update(float dt)
{
	float delta_time = dt / 1000.0f;

	movePlayer(dt);

	// update offset for other game objects
	m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
	m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

	GameObject::update(dt);

	
}

void Player::draw()
{
	//Player Diraction
	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		forwardDir = -1;
	}

	if (graphics::getKeyState(graphics::SCANCODE_D)) {
		forwardDir = 1;
	}
	
	
	animationtime += 0.07f;
	

	//Fall Trigger
	if (m_vy > 0.0f && !graphics::getKeyState(graphics::SCANCODE_K) && !graphics::getKeyState(graphics::SCANCODE_L))
	{
		if (forwardDir == -1)
		{
				int sprite = (int)fmod(animationtime, m_spritesfallleft.size());
				m_brush_player.texture = m_spritesfallleft[sprite];
				graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, playerWidth, playerHeight, m_brush_player);
		}
		else if (forwardDir == 1)
		{
				int sprite = (int)fmod(animationtime, m_spritesfall.size());
				m_brush_player.texture = m_spritesfall[sprite];
				graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, playerWidth, playerHeight, m_brush_player);
		}
	}
	

    //Idle Trigger    
    if (!graphics::getKeyState(graphics::SCANCODE_A) && !graphics::getKeyState(graphics::SCANCODE_D) 
		&& !graphics::getKeyState(graphics::SCANCODE_W) && m_vy == 0.0f && !graphics::getKeyState(graphics::SCANCODE_K) && !graphics::getKeyState(graphics::SCANCODE_L))
    {
		if (m_animation_state != IDLE)
		{
			m_animation_state = IDLE;
			animationtime = 0;
		}
		if (forwardDir == -1)
		{
			int sprite = (int)fmod(animationtime, m_spritesidleleft.size());
			m_brush_player.texture = m_spritesidleleft[sprite];
			graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, playerWidth, playerHeight, m_brush_player);
		}
		else if (forwardDir == 1)
		{
			int sprite = (int)fmod(animationtime, m_spritesidle.size());
			m_brush_player.texture = m_spritesidle[sprite];
			graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, playerWidth, playerHeight, m_brush_player);
		}
    }
	
	//Jump Trigger
	if (m_vy < 0.0f && !graphics::getKeyState(graphics::SCANCODE_K) && !graphics::getKeyState(graphics::SCANCODE_L))
	{
		if (forwardDir == -1)
		{
			int sprite = (int)fmod(animationtime, m_spritesjumpleft.size());
			m_brush_player.texture = m_spritesjumpleft[sprite];
			graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, playerWidth, playerHeight, m_brush_player);
		}
		else if (forwardDir == 1)
		{
			int sprite = (int)fmod(animationtime, m_spritesjump.size());
			m_brush_player.texture = m_spritesjump[sprite];
			graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, playerWidth, playerHeight, m_brush_player);
		}
	}

	//Run Trigger
	if (graphics::getKeyState(graphics::SCANCODE_A) && (m_vy == 0.0f) && !graphics::getKeyState(graphics::SCANCODE_K) && !graphics::getKeyState(graphics::SCANCODE_L)
		|| graphics::getKeyState(graphics::SCANCODE_D) && (m_vy == 0.0f) && !graphics::getKeyState(graphics::SCANCODE_K) && !graphics::getKeyState(graphics::SCANCODE_L))
	{
		if (m_animation_state != RUN)
		{
			m_animation_state = RUN;
			animationtime = 0;
		}
		if (forwardDir == -1)
		{
			int sprite = (int)fmod(100.0f - m_pos_x * 2.0f, m_spritesleft.size());
			m_brush_player.texture = m_spritesleft[sprite];
			graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, playerWidth, playerHeight, m_brush_player);
		}
		else if (forwardDir == 1)
		{
			int sprite = (int)fmod(100.0f - m_pos_x * 2.0f, m_spritesright.size());
			m_brush_player.texture = m_spritesright[sprite];
			graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, playerWidth, playerHeight, m_brush_player);
		}

	}


	//LightAttack Trigger
	if (graphics::getKeyState(graphics::SCANCODE_K) && !graphics::getKeyState(graphics::SCANCODE_L))
	{
		if (m_animation_state != ATTACK)
		{
			m_animation_state = ATTACK;
			animationtime = 0;
		}
		if (forwardDir == -1)
		{
			int sprite = (int)fmod(animationtime * 2, m_spritesLightAttackleft.size());
			m_brush_player.texture = m_spritesLightAttackleft[sprite];
			graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, playerWidth, 2.3f, m_brush_player);
			return;
		}
		else if (forwardDir == 1)
		{
			int sprite = (int)fmod(animationtime * 2, m_spritesLightAttack.size());
			m_brush_player.texture = m_spritesLightAttack[sprite];
			graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, playerWidth, 2.3f, m_brush_player);
		}
	}

	//HeavyAttack Trigger
	if (graphics::getKeyState(graphics::SCANCODE_L) && !graphics::getKeyState(graphics::SCANCODE_K))
	{
		if (m_animation_state != HEAVYATTACK)
		{
			m_animation_state = HEAVYATTACK;
			animationtime = 0;
		}
		if (forwardDir == -1)
		{
			int sprite = (int)fmod(animationtime * 2, m_spritesHeavyAttackleft.size());
			m_brush_player.texture = m_spritesHeavyAttackleft[sprite];
			graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, playerWidth, 2.3f, m_brush_player);
			return;
		}
		else if (forwardDir == 1)
		{
			int sprite = (int)fmod(animationtime * 2, m_spritesHeavyAttack.size());
			m_brush_player.texture = m_spritesHeavyAttack[sprite];
			graphics::drawRect(m_state->getCanvasWidth() * 0.5f, m_state->getCanvasHeight() * 0.5f, playerWidth, 2.3f, m_brush_player);
		}
	}

	
	if (m_state->m_debugging)
		debugDraw();
}


void Player::init()
{
	
		int bitmapHeight = 100;
		float layerHeight = 0.5f;
		m_pos_x = 5.0f;
		m_pos_y = static_cast<float>(bitmapHeight - 2) * layerHeight - m_height / 2.0f;


		m_state->m_global_offset_x = m_state->getCanvasWidth() / 2.0f - m_pos_x;
		m_state->m_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;

		m_brush_player.fill_opacity = 1.0f;
		m_brush_player.outline_opacity = 0.0f;
	
	//Idle Animation
	m_spritesidle.push_back(m_state->getFullAssetPath("idle1.png"));
	m_spritesidle.push_back(m_state->getFullAssetPath("idle2.png"));
	m_spritesidle.push_back(m_state->getFullAssetPath("idle3.png"));
	m_spritesidle.push_back(m_state->getFullAssetPath("idle4.png"));
	m_spritesidleleft.push_back(m_state->getFullAssetPath("idleleft1.png"));
	m_spritesidleleft.push_back(m_state->getFullAssetPath("idleleft2.png"));
	m_spritesidleleft.push_back(m_state->getFullAssetPath("idleleft3.png"));
	m_spritesidleleft.push_back(m_state->getFullAssetPath("idleleft4.png"));

	//Run Animation
	m_spritesleft.push_back(m_state->getFullAssetPath("runleft1.png"));
	m_spritesleft.push_back(m_state->getFullAssetPath("runleft2.png"));
	m_spritesleft.push_back(m_state->getFullAssetPath("runleft3.png"));
	m_spritesleft.push_back(m_state->getFullAssetPath("runleft4.png"));
	m_spritesleft.push_back(m_state->getFullAssetPath("runleft5.png"));
	m_spritesleft.push_back(m_state->getFullAssetPath("runleft6.png"));
	m_spritesleft.push_back(m_state->getFullAssetPath("runleft7.png"));
	m_spritesleft.push_back(m_state->getFullAssetPath("runleft8.png"));
	m_spritesright.push_back(m_state->getFullAssetPath("tile00.png"));
	m_spritesright.push_back(m_state->getFullAssetPath("tile01.png"));
	m_spritesright.push_back(m_state->getFullAssetPath("tile02.png"));
	m_spritesright.push_back(m_state->getFullAssetPath("tile03.png"));
	m_spritesright.push_back(m_state->getFullAssetPath("tile04.png"));
	m_spritesright.push_back(m_state->getFullAssetPath("tile05.png"));
	m_spritesright.push_back(m_state->getFullAssetPath("tile06.png"));
	m_spritesright.push_back(m_state->getFullAssetPath("tile07.png"));

	//Jump Animation
	m_spritesjump.push_back(m_state->getFullAssetPath("jump0.png"));
	m_spritesjump.push_back(m_state->getFullAssetPath("jump1.png"));
	m_spritesjumpleft.push_back(m_state->getFullAssetPath("jumpleft0.png"));
	m_spritesjumpleft.push_back(m_state->getFullAssetPath("jumpleft1.png"));

	//Fall Animation
	m_spritesfall.push_back(m_state->getFullAssetPath("fall1.png"));
	m_spritesfall.push_back(m_state->getFullAssetPath("fall2.png"));	
	m_spritesfallleft.push_back(m_state->getFullAssetPath("fallleft0.png"));
	m_spritesfallleft.push_back(m_state->getFullAssetPath("fallleft1.png"));

	//LightAttack Animation
	m_spritesLightAttack.push_back(m_state->getFullAssetPath("attack1.png"));
	m_spritesLightAttack.push_back(m_state->getFullAssetPath("attack2.png"));
	m_spritesLightAttack.push_back(m_state->getFullAssetPath("attack3.png"));
	m_spritesLightAttack.push_back(m_state->getFullAssetPath("attack4.png"));
	m_spritesLightAttackleft.push_back(m_state->getFullAssetPath("attackleft1.png"));
	m_spritesLightAttackleft.push_back(m_state->getFullAssetPath("attackleft2.png"));
	m_spritesLightAttackleft.push_back(m_state->getFullAssetPath("attackleft3.png"));
	m_spritesLightAttackleft.push_back(m_state->getFullAssetPath("attackleft4.png"));

	//HeavyAttack Animation
	m_spritesHeavyAttack.push_back(m_state->getFullAssetPath("HeavyAttack1.png"));
	m_spritesHeavyAttack.push_back(m_state->getFullAssetPath("HeavyAttack2.png"));
	m_spritesHeavyAttack.push_back(m_state->getFullAssetPath("HeavyAttack3.png"));
	m_spritesHeavyAttack.push_back(m_state->getFullAssetPath("HeavyAttack4.png"));
	m_spritesHeavyAttackleft.push_back(m_state->getFullAssetPath("HeavyAttackleft1.png"));
	m_spritesHeavyAttackleft.push_back(m_state->getFullAssetPath("HeavyAttackleft2.png"));
	m_spritesHeavyAttackleft.push_back(m_state->getFullAssetPath("HeavyAttackleft3.png"));
	m_spritesHeavyAttackleft.push_back(m_state->getFullAssetPath("HeavyAttackleft4.png"));
	


	

	


	
		
	

	// Adjust width for finer collision detection
	m_width = playerCollisionWidth;
	m_height = playerCollisionHeight;
}

void Player::debugDraw()
{
	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.3f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.1f, 0);
	debug_brush.fill_opacity = 0.1f;
	debug_brush.outline_opacity = 1.0f;
	graphics::drawRect(m_state->getCanvasWidth()*0.5f, m_state->getCanvasHeight() * 0.5f, m_width, m_height, debug_brush);
	
	char s[20];
	sprintf_s(s,"(%5.2f, %5.2f)", m_pos_x, m_pos_y);
	SETCOLOR(debug_brush.fill_color, 1, 0, 0);
	debug_brush.fill_opacity = 1.0f;
	graphics::drawText(m_state->getCanvasWidth() * 0.5f - 0.4f, m_state->getCanvasHeight() * 0.5f - 0.6f, 0.15f, s, debug_brush);
}


void Player::movePlayer(float dt)
{
	float delta_time = dt / 1000.0f;

	// Stage 2 code: Acceleration-based velocity
	float move = 0.0f;
	if (graphics::getKeyState(graphics::SCANCODE_A))
	{
		move -= 1.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D))
	{
		move += 1.0f;
	}
		
	m_vx = std::min<float>(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);
	m_vx = std::max<float>(-m_max_velocity, m_vx);

	// friction
	m_vx -= 0.2f * m_vx / (0.1f + fabs(m_vx));

	// apply static friction threshold
	if (fabs(m_vx) < 0.01f)
		m_vx = 0.0f;

	// adjust horizontal position
	m_pos_x += m_vx * delta_time;

	// jump only when not in flight:
	std::cout << m_state->getPlayer()->m_vy << std::endl;
	if (m_vy == 0.0f || isCollidingSideways == true)
		m_vy -= (graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f) * 0.02f;// not delta_time!! Burst 
	
	else
	{
		m_vy -= (graphics::getKeyState(graphics::SCANCODE_S) ? m_accel_vertical : 0.0f) * -0.005f; // not delta_time!! Burst 
	}

	// add gravity
	m_vy += delta_time * m_gravity;

	// adjust vertical position
	m_pos_y += m_vy * delta_time;

	
}

