#include "Enemy.h"

Enemy::Enemy() : GameObject()
{
	name = "";
	health = 1;
	alive = true;
	velocity = Vector2::Zero;
	acceleration = Vector2::Zero;
	maxForce = 400.0f;
	maxSpeed = 200.0f;
	shouldRemove = false;
}

Enemy::Enemy(string enemyName, int enemyHealth, int enemySpeed, Player target, Texture* deadTex) : GameObject()
{
	name = enemyName;
	health = enemyHealth;
	speed = enemySpeed;
	deadTexture = deadTex;
	alive = true;
	velocity = Vector2::Zero;
	acceleration = Vector2::Zero;
	maxForce = 400.0f;
	maxSpeed = 200.0f;
	shouldRemove = false;
	seekPlayer(target);
}

Enemy::~Enemy(void)
{
}

Vector2 Enemy::GetVelocity()
{
	return velocity;
}

float Enemy::GetMaxForce()
{
	return maxForce;
}

int Enemy::GetHealth()
{
	return health;
}

bool Enemy::ShouldRemove()
{
	return shouldRemove;
}

void Enemy::takeDamage(int dmg)
{
	health -= dmg;
}

void Enemy::explode()
{
	alive = false;
	SetCurrentAnimation(VTEXT("Splat"));
}

void Enemy::revive()
{
	alive = true;
	m_alpha = 1.0f;
}

const bool Enemy::IsAlive() const
{
	return alive;
}

void Enemy::VUpdate(float dt)
{
	if(alive)
	{
		m_position += velocity * Vector2(cos(m_rotation*0.0174532925f), sin(m_rotation*0.0174532925f)) * dt * speed;
	} else {
		if(m_animations[m_currentAnimation]->GetPlayCount() >= 1)
			shouldRemove = true;
	}

	m_bounds.x = m_position.x;
	m_bounds.y = m_position.y;

	GameObject::VUpdate(dt);
}

void Enemy::VRender(GLRenderer* renderer, float dt)
{
	if(alive)
		GameObject::VRender(renderer, dt);
	else {
		Animation* splatAnim = m_animations[m_currentAnimation];
		renderer->Render2DTexture((GLTexture*)deadTexture, m_position, splatAnim->GetSourceRect(), m_origin, Vector2::Unit,
		m_rotation, m_alpha, Colors::White, 0.0f);
	}
}

void Enemy::seekPlayer(Player target)
{
	velocity.x = 1.0;
	velocity.y = 1.0;
	
	float dx = target.GetPosition().x - m_position.x;
	float dy = target.GetPosition().y - m_position.y;

	m_rotation = atan2(dy, dx) * (180 / PI);
}