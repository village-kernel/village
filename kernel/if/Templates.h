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
		Node*   prev;
		Node*   next;

		Node(Object* obj = NULL, int nid = 0) :
			obj(obj),
			nid(nid),
			prev(NULL),
			next(NULL)
		{}
	};

	//Members
	Node* head;
	Node* tail;
	Node* iterator;
	int   nidCounter;
public:
	///Constructor
	List() :
		head(NULL),
		tail(NULL),
		iterator(NULL),
		nidCounter(0)
	{}

	///List begin node
	void Begin() { iterator = head; }

	///List next node
	void Next() { if (NULL != iterator) iterator = iterator->next; }

	///List prev node
	void Prev() { if (NULL != iterator) iterator = iterator->prev; }

	///List end node
	void End() { iterator = tail; }

	///List is begin
	bool IsBegin() { return (NULL == iterator); }

	///List is end
	bool IsEnd() { return (NULL == iterator); }

	///List item
	Object* Item() { return iterator->obj; }

	///List get node id 
	int GetNid() { return iterator->nid; }

	///Add object node to list
	int Add(Object* obj)
	{
		if (NULL == obj) return -1;

		if (0 == nidCounter)
		{
			head = new Node(obj, nidCounter++);
			tail = head;
		}
		else
		{
			tail->next = new Node(obj, nidCounter++);
			tail->next->prev = tail;
			tail = tail->next;
		}

		return (NULL != tail) ? tail->nid : -1;
	}

	///Insert object node to list
	int Insert(Object* obj, int nid)
	{
		if (NULL == obj) return -1;

		Node* temp = NULL;

		if (NULL == head)
		{
			temp = new Node(obj, nid);
			head = temp;
			tail = head;
		}
		else
		{
			if (nid > tail->nid)
			{
				temp = new Node(obj, nid);
				temp->prev = tail;
				tail->next = temp;
				tail = tail->next;
			}
			else if (nid < head->nid)
			{
				temp = new Node(obj, nid);
				temp->next = head;
				head->prev = temp;
				head = head->prev;
			}
			else
			{
				Node* prevNode = head;
				Node* nextNode = head->next;

				while (NULL != nextNode)
				{
					if (nid < nextNode->nid)
					{
						temp = new Node(obj, nid);
						temp->prev = prevNode;
						temp->next = nextNode;
						prevNode->next = temp;
						nextNode->prev = temp;
						break;
					}
					else
					{
						prevNode = nextNode;
						nextNode = nextNode->next;
					}
				}
			}
		}

		nidCounter = tail->nid;

		return (NULL != temp) ? temp->nid : -1;
	}

	///Remove object node from list
	int Remove(Object* obj, int nid)
	{
		if (NULL == obj && 0 > nid) return _ERR;

		for (Node* node = head; NULL != node; node = node->next)
		{
			if ((obj == node->obj) || (nid == node->nid))
			{
				if (NULL != node->prev)
					node->prev->next = node->next;
				else
					head = node->next;

				if (NULL != node->next)
					node->next->prev = node->prev;
				else
					tail = node->prev;

				delete node;
				delete obj;
				return _OK;
			}
		}

		return _ERR;
	}

	///List GetItem
	Object* GetItem(int nid)
	{
		for (Node* node = head; NULL != node; node = node->next)
		{
			if (nid == node->nid) return node->obj;
		}
		return NULL;
	}
};
 
#endif //!__TEMPLATES_H__
