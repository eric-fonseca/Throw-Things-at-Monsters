#include "ItemManager.h"
#include "Item.h"
#include "AllWeapons.h"


ItemManager::ItemManager(ContentManager* content)
{
	contentManage = content;
}


ItemManager::~ItemManager(void)
{
}

/*
Spawns an item based on the given Item code
*/
void ItemManager::SpawnItem(int itemCode, Vixen::Vector2 position){

	Item* newItem = NULL;

	switch (itemCode){
	
	//Blunt weapons
	case 101:
		newItem = new SmallRock();
		//newItem->SetTexture();
		break;

	//Sharp Weapons
	case 201:
		newItem = new ThrowingKnife();
		//newItem->SetTexture();
		break;

	//Chain Weapons
	case 301:
		newItem = new FlyingClaw();
		//newItem->SetTexture();
		break;

	default:
		//ERROR, not a valid item code
		break;
	}

	if(newItem) {
		newItem->SetPosition(position);
		newItem->SetOrigin(Vixen::Vector2(16,16));
	}
	
	items.push_back(newItem);
	
}
