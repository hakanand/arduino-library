#define __LISTITEM

#include <arduino.h>
#include <ListItem.h>
#include <LinkedList.h>

ListItem::ListItem()
{
	prev = next = NULL;
	owner = NULL;
	pszName = NULL;
}

ListItem::ListItem(char * pszEntryName)
{
	prev = next = NULL;
	owner = NULL;
	if(pszEntryName && *pszEntryName) {
		pszName = (char *)malloc(strlen(pszEntryName) + 1);
		strcpy(pszName, pszEntryName);
	}
	else
		pszName = NULL;
}

ListItem::~ListItem()
{
	if(pszName)
		free(pszName);

	if(owner)
		owner->RemovePtr(this);
}

int	ListItem::Compare(char * pszEntryName)
{
	if(pszName && pszEntryName)
		return strcasecmp(pszName, pszEntryName);
	else
		return 0xFFFF;
}

int	ListItem::CompareNI(char * pszEntryName)
{
	if(pszName && pszEntryName)
		return strncasecmp(pszName, pszEntryName, strlen(pszEntryName));
	else
		return 0xFFFF;
}

int	ListItem::CompareN(char * pszEntryName)
{
	if(pszName && pszEntryName)
		return strncmp(pszName, pszEntryName, strlen(pszEntryName));
	else
		return 0xFFFF;
}

void ListItem::Switch(ListItem * pSwitch)
{
	ListItem * ptrNext, * ptrPrev;
	
	// save old values
	ptrNext = next;
	ptrPrev = prev;
	
	prev = pSwitch->prev;
	next = pSwitch->next;
	pSwitch->prev = ptrPrev;
	pSwitch->next = ptrNext;
	
	if((pSwitch->prev)->next)
		(pSwitch->prev)->next = pSwitch;
	
	if((pSwitch->next)->prev)
		(pSwitch->next)->prev = pSwitch;
	
	if(prev->next)
		prev->next = this;
	if(next->prev)
		next->prev = this;
}
