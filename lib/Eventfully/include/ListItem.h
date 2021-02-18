#ifndef __CLISTITEM_H
#define __CLISTITEM_H

#include <arduino.h>
#include <Generic.h>

class LinkedList;

class ListItem
{
	private:
		ListItem *		prev;
		ListItem *		next;
		LinkedList *	owner;

	protected:
		ListItem * GetPrev() { return prev; };
		ListItem * GetNext() { return next; };

	public:
		ListItem();
		ListItem(char * pszEntryName);
		virtual ~ListItem();

		virtual int		Compare(ListItem * entry) { return 0; };
		virtual int		Compare(char * pszEntryName);
		virtual int		Compare(long lEntryId) { return 0; };
		virtual int		CompareNI(char * pszEntryName);
		virtual int		CompareN(char * pszEntryName);

		virtual WORD	Read() { return 0; };
		virtual WORD	Write() { return 0; };
		virtual void 	Switch(ListItem * pSwitch);
		
		LinkedList * GetOwner() { return owner; };
		virtual const char * GetType() { return "ListItem"; };

		time_t	tmLastUsed;
		char *	pszName;
		WORD	type;

		friend class LinkedList;
};

#endif