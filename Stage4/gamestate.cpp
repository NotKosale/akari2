#include "gamestate.h"
#include "level.h"
#include "player.h"
#include "coin.h"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

GameState::GameState()// constructor
{
	//m_asset_path = ASSET_PATH;
}


GameState::~GameState()// destructor tsekarei an yparxei current level kai an yparxei tote to katastrefei
{
	if (m_current_level)
		delete m_current_level;
}

GameState* GameState::getInstance()// singleton design pattern mono ena instance tou gamestate dhmiourgeitai
{
	if (!m_unique_instance)
	{
		m_unique_instance = new GameState();
	}
	return m_unique_instance;
}


bool GameState::init()
    {
        m_current_level = new Level("1.lvl");
        m_current_level->init();
        
        m_player = new Player("Player");
        m_player->init();

		m_coin = new Coin("Coin");
		m_coin->init();

	
		
   

        graphics::preloadBitmaps(getAssetDir());
        graphics::setFont(m_asset_path + "OpenSans-Regular.ttf");

        m_current_level->init();

        return true;
    }
	

	



	

	
	


void GameState::draw()// edw ginetai h emfanish tou current level kai tou player(o player emfanizetai panw apo to level)
{
	if (!m_current_level)
		return;

	m_current_level->draw();
	
	
}

void GameState::update(float dt)// edw ginetai h kinhsh tou current level kai tou player

{
	// Skip an update if a long delay is detected 
	// to avoid messing up the collision simulation
	if (dt > 500) // ms
		return;
	
	// Avoid too quick updates
	float sleep_time = std::max(17.0f - dt, 0.0f);
	if (sleep_time > 0.0f)
	{
		std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));// edw ginetai sleep to thread dhladh perimenei 17ms gia na ginei h epomenh kinhsh
	}

	if (!m_current_level)
		return;

	m_current_level->update(dt);// edw ginetai h kinhsh tou current level

	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);// elegxetai an to 0 exei paththei gia na emfanistei to debug mode

	
	

}

std::string GameState::getFullAssetPath(const std::string& asset)// epistrefei to asset path dhladh to path tou asset pou theloume na emfanisoume
{
	return m_asset_path + asset;
}

std::string GameState::getAssetDir()// epistrefei to asset path tou gamestate dhladh to path tou gamestate
{
	return m_asset_path;
}

GameState* GameState::m_unique_instance = nullptr;// arxikopoieitai to unique instance tou gamestate