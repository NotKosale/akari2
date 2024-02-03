#include "Coin.h"
#include "util.h"
#include "gamestate.h"
#include "gameobject.h"

Coin::Coin(std::string name, float x, float y) : GameObject(name), collected(false)
{
	// edw kanei to initial position of the coin	
	int bitmapHeight = 100;
	float layerHeight = 0.5f;
	float desiredX = 15.0f;
	float desiredY = static_cast<float>(bitmapHeight - 90) * layerHeight - m_height / 2.0f;
}

void Coin::update(float dt)
{
	float delta_time = dt / 1000.0f;
	GameObject::update(dt);
}

void Coin::draw(float x, float y , float w , float h) {
	animationtime += 0.15f;
	if (!collected) {
		
		
			int sprite = (int)fmod(animationtime, m_allCoinSprites.size());
			m_brush_coin.texture = m_allCoinSprites[sprite];
			graphics::drawRect(x, y, w, h, m_brush_coin);
		
	}
}

void Coin::init() {

	m_allCoinSprites.push_back(m_state->getFullAssetPath("Gold_1.png"));
	m_allCoinSprites.push_back(m_state->getFullAssetPath("Gold_2.png"));
	m_allCoinSprites.push_back(m_state->getFullAssetPath("Gold_3.png"));
	m_allCoinSprites.push_back(m_state->getFullAssetPath("Gold_4.png"));
	m_allCoinSprites.push_back(m_state->getFullAssetPath("Gold_5.png"));
	m_allCoinSprites.push_back(m_state->getFullAssetPath("Gold_6.png"));
	m_allCoinSprites.push_back(m_state->getFullAssetPath("Gold_7.png"));
	m_allCoinSprites.push_back(m_state->getFullAssetPath("Gold_8.png"));
	m_allCoinSprites.push_back(m_state->getFullAssetPath("Gold_9.png"));
	m_allCoinSprites.push_back(m_state->getFullAssetPath("Gold_10.png"));


}

bool Coin::isCollected() const {  // Returns true if the coin has been collected	
	return collected;
}

void Coin::collect() {  // Sets the coin as collected
	collected = true;
}	    