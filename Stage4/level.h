#pragma once

#include "gameobject.h"
#include <vector>
#include <list>
#include <string>
#include <sgg/graphics.h>
#include "player.h"

class Level : public GameObject
{
	graphics::Brush m_brush_background;
	graphics::Brush m_brush_kunai;

	std::vector<GameObject*> m_static_objects;
	std::list<GameObject*> m_dynamic_objects;

	// add some collidable blocks
	std::vector<Box> m_blocks;
	std::vector<Box> m_blocks_no_collide;
	std::vector<Box> m_blocks_no_items;
	std::vector<Box> m_blocks_coin1;
	std::vector<Box> m_blocks_coin2;
	std::vector<Box> m_blocks_coin3;
	std::vector<Box> m_attack;
	std::vector<std::string> m_block_names;
	std::vector<std::string> m_block_no_names;
	std::vector<std::string> m_block_items;
	const float m_block_size = 0.5f;
	graphics::Brush m_block_brush_no;
	graphics::Brush m_block_brush;
	graphics::Brush m_block_brush_debug;

	float m_center_x = 5.0f;
	float m_center_y = 5.0f;

	bool coincollected1;
	bool coincollected2;
	bool coincollected3;
	float collectedcoins = 0;

	// dedicated method to draw a block
	void drawBlock(int i);

	void drawNonCollidingBlock(int i);

	void drawItems(int i);

	void drawCoin1();
	void drawCoin2();
	void drawCoin3();
	void drawAttack();

	// detect collisions
	void checkCollisions();

public:
	void update(float dt) override;
	void draw() override;
	void init() override;

	Level(const std::string& name = "Level0");
	~Level() override;
};