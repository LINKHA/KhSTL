#ifndef KH_STL_TYPEE_ALLCATOR_H_
#define KH_STL_TYPEE_ALLCATOR_H_
namespace KhSTL {
namespace Detail
{
struct tAllocatorBlock;
struct tAllocatorNode;

/**
* Allocator memory block
*/
struct tAllocatorBlock
{
	/// Size of a node.
	unsigned nodeSize;
	/// Number of nodes in this block.
	unsigned capacity;
	/// First free node.
	tAllocatorNode* free;
	/// Next allocator block.
	tAllocatorBlock* next;
	/// Nodes follow.
};


/**
* Allocator node
*/
struct tAllocatorNode
{
	/// Next free node.
	tAllocatorNode* next;
	/// Data follows.
};


/**
* @brief : Initialize a fixed-size allocator with the node size and initial capacity
*/
tAllocatorBlock* AllocatorInitialize(unsigned nodeSize, unsigned initialCapacity = 1);
/**
* @brief : Uninitialize a fixed-size allocator. Frees all blocks in the chain
*/
void AllocatorUninitialize(tAllocatorBlock* allocator);
/**
* @brief : Reserve a node. Creates a new block if necessary
*/
void* AllocatorReserve(tAllocatorBlock* allocator);
/**
* @brief : Free a node. Does not free any blocks
*/
void AllocatorFree(tAllocatorBlock* allocator, void* ptr);


/**
* Allocator template class. Allocates objects of a specific class
*/
template <class T> class tAllocator
{
public:

	/**
	* @brief : Construct
	*/
	explicit tAllocator(unsigned initialCapacity = 0) 
		: _allocator(nullptr)
	{
		if (initialCapacity)
			_allocator = AllocatorInitialize((unsigned)sizeof(T), initialCapacity);
	}
	/**
	* @brief : Destruct
	*/
	~tAllocator()
	{
		AllocatorUninitialize(_allocator);
	}
	/**
	* @brief : Prevent copy construction
	*/
	tAllocator(const tAllocator<T>& rhs) = delete;
	/**
	* @brief : Prevent assignment
	*/
	tAllocator<T>& operator =(const tAllocator<T>& rhs) = delete;
	/**
	* @brief : Reserve and default-construct an object
	*/
	T* Reserve()
	{
		if (!_allocator)
			_allocator = AllocatorInitialize((unsigned)sizeof(T));
		auto* newObject = static_cast<T*>(AllocatorReserve(_allocator));
		new(newObject) T();

		return newObject;
	}
	/**
	* @brief : Reserve and copy-construct an object
	*/
	T* Reserve(const T& object)
	{
		if (!_allocator)
			_allocator = AllocatorInitialize((unsigned)sizeof(T));
		auto* newObject = static_cast<T*>(AllocatorReserve(_allocator));
		new(newObject) T(object);

		return newObject;
	}
	/**
	* @brief : Destruct and free an object
	*/
	void Free(T* object)
	{
		(object)->~T();
		AllocatorFree(_allocator, object);
	}

private:
	/// Allocator block
	tAllocatorBlock* _allocator;
};




}
}

#endif //!KH_STL_TYPEE_ALLCATOR_H_