#include "gameobject.h"

GameObject::GameObject(void)
{
	m_texture = nullptr;
	m_position = Vector2::Zero;
	m_origin = Vector2::Zero;
	m_rotation = 0.0f;
	m_bounds = Rect::EMPTY;
	m_alpha = 1.0f;
}

GameObject::~GameObject(void)
{

}

void GameObject::VUpdate(float dt)
{
	if(HasAnimations()) {
		Animation* animation = m_animations[m_currentAnimation];
		animation->Update(dt);
	}
}

void GameObject::VRender(GLRenderer* renderer, float dt)
{
	if(m_texture) {
		if(HasAnimations()) {
			Animation* animation = m_animations[m_currentAnimation];
			renderer->Render2DTexture((GLTexture*)m_texture, m_position, animation->GetSourceRect(), m_origin, Vector2::Unit,
			m_rotation, m_alpha, Colors::White, 0.0f);
		}
		else
			renderer->Render2DTexture((GLTexture*)m_texture, m_position, Rect::EMPTY, m_origin, Vector2::Unit,
			m_rotation, m_alpha, Colors::White, 0.0f);
	}
}

/*SETTERS*/

void GameObject::SetTexture(Texture* texture)
{
	m_texture = texture;
	if(HasAnimations()) {
		Animation* anim = m_animations[m_currentAnimation];
		m_bounds = Rect(m_position.x, m_position.y, 32, 32);
	}
	else
		m_bounds = Rect(m_position.x, m_position.y, 32, 32);
	
}

void GameObject::SetPosition(Vector2 position)
{
	m_position = position;
	m_bounds.x = m_position.x;
	m_bounds.y = m_position.y;
}

void GameObject::SetOrigin(Vector2 origin)
{
	m_origin = origin;
}

void GameObject::SetRotation(float rotation)
{
	m_rotation = rotation;
}

void GameObject::SetCurrentAnimation(UString name)
{
	m_currentAnimation = name;
}

void GameObject::AddAnimation(UString name, Animation* animation)
{
	m_animations[name] = animation;
	if(m_currentAnimation.empty()) //set current if not already set
		m_currentAnimation = name;
}

/*GETTERS*/

const Texture* GameObject::GetTexture() const
{
	return m_texture;
}

const Vector2& GameObject::GetPosition() const
{
	return m_position;
}

const Vector2& GameObject::GetOrigin() const
{
	return m_origin;
}

const float GameObject::GetRotation() const
{
	return m_rotation;
}

Rect& GameObject::GetBounds()
{
	return m_bounds;
}

bool GameObject::HasAnimations()
{
	return m_animations.size() > 0;
}


