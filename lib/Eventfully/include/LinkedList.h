#ifndef __CLINKEDLIST_H
#define __CLINKEDLIST_H

#include <arduino.h>
#include <Generic.h>
#include <ListItem.h>

class LinkedList
{
	private:
		ListItem *	first;
		ListItem *	last;
		ListItem *	current;
		long		entries;
		
	public:
		LinkedList();
		virtual ~LinkedList();
		virtual const char * GetType() { return "LinkedList"; };
		
		ListItem *	InsertFirst(ListItem *); // new
		ListItem *	InsertLast(ListItem * insert);
		ListItem *	InsertBefore(ListItem * entry, ListItem * refItem = NULL); // new
		ListItem *	InsertAfter(ListItem * entry, ListItem * refItem = NULL); // new
		ListItem *	InsertSorted(ListItem * entry);

		ListItem *	Remove(ListItem * entry);
		ListItem *	RemovePtr(ListItem * entry);

		ListItem *	GetFirstItem() { current = first; return (first); };
		ListItem *	GetFirstItem(WORD type);

		ListItem *	GetLastItem() { current = last; return (last); };
		ListItem *	GetLastItem(WORD type);

		ListItem *	GetNextItem() { if(current) current = current->next; return (current); };
		ListItem *	GetNextItem(ListItem * entry) { if(entry) return (entry->next); else return (NULL); };
		ListItem *	GetNextItem(WORD type, ListItem * entry);

		ListItem *	GetPreviousItem() { if(current) current = current->prev; return (current); };
		ListItem *	GetPreviousItem(ListItem * entry) { if(entry) return (entry->prev); else return (NULL); };
		ListItem *	GetPreviousItem(WORD type, ListItem * entry);

		ListItem *	GetCurrentItem() { return (current); };
		long		GetCount()	{ return entries; };

		ListItem *	LocateName(char * EntryName);
		ListItem *	LocateNameN(char * EntryName);
		ListItem *	LocateNameNI(char * EntryName);
		ListItem *	LocateName(WORD type, char * EntryName);
		ListItem *	LocateName(char * Entryname, bool * bMatch);
		ListItem *	LocateNameReverse(char * EntryName);
		
		void 		Sort();
		ListItem *	GetItemForward(long lOrder, ListItem * refItem = NULL);
		ListItem *	GetItemBackward(long lOrder, ListItem * refItem = NULL);
		void 		FreeAllEntries();
};

#endif