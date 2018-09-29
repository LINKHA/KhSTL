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
	/// Size of a node
	unsigned nodeSize;
	/// Number of nodes in this block
	unsigned capacity;
	/// First free node
	tAllocatorNode* free;
	/// Next allocator block
	tAllocatorBlock* next;
	/// Nodes follow
};


/**
* Allocator node
*/
struct tAllocatorNode
{
	/// Next free node
	tAllocatorNode* next;
	/// Data follows
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
template <class _Ty> 
	class tAllocator
{
public:
	using ValueType = _Ty;
public:
	/**
	* @brief : Construct default allocator (do nothing)
	*/
	constexpr tAllocator() noexcept
		: _allocator(nullptr)
	{
		_allocator = AllocatorInitialize((unsigned)sizeof(_Ty));
	}
	/**
	* @brief : Construct
	*/
	explicit tAllocator(unsigned initialCapacity) 
		: _allocator(nullptr)
	{
		if (initialCapacity)
			_allocator = AllocatorInitialize((unsigned)sizeof(_Ty), initialCapacity);
	}
	/**
	* @brief : Destruct
	*/
	virtual ~tAllocator()
	{
		AllocatorUninitialize(_allocator);
	}
	/**
	* @brief : Prevent copy construction
	*/
	tAllocator(const tAllocator<_Ty>& rhs) = delete;
	/**
	* @brief : Prevent assignment
	*/
	tAllocator<_Ty>& operator =(const tAllocator<_Ty>& rhs) = delete;

	/**
	* @brief : Reserve and default-construct an object
	*/
	_Ty* Reserve()
	{
		if (!_allocator)
			_allocator = AllocatorInitialize((unsigned)sizeof(_Ty));
		auto* newObject = static_cast<_Ty*>(AllocatorReserve(_allocator));
		new(newObject) _Ty();

		return newObject;
	}
	/**
	* @brief : Reserve and copy-construct an object
	*/
	_Ty* Reserve(const _Ty& object)
	{
		if (!_allocator)
			_allocator = AllocatorInitialize((unsigned)sizeof(_Ty));
		auto* newObject = static_cast<_Ty*>(AllocatorReserve(_allocator));
		new(newObject) _Ty(object);

		return newObject;
	}
	/**
	* @brief : Destruct and free an object
	*/
	void Free(_Ty* object)
	{
		(object)->~_Ty();
		AllocatorFree(_allocator, object);
	}
	/**
	* @brief : Destruct and free an other object
	*/
	template <typename _Other> void Free(_Other* object)
	{
		(object)->~_Other();
		AllocatorFree(_allocator, object);
	}
	/**
	* @brief : Allocate allocator
	*/
	void* Allocation()
	{
		return AllocatorReserve(_allocator);
	}
private:
	/// Allocator block
	tAllocatorBlock* _allocator;
};




}

#endif //!KH_STL_TYPEE_ALLCATOR_H_