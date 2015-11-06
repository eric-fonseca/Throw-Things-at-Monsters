#include "animation.h"

Animation::Animation(int startX, int startY, int frameSize, int numFrames, float duration, bool oneshot)
{
	m_currentFrameX = startX;
	m_currentFrameY = startY;
	m_curFrameIndex = 0;
	m_numFrames = numFrames;
	m_duration = duration;
	m_frameSize = frameSize;
	m_isOneShot = oneshot;
	m_playCount = 0;
	m_elapsed = 0.0f;
}

Vixen::Rect Animation::GetSourceRect()
{
	int x = m_currentFrameX + (m_frameSize * m_curFrameIndex);
	int y = m_currentFrameY;
	return Vixen::Rect(x, y, m_frameSize, m_frameSize);
}

int Animation::GetCurrentFrameIndex()
{
	return m_curFrameIndex;
}

int Animation::GetPlayCount()
{
	return m_playCount;
}

void Animation::Update(float dt)
{
	
	m_elapsed += dt;
	if(m_elapsed > m_duration / static_cast<float>(m_numFrames)) {
		m_elapsed = 0.0f;

		if(m_isOneShot && m_playCount >= 1) {

		}
		else
			m_curFrameIndex = (m_curFrameIndex + 1) % m_numFrames;
		
		if(m_curFrameIndex == m_numFrames-1)
			m_playCount++;

	}
}