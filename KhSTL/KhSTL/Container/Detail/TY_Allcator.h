#pragma once

namespace KH_STL {
namespace Detail
{
struct AllocatorBlock;
struct AllocatorNode;

/**
* Allocator memory block
*/
struct AllocatorBlock
{
	/// Size of a node.
	unsigned nodeSize;
	/// Number of nodes in this block.
	unsigned capacity;
	/// First free node.
	AllocatorNode* free;
	/// Next allocator block.
	AllocatorBlock* next;
	/// Nodes follow.
};


/**
* Allocator node
*/
struct AllocatorNode
{
	/// Next free node.
	AllocatorNode* next;
	/// Data follows.
};


/**
* @brief : Initialize a fixed-size allocator with the node size and initial capacity
*/
AllocatorBlock* AllocatorInitialize(unsigned nodeSize, unsigned initialCapacity = 1);
/**
* @brief : Uninitialize a fixed-size allocator. Frees all blocks in the chain
*/
void AllocatorUninitialize(AllocatorBlock* allocator);
/**
* @brief : Reserve a node. Creates a new block if necessary
*/
void* AllocatorReserve(AllocatorBlock* allocator);
/**
* @brief : Free a node. Does not free any blocks
*/
void AllocatorFree(AllocatorBlock* allocator, void* ptr);


/**
* Allocator template class. Allocates objects of a specific class
*/
template <class T> class Allocator
{
public:

	/**
	* @brief : Construct
	*/
	explicit Allocator(unsigned initialCapacity = 0) 
		: allocator_(nullptr)
	{
		if (initialCapacity)
			allocator_ = AllocatorInitialize((unsigned)sizeof(T), initialCapacity);
	}
	/**
	* @brief : Destruct
	*/
	~Allocator()
	{
		AllocatorUninitialize(allocator_);
	}
	/**
	* @brief : Prevent copy construction
	*/
	Allocator(const Allocator<T>& rhs) = delete;
	/**
	* @brief : Prevent assignment
	*/
	Allocator<T>& operator =(const Allocator<T>& rhs) = delete;
	/**
	* @brief : Reserve and default-construct an object
	*/
	T* Reserve()
	{
		if (!allocator_)
			allocator_ = AllocatorInitialize((unsigned)sizeof(T));
		auto* newObject = static_cast<T*>(AllocatorReserve(allocator_));
		new(newObject) T();

		return newObject;
	}
	/**
	* @brief : Reserve and copy-construct an object
	*/
	T* Reserve(const T& object)
	{
		if (!allocator_)
			allocator_ = AllocatorInitialize((unsigned)sizeof(T));
		auto* newObject = static_cast<T*>(AllocatorReserve(allocator_));
		new(newObject) T(object);

		return newObject;
	}
	/**
	* @brief : Destruct and free an object
	*/
	void Free(T* object)
	{
		(object)->~T();
		AllocatorFree(allocator_, object);
	}

private:
	/// Allocator block
	AllocatorBlock * allocator_;
};




}
}