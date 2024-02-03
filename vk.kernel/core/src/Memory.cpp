//###########################################################################
// Memory.cpp
// Definitions of the functions that manage memory
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Memory.h"
#include "Kernel.h"
#include "Debug.h"


/// @brief ConcreteMemory
class ConcreteMemory : public Memory
{
private:
	//Structures
	struct Map 
	{
		uint32_t addr;
		uint32_t size;

		Map(uint32_t addr = 0, uint32_t size = 0):
			addr(addr),
			size(size)
		{}
	};

	struct MapNode
	{
		Map map;
		MapNode* prev;
		MapNode* next;

		MapNode(Map map = 0):
			map(map),
			prev(NULL),
			next(NULL)
		{}
	};
private:
	//Static constants
	const static uint8_t  align = 4;
	const static uint32_t size_of_node = sizeof(MapNode);
	const static uint32_t kernel_rsvd_heap  = 0x4000;  //10k
	const static uint32_t kernel_rsvd_stack = 0x3200;  //8k

	//Sram parameters
	bool isMemReady;
	uint32_t sram_start;
	uint32_t sram_ended;
	uint32_t sram_used;
	uint32_t sbrk_heap;

	//Members
	MapNode* head;
	MapNode* tail;
	MapNode* curr;
public:
	/// @brief Constructor
	ConcreteMemory()
		:isMemReady(false),
		sram_start(0),
		sram_ended(0),
		sram_used(0),
		sbrk_heap(0),
		head(NULL),
		tail(NULL),
		curr(NULL)
	{
		Initialize();
	}


	/// @brief Destructor
	~ConcreteMemory()
	{
	}


	/// @brief Memory initialize sram parameters
	void Initialize()
	{
		//Clear memory ready flag
		isMemReady = false;

		//Initialize heap end at first call
		if (0 == sbrk_heap)
		{
			//Symbol defined in the linker script
			extern void* _ebss;
			extern void* _estack;

			//Calculate sram start and end address
			sram_start = (uint32_t)&_ebss   + kernel_rsvd_heap;
			sram_ended = (uint32_t)&_estack - kernel_rsvd_stack;

			//Aligning sram_start and sram_ended by align byte
			if (sram_start % align) sram_start += (align - (sram_start % align));
			if (sram_ended % align) sram_ended -= (sram_ended % align);

			//Calculate the used size of sram
			sram_used  = kernel_rsvd_heap + kernel_rsvd_stack;

			//Calculate sbrk stack address
			sbrk_heap  = (uint32_t)&_ebss;
		}

		//Initialize list, align 4 bytes
		if (NULL == head || NULL == tail)
		{
			head       = (MapNode*)(sram_start) + 0;
			tail       = (MapNode*)(sram_start) + 1;

			head->map  = Map(sram_start + size_of_node, size_of_node);
			head->prev = NULL;
			head->next = tail;

			tail->map  = Map(sram_ended - size_of_node, size_of_node);
			tail->prev = head;
			tail->next = NULL;

			curr       = head;
		}

		//Set memory ready flag
		isMemReady = true;
	}


	/// @brief Memory heap alloc
	/// @param size heap alloc byte size
	/// @return alloc address
	uint32_t HeapAlloc(uint32_t size)
	{
		MapNode* newNode  = NULL;
		MapNode* currNode = curr;
		MapNode* nextNode = curr->next;
		uint32_t nextMapSize = 0;
		uint32_t nextMapAddr = 0;
		uint32_t nextEndAddr = 0;

		//Find free space
		while (NULL != nextNode)
		{
			//Calculate the next map size
			nextMapSize = size_of_node + size;

			//Align memory by aligning allocation sizes
			if (nextMapSize % align) nextMapSize += (align - (nextMapSize % align));

			//Calculate the next map and end addr
			nextMapAddr = currNode->map.addr + currNode->map.size;
			nextEndAddr = nextMapAddr + nextMapSize;

			//There is free space between the current node and the next node
			if (nextEndAddr <= nextNode->map.addr)
			{
				//Output debug info
				if (isMemReady)
				{
					kernel->debug->Output
					(
						Debug::_Lv0, 
						"heap alloc: addr = 0x%08lx, size = %ld",
						nextMapAddr,
						nextMapSize
					);
				}

				//Update the used size of sram
				sram_used += nextMapSize;

				//Add map node into list
				newNode           = (MapNode*)(nextMapAddr);
				newNode->map.addr = nextMapAddr;
				newNode->map.size = nextMapSize;
				newNode->prev     = currNode;
				newNode->next     = nextNode;
				currNode->next    = newNode;
				nextNode->prev    = newNode;
				curr              = newNode;
				return newNode->map.addr + size_of_node;
			}
			else
			{
				currNode = nextNode;
				nextNode = nextNode->next;
			}
		}

		//Out of memory
		if (isMemReady) kernel->debug->Error("out of memory.");

		//Halt on here
		while(1) {}
	}


	/// @brief Memory stack alloc
	/// @param size stack alloc byte size
	/// @return alloc address
	uint32_t StackAlloc(uint32_t size)
	{
		MapNode* newNode  = new MapNode();
		MapNode* prevNode = tail->prev;
		MapNode* currNode = tail;
		uint32_t prevMapSize = 0;
		uint32_t prevMapAddr = 0;
		uint32_t prevEndAddr = 0;

		//Find free space
		while (NULL != prevNode)
		{
			//Calculate the prev map size
			prevMapSize = size;

			//Align memory by aligning allocation sizes
			if (prevMapSize % align) prevMapSize += (align - (prevMapSize % align));

			//Calculate the prev map and end addr
			prevMapAddr = currNode->map.addr - currNode->map.size;
			prevEndAddr = prevMapAddr - prevMapSize;

			//There is free space between the current node and the prev node
			if (prevEndAddr >= prevNode->map.addr)
			{
				//Output debug info
				if (isMemReady)
				{
					kernel->debug->Output
					(
						Debug::_Lv0,
						"stack alloc: addr = 0x%08lx, size = %ld",
						prevMapAddr,
						prevMapSize
					);
				}

				//Update the used size of sram
				sram_used += prevMapSize;

				//Add map node into list
				newNode->map.addr = prevMapAddr;
				newNode->map.size = prevMapSize;
				newNode->prev     = prevNode;
				newNode->next     = currNode;
				currNode->prev    = newNode;
				prevNode->next    = newNode;
				return newNode->map.addr;
			}
			else
			{
				currNode = prevNode;
				prevNode = prevNode->prev;
			}
		}

		//Out of memory
		if (isMemReady) kernel->debug->Error("out of memory.");

		//Halt on here
		while(1) {}
	}


	/// @brief Memory free
	/// @param memory free address
	/// @param size free byte size
	void Free(uint32_t memory, uint32_t size)
	{
		if (0 == memory) return;

		MapNode* currNode = curr;

		while (NULL != currNode)
		{
			if ((memory >= currNode->map.addr) && 
				(memory < (currNode->map.addr + currNode->map.size)))
			{
				if (0 == size || size_of_node == (currNode->map.size - size))
				{
					//Remove map node from list
					currNode->prev->next = currNode->next;
					currNode->next->prev = currNode->prev;
				}
				else
				{
					//Reduce space
					currNode->map.size = currNode->map.size - size;
				}

				//Update current node pointer
				curr = (currNode->prev) ? currNode->prev : head;

				//Update the used size of sram
				sram_used -= currNode->map.size;

				//Output debug info
				if (isMemReady)
				{
					kernel->debug->Output
					(
						Debug::_Lv0,
						"free memory: addr = 0x%08lx, size = %ld",
						currNode->map.addr,
						currNode->map.size
					);
				}

				break;
			}
			else
			{
				currNode = (memory < currNode->map.addr) ? currNode->prev : currNode->next;
			}
		}
	}

	/// @brief Get the max size of sram
	uint32_t GetSize()  { return sram_ended; }

	/// @brief Get the used size of sram
	uint32_t GetUsed() { return sram_used; }
};


///Register module
REGISTER_MODULE(ConcreteMemory, ModuleID::_memory, memory);



/// @brief Memory new method
/// @param size byte size
/// @return address
void* New(uint32_t size)
{
	return (void*)kernel->memory->HeapAlloc((uint32_t)size);
}
EXPORT_SYMBOL_ALIAS(_Z3Newm, _Znwm);
EXPORT_SYMBOL_ALIAS(_Z3Newm, _Znam);
EXPORT_SYMBOL_ALIAS(_Z3Newm, _Znwj);
EXPORT_SYMBOL_ALIAS(_Z3Newm, _Znaj);
EXPORT_SYMBOL_ALIAS(_Z3Newm, malloc);


/// @brief Memory delete method
/// @param ptr address
void Delete(void* ptr)
{
	kernel->memory->Free((uint32_t)ptr);
}
EXPORT_SYMBOL_ALIAS(_Z6DeletePv, _ZdaPv);
EXPORT_SYMBOL_ALIAS(_Z6DeletePv, _ZdlPv);
EXPORT_SYMBOL_ALIAS(_Z6DeletePv, free);


/// @brief Memory delete method
/// @param ptr address
/// @param size byte size
void DeleteSize(void* ptr, uint32_t size)
{
	kernel->memory->Free((uint32_t)ptr, size);
}
EXPORT_SYMBOL_ALIAS(_Z10DeleteSizePvm, _ZdaPvm);
EXPORT_SYMBOL_ALIAS(_Z10DeleteSizePvm, _ZdlPvm);
EXPORT_SYMBOL_ALIAS(_Z10DeleteSizePvm, _ZdaPvj);
EXPORT_SYMBOL_ALIAS(_Z10DeleteSizePvm, _ZdlPvj);


/// @brief Override new
/// @param size byte size
/// @return address
void *operator new(size_t size)
{
	return New(size);
}


/// @brief Override new[]
/// @param size byte size
/// @return address
void *operator new[](size_t size)
{
	return New(size);
}


/// @brief Override delete
/// @param ptr address
void operator delete(void *ptr)
{
	Delete(ptr);
}


/// @brief Override delete[]
/// @param ptr address
void operator delete[](void *ptr)
{
	Delete(ptr);
}


/// @brief Override delete
/// @param ptr address
/// @param size byte size
void operator delete(void *ptr, size_t size)
{
	DeleteSize(ptr, size);
}


/// @brief Override delete[]
/// @param ptr address
/// @param size byte size
void operator delete[](void *ptr, size_t size)
{
	DeleteSize(ptr, size);
}


/// @brief malloc
/// @param size 
/// @return 
extern "C" void* malloc(size_t size)
{
	return New(size);
}


/// @brief free
/// @param ptr 
extern "C" void free(void* ptr)
{
	Delete(ptr);
}
