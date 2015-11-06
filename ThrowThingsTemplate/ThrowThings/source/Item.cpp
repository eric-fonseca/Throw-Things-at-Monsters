#include "Item.h"
#include "player.h"

Item::Item(void)
{
}
Item::Item(char* n, float w, float s, float d)
{
	name = n;
	weight = w;
	speed = s;
	damage = d;
	active = true;
	onGround = true;
	inAir = false;
	isScenery = false;
	velocity = Vector2::Unit;
	acceleration = Vector2(-.01, -.01);
}

Item::~Item(void)
{
}
//Setters
void Item::SetName(char* n){
	name = n;
}
void Item::SetWeight(float w){
	weight = w;
}
void Item::SetSpeed(float s){
	speed = s;
}
void Item::SetDamage(float d){
	damage = d;
}
void Item::SetOwner(GameObject* g){
	owner = g;
}
void Item::SetActive(bool a){
	active = a;
}

void Item::SetOnGround(bool og) {
	onGround = og;
}
void Item::SetIsScenery(bool s) {
	isScenery = s;
}
void Item::SetDirection(float dir) {
	direction = dir;
}

void Item::SetOwned(bool ow) {
	owned = ow;
}

void Item::SetInAir(bool ia) {
	inAir = ia;
}

//Getters
const char* Item::GetName() const{
	return name;
}
const float Item::GetWeight() const{
	return weight;
}
const float Item::GetSpeed() const{
	return speed;
}
const float Item::GetDamage() const{
	return damage;
}
const GameObject* Item::GetOwner() const{
	return owner;
}
const bool Item::GetActive() const{
	return active;
}

const bool Item::GetOnGround() const {
	return onGround;
}

const float Item::GetDirection() const {
	return direction;
}

const bool Item::GetInAir() const {
	return inAir;
}

const bool Item::GetOwned() const {
	return owned;
}
const bool Item::GetIsScenery() const{
	return isScenery;
}

//Special functions
void Item::PickUp(GameObject* o){
	//method called when the player steps on an item that is just sitting in the world
	//set owner to have this item
	//set this item to have this owner
	//set active to false(so we don't draw it while the player holds it)
}
void Item::ThrowItem(){
	//function called whenever the owning player throws it
}
void Item::DestroyItem(){
	//function called when the item needs to be destructed
}

void Item::stop()
{   // function called when colliding with an enemy or after full throw distance
	inAir = false;
	onGround = true;
	velocity = Vector2::Unit;
}

void Item::VUpdate(float dt)
{
	if(!active)
		return;

	Vector2 angleDir = Vector2(cos(direction*0.0174532925), sin(direction*0.0174532925));

	if(inAir)
	{
		m_position += velocity  * angleDir * dt * 400 * speed;
		velocity += acceleration;
		if(velocity.x <= 0.0f || velocity.y <= 0.0f) {
			stop();
		}
	}

	if(!owned) {
		m_bounds.x = m_position.x;
		m_bounds.y = m_position.y;
	}
}

void Item::VRender(GLRenderer* renderer, float dt)
{
	if(active)
		GameObject::VRender(renderer, dt);
}