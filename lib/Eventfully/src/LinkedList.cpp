#include <arduino.h>
#include <LinkedList.h>
#include <ListItem.h>

LinkedList::LinkedList()
{
	first = last = current = nullptr;
	entries = 0;
}

LinkedList::~LinkedList()
{
	FreeAllEntries();
}

ListItem * LinkedList::InsertLast(ListItem * insert)
{
	// Check if this is first entry into list
	if(last == NULL && first == NULL) {
		first = last = insert;
		insert->next = insert->prev = NULL;
	}
	else {
		last->next = insert;
		insert->prev = last;
		insert->next = NULL;
		last = insert;
	}

	++entries;

	insert->owner = this;
	current = insert;
	
	return(insert);
}

ListItem * LinkedList::RemovePtr(ListItem * entry)
{
	ListItem *	ptr;

	if(entry == NULL)
		return NULL;
	
	if(first == entry && last == entry) {
		first = NULL;
		last = NULL;
		ptr = NULL;
	}
	else if (first == entry) {
		first = entry->next;
		first->prev = NULL;
		ptr = first;
	}
	else if (last == entry) {
		last = entry->prev;
		last->next = NULL;
		ptr = last;
	}
	else {
		(entry->prev)->next = entry->next;
		(entry->next)->prev = entry->prev;
		ptr = entry->next;
	}
	
	entry->owner = NULL;
	--entries;
	
	current = ptr;
	return(ptr);
}

ListItem * LinkedList::Remove(ListItem * entry)
{
	ListItem * ptr;

	if(entry == NULL)
		return NULL;

	ptr = RemovePtr(entry);
	delete entry;

	return(ptr);
}

void LinkedList::FreeAllEntries()
{
	current = GetFirstItem();
	while(current)
		Remove(current);
}

ListItem * LinkedList::GetFirstItem(WORD type)
{
	ListItem * ptr = first;

	while(ptr) {
		if(ptr->type == type)
			break;

		ptr = ptr->next;
	}

	return ptr;
}

ListItem * LinkedList::GetLastItem(WORD type)
{
	ListItem * ptr = last;

	while(ptr) {
		if(ptr->type == type)
			break;

		ptr = ptr->prev;
	}

	return ptr;
}

ListItem * LinkedList::GetNextItem(WORD type, ListItem * entry)
{
	ListItem * ptr = entry->next;

	while(ptr) {
		if(ptr->type == type)
			break;

		ptr = ptr->next;
	}

	return ptr;
}

ListItem * LinkedList::GetPreviousItem(WORD type, ListItem * entry)
{
	ListItem * ptr = entry->prev;

	while(ptr) {
		if(ptr->type == type)
			break;

		ptr = ptr->prev;
	}

	return ptr;
}

ListItem * LinkedList::LocateName(char *EntryName)
{
	ListItem * ptr;

	if(*EntryName == 0 || EntryName == NULL) {
		return NULL;
	}

	ptr = GetFirstItem();
	
	while(ptr) {
		if(ptr->Compare(EntryName) == 0)
			break;
		ptr = GetNextItem(ptr);
	}
	
	return ptr;
}

ListItem * LinkedList::LocateNameNI(char *EntryName)
{
	ListItem * ptr;

	if(*EntryName == 0 || EntryName == NULL) {
		return NULL;
	}

	ptr = GetFirstItem();
	
	while(ptr) {
		if(ptr->CompareNI(EntryName) == 0)
			break;
		ptr = GetNextItem(ptr);
	}
	
	return ptr;
}

ListItem * LinkedList::LocateNameN(char *EntryName)
{
	ListItem * ptr;

	if(*EntryName == 0 || EntryName == NULL) {
		return NULL;
	}

	ptr = GetFirstItem();
	
	while(ptr) {
		if(ptr->CompareN(EntryName) == 0)
			break;
		ptr = GetNextItem(ptr);
	}
	
	return ptr;
}

ListItem * LinkedList::LocateName(WORD type, char *EntryName)
{
	ListItem * ptr;

	if(*EntryName == 0 || EntryName == NULL) {
		return NULL;
	}

	ptr = GetFirstItem(type);
	
	while(ptr) {
		if(ptr->Compare(EntryName) == 0)
			break;
		ptr = GetNextItem(type, ptr);
	}
	
	return ptr;
}

ListItem * LinkedList::InsertBefore(ListItem * insert, ListItem * refItem)
{
	ListItem * pItem;
	
	if(refItem)
		pItem = refItem;
	else
		pItem = current;
		
	if(pItem == NULL || pItem == first)
		InsertFirst(insert);
	else {
		// if this entry already belongs to a list
		// remove it from that list and insert it into this one
		// to have multiple objects in lists, copy them.
		if(insert->owner)
			((LinkedList *)insert->owner)->RemovePtr(insert);

		// If other activities occurs on list, wait
		// WaitOnLocalSemaphore(spChangeActivity);

		insert->prev = pItem->prev;
		insert->next = pItem;
		pItem->prev = insert;
		if(insert->prev)
			(insert->prev)->next = insert;

		++entries;

		insert->owner = this;
		current = insert;
	
		// Ready changing pointers
		// SignalLocalSemaphore(spChangeActivity);
	}
	
	return(insert);
}

ListItem * LinkedList::InsertAfter(ListItem * insert, ListItem * refItem)
{
	ListItem * pItem;
	
	if(refItem)
		pItem = refItem;
	else
		pItem = current;
		
	if(pItem == NULL || pItem == last)
		InsertLast(insert);
	else {
		// if this entry already belongs to a list
		// remove it from that list and insert it into this one
		// to have multiple objects in lists, copy them.
		if(insert->owner)
			((LinkedList *)insert->owner)->RemovePtr(insert);
	
		// If other activities occurs on list, wait
		// WaitOnLocalSemaphore(spChangeActivity);

		insert->next = pItem->next;
		insert->prev = pItem;
		pItem->next = insert;
		if(insert->next)
			(insert->next)->prev = insert;

		++entries;
	
		insert->owner = this;
		current = insert;
	
		// Ready changing pointers
		// SignalLocalSemaphore(spChangeActivity);
	}

	return(insert);
}

ListItem * LinkedList::InsertSorted(ListItem * entry)
{
	ListItem *	liPtr;
	bool			bMatch;
	
	liPtr = LocateName(entry->pszName, &bMatch);
	
	// if liPtr == NULL (not found) it is inserted first
	InsertBefore(entry, liPtr);
	return entry;
}

ListItem * LinkedList::InsertFirst(ListItem * insert)
{
	// if this entry already belongs to a list
	// remove it from that list and insert it into this one
	// to have multiple objects in lists, copy them.
	if(insert->owner)
		((LinkedList *)insert->owner)->RemovePtr(insert);

	// If other activities occurs on list, wait
	// WaitOnLocalSemaphore(spChangeActivity);

	// Check if this is first entry into list
	if(last == NULL && first == NULL) {
		first = last = insert;
		insert->next = insert->prev = NULL;
	}
	else {
		first->prev = insert;
		insert->prev = NULL;
		insert->next = first;
		first = insert;
	}

	++entries;

	insert->owner = this;
	current = insert;

	// Ready changing pointers
	// SignalLocalSemaphore(spChangeActivity);
	
	return(insert);
}

void LinkedList::Sort()
{
	ListItem *	pItem, * pItemCmp, * pItemCmpStart;
	long			lJump = entries;
	bool			bSwitch;
	
	// If other activities occurs on list, wait
	// WaitOnLocalSemaphore(spChangeActivity);

	while(lJump > 1) {
		bSwitch = true;
		lJump = lJump / 2;
		if(lJump % 2 && lJump != 1)
			lJump--;
			
		pItemCmpStart = GetItemForward(lJump, __null);

		while(bSwitch) {
			bSwitch = false;
			pItem = first;
			pItemCmp = pItemCmpStart;
	
			while(pItem && pItemCmp) {
				if(pItem->Compare(pItemCmp->pszName) > 0) {

					pItem->Switch(pItemCmp);

					if(pItemCmp == pItemCmpStart)
						pItemCmpStart = pItem;
						
					pItem = pItemCmp->next;
					pItemCmp = pItem->next;
					bSwitch = true;
				}
				else {
					pItem = pItem->next;
					pItemCmp = pItemCmp->next;
				}
			}
		}
	}

	// Ready changing pointers
	// SignalLocalSemaphore(spChangeActivity);
}

ListItem * LinkedList::GetItemForward(long lOrder, ListItem * refItem)
{
	ListItem *	liPtr;
	long 			lCnt = lOrder;
	
	if(refItem == NULL)
		liPtr = first;
	else
		liPtr = refItem;
		
	while(liPtr) {
		liPtr = liPtr->next;
		if(--lCnt == 0)
			break;
	}
	
	return liPtr;
}

ListItem * LinkedList::GetItemBackward(long lOrder, ListItem * refItem)
{
	ListItem *	liPtr;
	long 			lCnt = lOrder;
	
	if(refItem == NULL)
		liPtr = first;
	else
		liPtr = refItem;
		
	while(liPtr) {
		liPtr = liPtr->prev;
		if(--lCnt == 0)
			break;
	}
	
	return liPtr;
}

ListItem * LinkedList::LocateName(char * EntryName, bool * bMatch)
{
	ListItem *	ptr;
	int				cResult;

	*bMatch = false;
	
	if(*EntryName == 0 || EntryName == NULL) {
		// Log(LOG_DEBUG, "EntryName in LocateName was NULL or first char = 0\n");
		return NULL;
	}

	// If other activities occurs on list, wait
	// WaitOnLocalSemaphore(spChangeActivity);

	ptr = GetFirstItem();
	
	while(ptr) {
		if((cResult = ptr->Compare(EntryName)) == 0) {
			*bMatch = true;
			break;
		}
		else if(cResult > 0)
			break;
			
		ptr = GetNextItem(ptr);
	}
	
	// Ready changing pointers
	// SignalLocalSemaphore(spChangeActivity);

	return ptr;
}

ListItem * LinkedList::LocateNameReverse(char * EntryName)
{
	ListItem * ptr;

	if(*EntryName == 0 || EntryName == NULL) {
		// Log(LOG_DEBUG, "EntryName in LocateNameReverse was NULL or first char = 0\n");
		return NULL;
	}

	// If other activities occurs on list, wait
	// WaitOnLocalSemaphore(spChangeActivity);

	ptr = GetLastItem();
	
	while(ptr) {
		if(ptr->Compare(EntryName) == 0)
			break;
		ptr = GetPreviousItem(ptr);
	}
	
	// Ready changing pointers
	// SignalLocalSemaphore(spChangeActivity);

	return ptr;
}
