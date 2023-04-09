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
template<typename Object, typename Id = int>
class List
{
private:
	//Structures
	struct Node
	{
		Object* obj;
		Node*   next;

		Node(Object* obj = NULL) :
			obj(obj),
			next(NULL)
		{}
	};

	//Members
	Node* list;
	Node* curNode;
public:
	///Constructor
	List() : list(NULL) {}

	///List begin node
	void Begin() { curNode = list; }

	///List next node
	void Next() { if (NULL != curNode) curNode = curNode->next; }

	///List end
	bool End() { return (NULL == curNode); }

	///List item
	Object* Item() { return curNode->obj; }

	///Add object node to list
	void Add(Object* obj, Id id)
	{
		Node** nextNode = &list;

		if (obj) obj->SetID(id); else return;

		while (NULL != *nextNode)
		{
			uint32_t curModuleID = (*nextNode)->obj->GetID();
			uint32_t newModuleID = obj->GetID();

			if (newModuleID < curModuleID)
			{
				Node* curNode = *nextNode;
				*nextNode = new Node(obj);
				(*nextNode)->next = curNode;
				return;
			}
			
			nextNode = &(*nextNode)->next;
		}

		*nextNode = new Node(obj);
	}

	///Remove object node from list
	void Remove(Object* obj, Id id)
	{
		Node** prevNode = &list;
		Node** currNode = &list;

		while (NULL != *currNode)
		{
			if (obj == (*currNode)->obj)
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
	Object* GetItem(Id id)
	{
		Node** nextNode = &list;

		while (NULL != *nextNode)
		{
			Id curObjId = (*nextNode)->obj->GetID();
			Id getObjId = id;

			if (getObjId == curObjId)
			{
				return (*nextNode)->obj;
			}

			nextNode = &(*nextNode)->next;
		}

		return NULL;
	}
};
 
#endif //!__TEMPLATES_H__
