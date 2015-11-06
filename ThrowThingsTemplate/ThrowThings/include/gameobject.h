#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

//VIXEN INCLUDES
#include <vix_glrenderer.h>
#include <vix_rectangle.h>
#include <vix_vector2.h>
#include <map>
#include "animation.h"

using namespace Vixen;

class GameObject
{
	typedef std::map<UString, Animation*> AnimationList;
public:
	GameObject(void);

	~GameObject(void);

	/*SETTERS*/
	void SetTexture(Texture* texture);
	void SetPosition(Vector2 position);
	void SetOrigin(Vector2 origin);
	void SetRotation(float rotation);
	void SetCurrentAnimation(UString name);
	void AddAnimation(UString name, Animation* animation);

	/*GETTERS*/
	const Texture* GetTexture()		const;
	const Vector2& GetPosition()	const;
	const Vector2& GetOrigin()		const;
	const float    GetRotation()	const;
	bool           HasAnimations();
	Rect&    GetBounds();

	/*Updated GameObject (AI, etc.)*/
	virtual void VUpdate(float dt);

	/*Render GameObject*/
	virtual void VRender(GLRenderer* renderer, float dt);

protected:
	Texture*		m_texture;  //GameObject sprite image
	Vector2			m_position; //GameObject 2D screen position (in PIXELS)
	Vector2			m_origin;   //GameObject origin (used for rotation)
	float			m_rotation; //GameObject rotation
	float			m_alpha;    //GameObject alpha
	Rect			m_bounds;
	AnimationList	m_animations;
	UString         m_currentAnimation;
};

#endif