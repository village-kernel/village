//###########################################################################
// List.h
// Declarations of the list
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __LIST_H__
#define __LIST_H__

#include "stdint.h"
#include "stddef.h"
#include "string.h"


/// @brief List class template 
/// @tparam Object 
template<typename Object>
class List
{
private:
	//Structures
	struct Node
	{
		Object  obj;
		int     nid;
		char*   name;
		Node*   prev;
		Node*   next;

		Node
		(
			Object  obj  = NULL,
			int     nid  = 0,
			char*   name = NULL
		):
			obj(obj),
			nid(nid),
			name(NULL),
			prev(NULL),
			next(NULL)
		{
			if (NULL != name)
			{
				this->name = new char[strlen(name) + 1]();
				strcpy(this->name, name);
			}
		}

		~Node() { if (NULL != name) delete[] this->name; }
	};

	//Members
	Node* head;
	Node* tail;
	Node* iterator;
	int   nidCounter;
	int   size;
public:
	/// @brief Constructor
	List() :
		head(NULL),
		tail(NULL),
		iterator(NULL),
		nidCounter(0),
		size(0)
	{}

	/// @brief List begin node
	/// @return object pointer
	Object Begin()
	{
		iterator = head;
		return Item();
	}

	/// @brief List next node
	/// @return object pointer
	Object Next()
	{
		if (NULL != iterator)
		{
			iterator = iterator->next;
		}
		return Item();
	}

	/// @brief List prev node
	/// @return object pointer
	Object Prev()
	{
		if (NULL != iterator)
		{
			iterator = iterator->prev;
		}
		return Item();
	}

	/// @brief List end node
	/// @return object pointer
	Object End()
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

	/// @brief List is empty
	/// @return result
	bool IsEmpty()
	{
		return (NULL == head);
	}

	/// @brief List item
	/// @return object pointer
	Object Item()
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

	/// @brief List get size
	/// @return size
	int GetSize()
	{
		return size;
	}

	/// @brief Add object node to list
	/// @param obj object pointer
	/// @return result
	int Add(Object obj, char* name = NULL)
	{
		if (NULL == obj) return -1;

		if (NULL == head)
		{
			nidCounter = 0;
			head = new Node(obj, nidCounter++, name);
			tail = head;
		}
		else
		{
			tail->next = new Node(obj, nidCounter++, name);
			tail->next->prev = tail;
			tail = tail->next;
		}

		if (NULL != tail) size++;

		return (NULL != tail) ? tail->nid : -1;
	}

	/// @brief Insert object node to list
	/// @param obj object pointer
	/// @param nid object node id
	/// @return result
	int Insert(Object obj, int nid, char* name = NULL)
	{
		if (NULL == obj) return -1;

		Node* temp = NULL;

		if (NULL == head)
		{
			temp = new Node(obj, nid, name);
			head = temp;
			tail = head;
		}
		else
		{
			if (nid > tail->nid)
			{
				temp = new Node(obj, nid, name);
				temp->prev = tail;
				tail->next = temp;
				tail = tail->next;
			}
			else if (nid < head->nid)
			{
				temp = new Node(obj, nid, name);
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
						temp = new Node(obj, nid, name);
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

		if (NULL != temp) size++;

		return (NULL != temp) ? temp->nid : -1;
	}

	/// @brief Insert object node to list
	/// @param obj object pointer
	/// @param nid object node id
	/// @return result
	int Insert(Object obj, char* name)
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

		if (NULL != temp) size++;

		return (NULL != temp) ? temp->nid : -1;
	}

	/// @brief Remove object node from list
	/// @param obj object pointer
	/// @param nid node id
	/// @return result
	bool Remove(Object obj, int nid = -1)
	{
		if (NULL == obj) return false;

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

				size--;
				delete node;
				return true;
			}
		}

		return false;
	}


	/// @brief Remove object node from list
	/// @param nid node id
	/// @return result
	bool Remove(int nid)
	{
		return Remove(GetItem(nid), nid); 
	}


	/// @brief Remove object node from list
	/// @param obj object pointer
	/// @param nid node id
	/// @return result
	bool Remove(Object obj, char* name)
	{
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

				size--;
				delete node;
				return true;
			}
		}

		return false;
	}

	/// @brief List GetItem
	/// @param nid node id
	/// @return object pointer
	Object GetItem(int nid)
	{
		for (Node* node = head; NULL != node; node = node->next)
		{
			if (nid == node->nid) return node->obj;
		}
		return NULL;
	}

	/// @brief List GetItem
	/// @param nid node name
	/// @return object pointer
	Object GetItem(const char* name)
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
		Node* node = head;
		
		while (NULL != node)
		{
			Node* next = node->next;
			delete node;
			node = next;
		}
	}
};
 
#endif //!__LIST_H__
