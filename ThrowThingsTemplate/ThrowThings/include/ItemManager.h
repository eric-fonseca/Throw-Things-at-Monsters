#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <vix_vector2.h>
#include <vix_texture.h>
#include <vix_contentmanager.h>

class Item;
using namespace Vixen;

class ItemManager
{
	typedef std::vector<Item*> ItemList;

public:
	ItemManager(ContentManager* content);
	~ItemManager(void);

	void SpawnItem(int itemCode, Vixen::Vector2 position);

	ItemList& getItems(void);

private:
	ItemList items;
	ContentManager* contentManage;
};

#endif

