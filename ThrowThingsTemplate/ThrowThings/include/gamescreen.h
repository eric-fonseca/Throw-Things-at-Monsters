#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <vix_texture.h>
#include <vix_glrenderer.h>

using namespace Vixen;

enum class ScreenState
{
	OFF,
	ACTIVE,
	PAUSED,
	TRANSON,
	TRANSOFF
};

class ScreenManager;

class GameScreen
{
public:
	GameScreen(ScreenManager* manager);

	virtual ~GameScreen();

	/*GETTERS*/
	ScreenState			  GetState() const;
	GameScreen*           GetPrev()  const;

	/*SETTERS*/
	void SetState(ScreenState state);
	void SetPrev(GameScreen* screen);


	/*UPDATE FUNCTIONS*/
	virtual void UpdateActive(float dt) = 0;
	virtual void UpdateTransOn(float dt) = 0;
	virtual void UpdateTransOff(float dt) = 0;
	void Update(float dt);

	/*RENDER FUNCTIONS*/
	virtual void DrawPaused(GLRenderer* renderer, float dt) = 0;
	virtual void DrawActive(GLRenderer* renderer, float dt) = 0;
	virtual void DrawTransOn(GLRenderer* renderer, float dt) = 0;
	virtual void DrawTransOff(GLRenderer* renderer, float dt) = 0;
	void Draw(GLRenderer* renderer, float dt);

protected:
	ScreenState     m_state;
	ScreenManager*  m_manager;
	Texture*        m_texture;
	GameScreen*     m_previous;
	float           m_transition;
};

#endif