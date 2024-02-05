#include "Coin.h"
#include "util.h"
#include "gamestate.h"
#include "gameobject.h"

Coin::Coin(std::string name, float x, float y) : GameObject(name), collected(false)
{
	// edw kanei to initial position of the coin	
	
}

void Coin::update(float dt)
{
	float delta_time = dt / 1000.0f;
	GameObject::update(dt);
}

void Coin::draw(float x, float y , float w , float h) {
	animationtime += 0.04f;
	if (!collected) {
		int sprite = (int)fmod(animationtime, m_allCoinSprites.size());
		m_brush_coin.texture = m_allCoinSprites[sprite];
		m_brush_coin.outline_opacity = 0.0f;
		graphics::drawRect(x, y, w, h, m_brush_coin); // Set outline parameter to false
	}
}

void Coin::init() {

	m_allCoinSprites.push_back(m_state->getFullAssetPath("kunai1.png"));
	m_allCoinSprites.push_back(m_state->getFullAssetPath("kunai2.png"));
	m_allCoinSprites.push_back(m_state->getFullAssetPath("kunai3.png"));
	m_allCoinSprites.push_back(m_state->getFullAssetPath("kunai4.png"));
	m_allCoinSprites.push_back(m_state->getFullAssetPath("kunai5.png"));
}

