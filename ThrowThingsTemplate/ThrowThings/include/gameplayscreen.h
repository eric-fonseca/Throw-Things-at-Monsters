#ifndef GAMEPLAYSCREEN_H
#define GAMEPLAYSCREEN_H
#include <fstream>
#include <string>
#include "gamescreen.h"
#include "gameobject.h"
#include "player.h"
#include "Enemy.h"
#include "Item.h"
#include "ItemManager.h"

class ScreenManager;

class GamePlayScreen : public GameScreen
{
	typedef std::vector<Item*>  ItemList;
	typedef std::vector<Enemy*> EnemyList;
public:
	GamePlayScreen(ScreenManager* manager);

	void UpdateActive(float dt) override;
	void UpdateTransOn(float dt) override;
	void UpdateTransOff(float dt) override;

	void DrawActive(GLRenderer* renderer, float dt) override;
	void DrawPaused(GLRenderer* renderer, float dt) override;
	void DrawTransOn(GLRenderer* renderer, float dt) override;
	void DrawTransOff(GLRenderer* renderer, float dt) override;

private:
	void loadContent();
	void initGame();
	void cleanup();

private:
	/*INTERFACE MEMBERS*/
	BMFont*		m_font;
	BMFont*     m_bigFont;
	Texture*	m_gymTexture;
	Texture*    m_gymOverlay;
	Texture*	m_lobbyTexture;
	Texture*    m_lobbyOverlay;
	Texture*    m_barInner;
	Texture*    m_barOutter;
	Texture*    m_heartTexture;
	Texture*    m_crosshairTexture;

	/*GAMEPLAY MEMBERS*/
	Texture*    m_zombieTexture;
	Texture*    m_bruteTexture;
	Texture*    m_playerTexture;
	Texture*    m_rockTexture;
	Texture*	m_dodgeballTexture;
	Texture*    m_ninjaStarTexture;
	Texture*    m_splatTexture;
	Vector2		m_position;
	Enemy*		m_zombieGO;
	Player      m_player;
	EnemyList   m_enemies;
	ItemList    m_items;
	ItemManager* itemManage;

	int         m_killed;
	bool        m_won;
	bool        m_loss;
	float       m_gameWinAlpha;
	float       m_elapsed;
	char        m_level; //l=lobby, g=gym
	FILE*       m_levelFile;
};

#endif