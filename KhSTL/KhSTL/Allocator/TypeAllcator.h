#ifndef KH_STL_TYPEE_ALLCATOR_H_
#define KH_STL_TYPEE_ALLCATOR_H_
namespace KhSTL {

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
template <class _Value> class tAllocator
{
public:

	/**
	* @brief : Construct
	*/
	explicit tAllocator(unsigned initialCapacity = 0) 
		: _allocator(nullptr)
	{
		if (initialCapacity)
			_allocator = AllocatorInitialize((unsigned)sizeof(_Value), initialCapacity);
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
	tAllocator(const tAllocator<_Value>& rhs) = delete;
	/**
	* @brief : Prevent assignment
	*/
	tAllocator<_Value>& operator =(const tAllocator<_Value>& rhs) = delete;
	/**
	* @brief : Reserve and default-construct an object
	*/
	_Value* Reserve()
	{
		if (!_allocator)
			_allocator = AllocatorInitialize((unsigned)sizeof(_Value));
		auto* newObject = static_cast<_Value*>(AllocatorReserve(_allocator));
		new(newObject) _Value();

		return newObject;
	}
	/**
	* @brief : Reserve and copy-construct an object
	*/
	_Value* Reserve(const _Value& object)
	{
		if (!_allocator)
			_allocator = AllocatorInitialize((unsigned)sizeof(_Value));
		auto* newObject = static_cast<_Value*>(AllocatorReserve(_allocator));
		new(newObject) _Value(object);

		return newObject;
	}
	/**
	* @brief : Destruct and free an object
	*/
	void Free(_Value* object)
	{
		(object)->~_Value();
		AllocatorFree(_allocator, object);
	}

private:
	/// Allocator block
	tAllocatorBlock* _allocator;
};




}

#endif //!KH_STL_TYPEE_ALLCATOR_H_