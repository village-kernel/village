//###########################################################################
// Templates.h
// Declarations of the templates
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __TEMPLATES_H__
#define __TEMPLATES_H__

#include "stdint.h"
#include "stddef.h"


/// @brief Get method address
/// @tparam dst_type 
/// @tparam src_type 
/// @param src 
/// @return addr 
template<typename dst_type, typename src_type>
dst_type pointer_cast(src_type src)
{
	return *static_cast<dst_type*>(static_cast<void*>(&src));
}


/// @brief Get method address
/// @tparam dst_type 
/// @tparam src_type 
/// @param src 
/// @return addr 
template<typename dst_type, typename src_type>
dst_type union_cast(src_type src)
{
	union{ src_type s; dst_type d; } u;
	u.s = src;
	return u.d;
}


///Class end point
class Class {};
typedef void (Class::*Method)(char*);
typedef void (*Function)(char*);


///List class template 
template<typename Object>
class List
{
private:
	//Structures
	struct Node
	{
		Object* obj;
		int     nid;
		Node*   next;

		Node(Object* obj = NULL, int nid = 0) :
			obj(obj),
			nid(nid),
			next(NULL)
		{}
	};

	//Members
	Node* list;
	Node* curNode;
	int   nidCounter;
public:
	///Constructor
	List() :
		list(NULL),
		curNode(NULL),
		nidCounter(0)
	{}

	///List begin node
	void Begin() { curNode = list; }

	///List next node
	void Next() { if (NULL != curNode) curNode = curNode->next; }

	///List end
	bool End() { return (NULL == curNode); }

	///List item
	Object* Item() { return curNode->obj; }

	///Add object node to list
	void Add(Object* obj)
	{
		if (NULL == obj) return;

		Node** nextNode = &list;

		while (NULL != *nextNode)
		{			
			nextNode = &(*nextNode)->next;
		}

		*nextNode = new Node(obj, ++nidCounter);
	}

	///Insert object node to list
	void Insert(Object* obj, int nid)
	{
		if (NULL == obj) return;

		Node** nextNode = &list;

		while (NULL != *nextNode)
		{
			if (nid < (*nextNode)->nid)
			{
				Node* curNode = *nextNode;
				*nextNode = new Node(obj, nid);
				(*nextNode)->next = curNode;
				return;
			}
			
			nextNode = &(*nextNode)->next;
		}

		*nextNode = new Node(obj, nid);
	}

	///Remove object node from list
	void Remove(Object* obj, int nid)
	{
		if (NULL == obj && 0 == nid) return;

		Node** prevNode = &list;
		Node** currNode = &list;

		while (NULL != *currNode)
		{
			if ((obj == (*currNode)->obj) || 
				(nid == (*currNode)->nid))
			{
				delete *currNode;

				if (*prevNode == *currNode)
					*prevNode = (*currNode)->next;
				else
					(*prevNode)->next = (*currNode)->next;

				break;
			}
			else
			{
				prevNode = currNode;
				currNode = &(*currNode)->next;
			}
		}
	}

	///List GetItem
	Object* GetItem(int nid)
	{
		Node** nextNode = &list;

		while (NULL != *nextNode)
		{
			if (nid == (*nextNode)->nid)
			{
				return (*nextNode)->obj;
			}

			nextNode = &(*nextNode)->next;
		}

		return NULL;
	}
};
 
#endif //!__TEMPLATES_H__
