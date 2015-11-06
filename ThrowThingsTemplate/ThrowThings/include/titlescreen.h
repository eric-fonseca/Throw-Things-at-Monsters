#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "gamescreen.h"


class ScreenManager;

class TitleScreen : public GameScreen
{
public:
	TitleScreen(ScreenManager* manager);

	void UpdateActive(float dt) override;
	void UpdateTransOn(float dt) override;
	void UpdateTransOff(float dt) override;

	void DrawActive(GLRenderer* renderer, float dt) override;
	void DrawPaused(GLRenderer* renderer, float dt) override;
	void DrawTransOn(GLRenderer* renderer, float dt) override;
	void DrawTransOff(GLRenderer* renderer, float dt) override;
	
private:
	float	m_time;
	Vector2 m_position;
	Vector2 m_startOptionPos;
	BMFont* m_titleFont;
	UString m_title;
	UString m_startGame;
	Color   m_color;
};

#endif