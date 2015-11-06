#ifndef ANIMATION_H
#define ANIMATION_H

#include <vix_rectangle.h>

using namespace Vixen;

class Animation
{
public:
	Animation(int startX, int startY, int frameSize, int numFrames, float duration, bool oneshot);


	/*GETTERS*/
	int		GetCurrentFrameIndex();
	int		GetPlayCount();
	Rect	GetSourceRect();

	void Update(float dt);

private:
	int		m_curFrameIndex;
	int		m_numFrames;
	int     m_frameSize;
	int		m_timeSinceLastFrame;
	int		m_millisecondsPerFrame;
	int		m_currentFrameX;
	int		m_currentFrameY;
	int		m_playCount;
	float	m_duration;
	float   m_elapsed;
	bool    m_isOneShot;
};

#endif