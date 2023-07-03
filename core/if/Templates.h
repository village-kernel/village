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
#include "string.h"
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


/// @brief Class end point
class Class {};
typedef void (Class::*Method)(void*);
typedef void (*Function)(void*, void*);


/// @brief List class template 
/// @tparam Object 
template<typename Object>
class List
{
private:
	//Structures
	struct Node
	{
		Object* obj;
		int     nid;
		char*   name;
		Node*   prev;
		Node*   next;

		Node
		(
			Object* obj  = NULL,
			int     nid  = 0,
			char*   name = NULL
		):
			obj(obj),
			nid(nid),
			name(name),
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
	/// @brief Constructor
	List() :
		head(NULL),
		tail(NULL),
		iterator(NULL),
		nidCounter(0)
	{}

	/// @brief List begin node
	/// @return object pointer
	Object* Begin()
	{
		iterator = head;
		return Item();
	}

	/// @brief List next node
	/// @return object pointer
	Object* Next()
	{
		if (NULL != iterator)
		{
			iterator = iterator->next;
		}
		return Item();
	}

	/// @brief List prev node
	/// @return object pointer
	Object* Prev()
	{
		if (NULL != iterator)
		{
			iterator = iterator->prev;
		}
		return Item();
	}

	/// @brief List end node
	/// @return object pointer
	Object* End()
	{
		iterator = tail;
		return Item();
	}

	/// @brief List is begin
	/// @return result
	bool IsBegin()
	{
		return (NULL == iterator);
	}

	/// @brief List is begin
	/// @return result
	bool IsEnd()
	{
		return (NULL == iterator);
	}

	/// @brief List item
	/// @return object pointer
	Object* Item()
	{
		return (NULL != iterator) ? iterator->obj : NULL;
	}

	/// @brief List get node id 
	/// @return node id
	int GetNid()
	{
		return (NULL != iterator) ? iterator->nid : 0;
	}

	/// @brief List get node name
	/// @return node name
	char* GetName()
	{
		return (NULL != iterator) ? iterator->name : (char*)"None";
	}

	/// @brief Add object node to list
	/// @param obj object pointer
	/// @return result
	int Add(Object* obj)
	{
		if (NULL == obj) return -1;

		if (NULL == head)
		{
			nidCounter = 0;
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

	/// @brief Insert object node to list
	/// @param obj object pointer
	/// @param nid object node id
	/// @return result
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

	/// @brief Insert object node to list
	/// @param obj object pointer
	/// @param nid object node id
	/// @return result
	int InsertByName(Object* obj, char* name)
	{
		if (NULL == obj) return -1;

		Node* temp = NULL;

		if (NULL == head)
		{
			temp = new Node(obj, nidCounter++, name);
			head = temp;
			tail = head;
		}
		else
		{
			if (strcmp(name, tail->name) > 0)
			{
				temp = new Node(obj, nidCounter++, name);
				temp->prev = tail;
				tail->next = temp;
				tail = tail->next;
			}
			else if (strcmp(name, head->name) < 0)
			{
				temp = new Node(obj, nidCounter++, name);
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
					if (strcmp(name, nextNode->name) < 0)
					{
						temp = new Node(obj, nidCounter++, name);
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

	/// @brief Remove object node from list
	/// @param obj object pointer
	/// @param nid node id
	/// @return result
	int Remove(Object* obj, int nid = -1)
	{
		if (NULL == obj) return _ERR;

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

	/// @brief Remove object node from list
	/// @param obj object pointer
	/// @param nid node id
	/// @return result
	int RemoveByName(Object* obj, char* name)
	{
		if (NULL == obj) return _ERR;

		for (Node* node = head; NULL != node; node = node->next)
		{
			if ((0 == strcmp(name, node->name)) ||
				(obj == node->obj))
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

	/// @brief List GetItem
	/// @param nid node id
	/// @return object pointer
	Object* GetItem(int nid)
	{
		for (Node* node = head; NULL != node; node = node->next)
		{
			if (nid == node->nid) return node->obj;
		}
		return NULL;
	}

	/// @brief List GetItemByName
	/// @param nid node name
	/// @return object pointer
	Object* GetItemByName(const char* name)
	{
		for (Node* node = head; NULL != node; node = node->next)
		{
			if (0 == strcmp(name, node->name)) return node->obj;
		}
		return NULL;
	}

	/// @brief Release source
	void Release()
	{
		for (Node* node = head; NULL != node; node = node->next)
		{
			delete node->obj;
			delete node;
		}
	}
};
 
#endif //!__TEMPLATES_H__
