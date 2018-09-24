#include "TY_Allcator.h"

namespace KH_STL {
namespace Detail
{

AllocatorBlock* AllocatorReserveBlock(AllocatorBlock* allocator, unsigned nodeSize, unsigned capacity)
{
	if (!capacity)
		capacity = 1;

	auto* blockPtr = new unsigned char[sizeof(AllocatorBlock) + capacity * (sizeof(AllocatorNode) + nodeSize)];
	auto* newBlock = reinterpret_cast<AllocatorBlock*>(blockPtr);
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
	unsigned char* nodePtr = blockPtr + sizeof(AllocatorBlock);
	auto* firstNewNode = reinterpret_cast<AllocatorNode*>(nodePtr);

	for (unsigned i = 0; i < capacity - 1; ++i)
	{
		auto* newNode = reinterpret_cast<AllocatorNode*>(nodePtr);
		newNode->next = reinterpret_cast<AllocatorNode*>(nodePtr + sizeof(AllocatorNode) + nodeSize);
		nodePtr += sizeof(AllocatorNode) + nodeSize;
	}
	// i == capacity - 1
	{
		auto* newNode = reinterpret_cast<AllocatorNode*>(nodePtr);
		newNode->next = nullptr;
	}

	allocator->free = firstNewNode;

	return newBlock;
}

AllocatorBlock* AllocatorInitialize(unsigned nodeSize, unsigned initialCapacity)
{
	AllocatorBlock* block = AllocatorReserveBlock(nullptr, nodeSize, initialCapacity);
	return block;
}

void AllocatorUninitialize(AllocatorBlock* allocator)
{
	while (allocator)
	{
		AllocatorBlock* next = allocator->next;
		delete[] reinterpret_cast<unsigned char*>(allocator);
		allocator = next;
	}
}

void* AllocatorReserve(AllocatorBlock* allocator)
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
	AllocatorNode* freeNode = allocator->free;
	void* ptr = (reinterpret_cast<unsigned char*>(freeNode)) + sizeof(AllocatorNode);
	allocator->free = freeNode->next;
	freeNode->next = nullptr;

	return ptr;
}

void AllocatorFree(AllocatorBlock* allocator, void* ptr)
{
	if (!allocator || !ptr)
		return;

	auto* dataPtr = static_cast<unsigned char*>(ptr);
	auto* node = reinterpret_cast<AllocatorNode*>(dataPtr - sizeof(AllocatorNode));

	// Chain the node back to free nodes
	node->next = allocator->free;
	allocator->free = node;
}



}
}