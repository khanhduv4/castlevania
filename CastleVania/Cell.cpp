#include "Cell.h"
#include "Utils.h"
Cell::Cell()
{
	listObj.clear();
}


Cell::~Cell()
{

}

void Cell::Insert(LPGAMEOBJECT object)
{
	try {
		listObj.push_back(object);
	}
	catch (exception e) {
		//DebugOut(L"%s", e.what());
	}
	
}

void Cell::Unload()
{
	listObj.clear();
}
