#include "gamescreen.h"

GameScreen::GameScreen(ScreenManager* manager)
{
	m_transition = 0.0f;
	m_manager = manager;
	m_state = ScreenState::OFF;
}

GameScreen::~GameScreen()
{

}

ScreenState GameScreen::GetState() const
{
	return m_state;
}

GameScreen* GameScreen::GetPrev() const
{
	return m_previous;
}

void GameScreen::SetState(ScreenState state)
{
	m_state = state;
}

void GameScreen::SetPrev(GameScreen* screen)
{
	m_previous = screen;
}

void GameScreen::Update(float dt)
{
	switch(m_state)
	{
	case ScreenState::ACTIVE:
		UpdateActive(dt);
		break;

	case ScreenState::TRANSOFF:
		UpdateTransOff(dt);
		break;

	case ScreenState::TRANSON:
		UpdateTransOn(dt);
		break;
	}
}

void GameScreen::Draw(GLRenderer* renderer, float dt)
{
	switch(m_state)
	{
		case ScreenState::ACTIVE:
		DrawActive(renderer, dt);
		break;

	case ScreenState::TRANSOFF:
		DrawTransOff(renderer, dt);
		break;

	case ScreenState::TRANSON:
		DrawTransOn(renderer, dt);
		break;

	case ScreenState::PAUSED:
		DrawPaused(renderer, dt);
		break;
	}
}