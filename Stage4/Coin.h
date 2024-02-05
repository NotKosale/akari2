#pragma once

#include <sgg/graphics.h>
#include "box.h"
#include "gameobject.h"
#include "gamestate.h"

class Coin : public Box, public GameObject
{
	std::vector<std::string> m_sprites;

	graphics::Brush m_brush_coin;
	;
	
	
public:

	float x;
	float y;
	float desiredX;
	float desiredY;

public:
	enum itemType   // edw pernaw to type tou coin ws COIN, opote ka8e fora pou 8elw na kanw instantiate ena coin, 8a to kanw me to itemType::COIN
	{
		COIN
	};


	itemType m_coinAnimationState;

	Coin(std::string name, float x, float y);
	void update(float dt) override;
	void draw(float x, float y, float w, float h);
	void init();
	bool isCollected() const;
	void collect();	// this method indicates if the coi is collected	
public:
	
	float animationtime = 0.0f;
	std::vector<std::string> m_allCoinSprites;
	Coin(std::string name) : GameObject(name) {}

private:
	bool collected;// indicates if the coin is collected
	float size;// size of the coin
	itemType itemType;
};
