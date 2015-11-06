#include "gameplayscreen.h"

#include "screenmanager.h"
#include "Enemy.h"
#include "Brute.h"

#include <vix_stringutil.h>

GamePlayScreen::GamePlayScreen(ScreenManager* manager)
	: GameScreen(manager)
{
	m_level = 'g';
	/*LOAD ALL CONTENT*/
	loadContent();

	/*INIT GAME*/
	initGame();
}

void GamePlayScreen::loadContent()
{
	m_levelFile = NULL;
	m_font = m_manager->ContentManager()->LoadFont(VTEXT("Consolas_24.fnt"));
	m_bigFont = m_manager->ContentManager()->LoadFont(VTEXT("Consolas_36.fnt"));
	m_gymTexture = m_manager->ContentManager()->LoadTexture(VTEXT("Court.png"));
	m_gymOverlay = m_manager->ContentManager()->LoadTexture(VTEXT("Court_Lights2.png"));
	m_lobbyTexture = m_manager->ContentManager()->LoadTexture(VTEXT("Lobby.png"));
	m_lobbyOverlay = m_manager->ContentManager()->LoadTexture(VTEXT("Court_Lights.png"));
	m_zombieTexture = m_manager->ContentManager()->LoadTexture(VTEXT("zombie_32_rot.png"));
	m_bruteTexture = m_manager->ContentManager()->LoadTexture(VTEXT("zombie_32_rot_pink.png"));
	m_playerTexture = m_manager->ContentManager()->LoadTexture(VTEXT("player.png"));
	m_splatTexture = m_manager->ContentManager()->LoadTexture(VTEXT("splat.png"));
	m_rockTexture = m_manager->ContentManager()->LoadTexture(VTEXT("rock.png"));
	m_dodgeballTexture = m_manager->ContentManager()->LoadTexture(VTEXT("dodgeball.png"));
	m_ninjaStarTexture = m_manager->ContentManager()->LoadTexture(VTEXT("ninja_star.png"));
	m_barInner = m_manager->ContentManager()->LoadTexture(VTEXT("bar_inner.png"));
	m_barOutter = m_manager->ContentManager()->LoadTexture(VTEXT("bar_outer.png"));
	m_heartTexture = m_manager->ContentManager()->LoadTexture(VTEXT("heart.png"));
	m_crosshairTexture = m_manager->ContentManager()->LoadTexture(VTEXT("crosshair.png"));
}

void GamePlayScreen::initGame()
{
	cleanup();

	/*INITIALIZE PLAYER*/
	m_player = Player();
	m_player.SetPosition(Vector2(50,50));
	m_player.SetOrigin(Vector2(16, 16));
	m_player.SetTexture(m_playerTexture);
	m_killed = 0;
	m_gameWinAlpha = 0.0f;
	m_won = false;
	m_loss = false;

	// set up enemies
	Enemy* enemy1 = new Enemy("", 1, 75, m_player, m_splatTexture);
	for(int i = 0; i < 7; i++)
	{
		int rX = rand() % 800;
		int rY = rand() % 600;
		enemy1->SetPosition(Vector2(rX + 100, rY));
		enemy1->SetTexture(m_zombieTexture);
		enemy1->SetOrigin(Vector2(16, 16));
		enemy1->AddAnimation(VTEXT("Zombie"), new Animation(0, 0, 32, 8, 1, false));
		enemy1->AddAnimation(VTEXT("Splat"), new Animation(0, 0, 42, 13, 1, true));
		enemy1->SetCurrentAnimation(VTEXT("Zombie"));
		m_enemies.push_back(enemy1);
		enemy1 = new Enemy("", 1, 75, m_player, m_splatTexture);
	}

	for(int i = 0; i < 2; i++)
	{
		Brute* brute1 = new Brute(m_player, m_splatTexture);
		
		int rX = rand() % 800;
		int rY = rand() % 600;
		brute1->SetPosition(Vector2(rX + 100, rY));
		brute1->SetTexture(m_bruteTexture);
		brute1->SetOrigin(Vector2(16, 16));
		brute1->AddAnimation(VTEXT("Zombie"), new Animation(0, 0, 32, 8, 1, false));
		brute1->AddAnimation(VTEXT("Splat"), new Animation(0, 0, 42, 13, 1, true));
		brute1->SetCurrentAnimation(VTEXT("Zombie"));
		m_enemies.push_back(brute1);
	}
	/*string line;
	ifstream levFile;*/
	Item* item;
	Item* item2;
	Item* item3;
	Item* item4;
	Item* item5;
	switch(m_level){		

	case 'l':
		fopen_s(&m_levelFile, "Lobby.txt", "rb");
		break;
	case 'g':
		fopen_s(&m_levelFile, "Gym.txt", "rb");
		break;
	default:
		break;
	}

	if(m_levelFile) {
	char line[1024];
		while(fgets(line, sizeof(line), m_levelFile) != NULL) {
			UConverter cv;
			UString cv_line = cv.from_bytes(line);
			std::vector<int> values = Vixen::parse<int>(cv_line, VTEXT(','));
			int cVal = values[0];
			int x = values[1];
			int y = values[2];
			Item* rock = NULL;
			Item* dodgeball = NULL;
			Item* block = NULL;
			switch(cVal)
			{
			case 101:
				rock = new Item("Rock", 1.0, 1.0, 1.0);
				rock->SetTexture(m_rockTexture);
				rock->SetPosition(Vector2(x,y));
				rock->SetOrigin(Vector2(16, 16));
				m_items.push_back(rock);
				break;

			case 102:
				dodgeball = new Item("Dodgeball", 1.0, 1.0, 1.0);
				dodgeball->SetTexture(m_dodgeballTexture);
				dodgeball->SetPosition(Vector2(x,y));
				dodgeball->SetOrigin(Vector2(16, 16));
				m_items.push_back(dodgeball);
				break;
			case 103:
				block = new Item("Block",1.0,1.0,1.0);
				block->SetTexture(m_ninjaStarTexture);
				block->SetPosition(Vector2(x,y));
				block->SetOrigin(Vector2(16, 16));
				block->SetIsScenery(true);
				m_items.push_back(block);
				break;
			}
		}
		fclose(m_levelFile);
	}
}

void GamePlayScreen::cleanup()
{
	for(int i = 0; i < m_enemies.size(); i++)
	{
		Enemy* enemy = m_enemies[i];
		delete enemy;
		m_enemies.erase(m_enemies.begin() + i); //in case I want to add logic
	}

	for(int i = 0; i < m_items.size(); i++)
	{
		Item* item = m_items[i];
		delete item;
		m_items.erase(m_items.begin() + i); //in case I want to add logic
	}

	m_enemies.clear();
	m_items.clear();
}

void GamePlayScreen::UpdateActive(float dt)
{
	for(Enemy*& e : m_enemies)
	{
		e->VUpdate(dt);
		if(e->IsAlive()) {
			e->seekPlayer(m_player);

			/*HANDLE COLLISION WITH PLAYER*/
			if(e->GetBounds().Intersects(m_player.GetBounds()) && m_player.GetHP() > 0)
			{
				if(!m_player.IsImmune())
					m_player.TakeDamage();
				if(m_player.GetHP() == 0) {
					m_player.Die();
				}
			}

			/*HANDLE COLLISION WITH THROWN ITEMS*/
			Item* thrownItem = m_player.GetLastThrownItem();
			if(thrownItem) {
				if(thrownItem->GetInAir()) {
					if(e->GetBounds().Intersects(thrownItem->GetBounds())){
						thrownItem->stop();
						e->takeDamage(1);

						if(e->GetHealth() <= 0) {
							e->explode();
							m_killed++;
						}
					}
				}
			}
		}
		
	}

	for(Item*& item : m_items) {
		item->VUpdate(dt);
		Rect r = m_player.GetBounds();
		Rect t = item->GetBounds();
		if(item->GetActive()) {
			if(r.Intersects(t)) {
				if(item->GetIsScenery()){
					m_player.Stop(dt);
				}
				else if(item->GetOnGround()) {
					if(!m_player.HasItem()) {
						USStream ss;
						ss << "Picked up: " << item->GetName();
						DebugPrintF(ss.str().c_str());
						m_player.PickUpItem(item);
					}
				}
			}
		}
	}

	m_player.VUpdate(dt);
	m_player.VHandleInput(m_manager->Keyboard(), m_manager->Mouse(), dt);

	if(m_killed >= m_enemies.size()) {
		//WE DEFEATED EVERY ENEMY!!
		m_won = true;
	}

	if(m_player.GetHP() <= 0){
		//WE DIED
		m_loss = true;
	}

	if(m_won || m_loss) {
		m_gameWinAlpha += dt;
		if(m_gameWinAlpha >= 2.0f) {
			if(m_level=='g') {m_level='l';}
			if(m_loss)
			{
				if(m_level == 'l') m_level = 'g';
			}
			initGame();
		}
	}
}

void GamePlayScreen::UpdateTransOn(float dt)
{
	m_transition += dt;
	if(m_transition >= 1) {
		m_state = ScreenState::ACTIVE;
	}
	
}

void GamePlayScreen::UpdateTransOff(float dt)
{

}

void GamePlayScreen::DrawActive(GLRenderer* renderer, float dt)
{
	/*GAMEPLAY RENDERING*/
	if(m_level == 'g')
		renderer->Render2DTexture((GLTexture*)m_gymTexture, Vector2::Zero, Rect::EMPTY, Vector2::Zero, Vector2::Unit, 0.0f, 1.0f, Colors::White, 0.0f);
	else
		renderer->Render2DTexture((GLTexture*)m_lobbyTexture, Vector2::Zero, Rect::EMPTY, Vector2::Zero, Vector2::Unit, 0.0f, 1.0f, Colors::White, 0.0f);

	for(Enemy*& e : m_enemies)
		e->VRender(renderer, dt);
	for(Item*& item : m_items)
		item->VRender(renderer, dt);
	m_player.VRender(renderer, dt);
	if(m_level == 'g')
		renderer->Render2DTexture((GLTexture*)m_gymOverlay, Vector2::Zero, Rect::EMPTY, Vector2::Zero, Vector2::Unit, 0.0f, 1.0f, Colors::White, 0.0f);
	else
		renderer->Render2DTexture((GLTexture*)m_lobbyOverlay, Vector2::Zero, Rect::EMPTY, Vector2::Zero, Vector2::Unit, 0.0f, 1.0f, Colors::White, 0.0f);
	

	/*USER INTERFACE RENDERING*/
	renderer->Render2DTexture((GLTexture*)m_barOutter, Vector2(20, 720 - 80),
		Rect::EMPTY, Vector2::Zero, Vector2::Unit, 0.0f, 1.0f, Colors::White, 0.0f);
	renderer->Render2DTexture((GLTexture*)m_barInner, Vector2(20, 720 - 80),
		Rect(0, 0, (m_player.GetThrowPower() / 1.0f) * 256.0f, 32), Vector2::Zero, Vector2::Unit, 0.0f, 1.0f, Colors::Green, 0.0f);

	for(int i = 0; i < m_player.GetHP(); i++)
		renderer->Render2DTexture((GLTexture*)m_heartTexture, Vector2(20 + i*32, 720 - 115),
			Rect::EMPTY, Vector2::Zero, Vector2::Unit, 0.0f, 1.0f, Colors::White, 0.0f);
	USStream ss;
	/*ss << VTEXT("Killed: ") << m_killed;
		renderer->Render2DText(m_font, ss.str(), Vector2(20, 100), 1.0f, Vixen::Colors::Purple);*/
	renderer->Render2DTexture((GLTexture*)m_crosshairTexture, Vector2(m_manager->Mouse()->X(), m_manager->Mouse()->Y()),
			Rect::EMPTY, Vector2::Zero, Vector2::Unit, 0.0f, 1.0f, Colors::White, 0.0f);

	if(m_won) {
		UString text = VTEXT("GAME WIN!");
		renderer->Render2DText(m_bigFont, text, Vector2(-1, -1), m_gameWinAlpha, Vixen::Colors::Goldenrod);
	}
	if(m_loss) {
		UString text = VTEXT("GAME LOSS...");
		renderer->Render2DText(m_bigFont, text, Vector2(-1, -1), m_gameWinAlpha, Vixen::Colors::Maroon);
	}
}

void GamePlayScreen::DrawPaused(GLRenderer* renderer, float dt)
{
	renderer->Render2DText(m_font, VTEXT("PAUSED"), m_position, m_transition, Vixen::Colors::Green);

}

void GamePlayScreen::DrawTransOn(GLRenderer* renderer, float dt)
{
	
}

void GamePlayScreen::DrawTransOff(GLRenderer* renderer, float dt)
{
	renderer->Render2DText(m_font, VTEXT("TRANSOFF"), m_position, m_transition, Vixen::Colors::Green);
}