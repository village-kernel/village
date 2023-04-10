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
#include "Defines.h"

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

	///List get nid 
	int GetNid() { return curNode->nid; }

	///Add object node to list
	int Add(Object* obj)
	{
		if (NULL == obj) return -1;

		Node** nextNode = &list;

		while (NULL != *nextNode)
		{			
			nextNode = &(*nextNode)->next;
		}

		*nextNode = new Node(obj, nidCounter++);

		return (NULL != *nextNode) ? (*nextNode)->nid : -1;
	}

	///Insert object node to list
	int Insert(Object* obj, int nid)
	{
		if (NULL == obj) return -1;

		Node** nextNode = &list;

		while (NULL != *nextNode)
		{
			if (nid < (*nextNode)->nid)
			{
				Node* currNode = *nextNode;
				*nextNode = new Node(obj, nid);
				(*nextNode)->next = currNode;
				return -1;
			}
			
			nextNode = &(*nextNode)->next;
		}

		*nextNode = new Node(obj, nid);

		return (NULL != *nextNode) ? (*nextNode)->nid : -1;
	}

	///Remove object node from list
	int Remove(Object* obj, int nid)
	{
		if (NULL == obj && 0 > nid) return _ERR;

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

				delete obj;

				return _OK;
			}
			else
			{
				prevNode = currNode;
				currNode = &(*currNode)->next;
			}
		}

		return _ERR;
	}

	///List GetItem
	Object* GetItem(int nid)
	{
		for (Node* node = list; NULL != node; node = node->next)
		{
			if (nid == node->nid) return node->obj;
		}
		return NULL;
	}
};
 
#endif //!__TEMPLATES_H__
