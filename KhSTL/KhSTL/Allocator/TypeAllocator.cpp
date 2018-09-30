#include "TypeAllocator.h"

namespace KhSTL {

tAllocatorBlock* AllocatorReserveBlock(tAllocatorBlock* allocator, unsigned nodeSize, unsigned capacity)
{
	if (!capacity)
		capacity = 1;

	auto* blockPtr = new unsigned char[sizeof(tAllocatorBlock) + capacity * (sizeof(tAllocatorNode) + nodeSize)];
	auto* newBlock = reinterpret_cast<tAllocatorBlock*>(blockPtr);
	newBlock->nodeSize = nodeSize;
	newBlock->capacity = capacity;
	newBlock->free = nullptr;
	newBlock->next = nullptr;

	if (!allocator)
		allocator = newBlock;
	else
	{
		newBlock->next = allocator->next;
		allocator->next = newBlock;
	}

	// Initialize the nodes. Free nodes are always chained to the first (parent) allocator
	unsigned char* nodePtr = blockPtr + sizeof(tAllocatorBlock);
	auto* firstNewNode = reinterpret_cast<tAllocatorNode*>(nodePtr);

	for (unsigned i = 0; i < capacity - 1; ++i)
	{
		auto* newNode = reinterpret_cast<tAllocatorNode*>(nodePtr);
		newNode->next = reinterpret_cast<tAllocatorNode*>(nodePtr + sizeof(tAllocatorNode) + nodeSize);
		nodePtr += sizeof(tAllocatorNode) + nodeSize;
	}
	// i == capacity - 1
	{
		auto* newNode = reinterpret_cast<tAllocatorNode*>(nodePtr);
		newNode->next = nullptr;
	}

	allocator->free = firstNewNode;

	return newBlock;
}

tAllocatorBlock* AllocatorInitialize(unsigned nodeSize, unsigned initialCapacity)
{
	tAllocatorBlock* block = AllocatorReserveBlock(nullptr, nodeSize, initialCapacity);
	return block;
}

void AllocatorUninitialize(tAllocatorBlock* allocator)
{
	while (allocator)
	{
		tAllocatorBlock* next = allocator->next;
		delete[] reinterpret_cast<unsigned char*>(allocator);
		allocator = next;
	}
}

void* AllocatorReserve(tAllocatorBlock* allocator)
{
	if (!allocator)
		return nullptr;

	if (!allocator->free)
	{
		// Free nodes have been exhausted. Allocate a new larger block
		unsigned newCapacity = (allocator->capacity + 1) >> 1u;
		AllocatorReserveBlock(allocator, allocator->nodeSize, newCapacity);
		allocator->capacity += newCapacity;
	}

	// We should have new free node(s) chained
	tAllocatorNode* freeNode = allocator->free;
	void* ptr = (reinterpret_cast<unsigned char*>(freeNode)) + sizeof(tAllocatorNode);
	allocator->free = freeNode->next;
	freeNode->next = nullptr;

	return ptr;
}

void AllocatorFree(tAllocatorBlock* allocator, void* ptr)
{
	if (!allocator || !ptr)
		return;

	auto* dataPtr = static_cast<unsigned char*>(ptr);
	auto* node = reinterpret_cast<tAllocatorNode*>(dataPtr - sizeof(tAllocatorNode));

	// Chain the node back to free nodes
	node->next = allocator->free;
	allocator->free = node;
}



}