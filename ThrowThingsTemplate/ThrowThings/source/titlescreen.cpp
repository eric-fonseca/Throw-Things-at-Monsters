#include "titlescreen.h"
#include "screenmanager.h"
#include "mathutil.h"

TitleScreen::TitleScreen(ScreenManager* manager)
	: GameScreen(manager)
{
	m_time = 0.0f;
	m_position = Vector2(20, 200);
	m_startOptionPos = Vector2(100, 300);
	m_titleFont = manager->ContentManager()->LoadFont(VTEXT("sigmar_one.fnt"));
	m_title = VTEXT("Throw Things at Monsters");
	m_startGame = VTEXT("Start Game");
	m_color = Colors::White;
}

void TitleScreen::UpdateActive(float dt)
{
	
	Rect bounds = m_titleFont->Bounds(m_startGame);
	Rect textB = Rect(m_startOptionPos.x,m_startOptionPos.y, bounds.w, bounds.h);
	if(textB.Contains(m_manager->Mouse()->X(), m_manager->Mouse()->Y())) {
		m_color = Colors::Green;
		if(m_manager->Mouse()->SingleButtonPress(MOUSECS_LEFT)) {
			m_manager->Window()->VToggleCursor();
			m_manager->OpenNextScreen(this, m_manager->GetGamePlayScreen());
		}
	} else {
		m_color = Colors::White;
	}
}

void TitleScreen::UpdateTransOn(float dt)
{
	m_transition += dt;
	if(m_transition >= 3) {
		m_state = ScreenState::ACTIVE;
	}
	Rect bounds = m_titleFont->Bounds(m_title);
	Rect bounds2 = m_titleFont->Bounds(m_startGame);
	float x = (1280 - bounds.w)/2;
	float x2 = (1280 - bounds2.w)/2;
	m_position = LerpVec(m_position, Vector2(x, 200), dt);
	m_startOptionPos = LerpVec(m_startOptionPos, Vector2(x2, 300), dt);
}

void TitleScreen::UpdateTransOff(float dt)
{
	m_transition -= dt;
	if(m_transition <= 0.0f)
		m_state = ScreenState::OFF;
	/*m_position = LerpVec(m_position, Vector2(-500, 200), dt);
	m_startOptionPos = LerpVec(m_startOptionPos, Vector2(-200, 300), dt*50);*/
}

void TitleScreen::DrawActive(GLRenderer* renderer, float dt)
{
	renderer->Render2DText(m_titleFont, m_title, m_position, m_transition, Vixen::Colors::White);
	renderer->Render2DText(m_titleFont, m_startGame, m_startOptionPos, m_transition, m_color);

}

void TitleScreen::DrawPaused(GLRenderer* renderer, float dt)
{
	renderer->Render2DText(m_titleFont, VTEXT("PAUSED"), m_position, m_transition, Vixen::Colors::Red);

}

void TitleScreen::DrawTransOn(GLRenderer* renderer, float dt)
{
	renderer->Render2DText(m_titleFont, m_title, m_position, m_transition, Vixen::Colors::White);
	renderer->Render2DText(m_titleFont, m_startGame, m_startOptionPos, m_transition, Vixen::Colors::White);

}

void TitleScreen::DrawTransOff(GLRenderer* renderer, float dt)
{
	//renderer->Render2DText(m_titleFont, VTEXT("TRANSOFF"), m_position, m_transition, Vixen::Colors::Red);
	//renderer->Render2DText(m_titleFont, m_title, m_position, m_transition, Vixen::Colors::White);
	//renderer->Render2DText(m_titleFont, m_startGame, m_startOptionPos, m_transition, Vixen::Colors::White);
}