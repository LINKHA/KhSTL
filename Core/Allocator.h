#pragma once

#include "STLCom.h"

#include <cstddef>
#include <new>

namespace KhSTL
{

struct AllocatorBlock;
struct AllocatorNode;

/// %Allocator memory block.
struct KH_STL_API AllocatorBlock
{
    /// Size of a node.
    size_t _nodeSize;
    /// Number of nodes in this block.
    size_t _capacity;
    /// First free node.
    AllocatorNode* _free;
    /// Next allocator block.
    AllocatorBlock* _next;
    /// Nodes follow.
};

/// %Allocator node.
struct KH_STL_API AllocatorNode
{
    /// Next free node.
    AllocatorNode* _next;
    /// Data follows.
};

/// Initialize a fixed-_size allocator with the node _size and initial capacity.
KH_STL_API AllocatorBlock* AllocatorInitialize(size_t nodeSize, size_t initialCapacity = 1);
/// Uninitialize a fixed-_size allocator. Frees all blocks in the chain.
KH_STL_API void AllocatorUninitialize(AllocatorBlock* allocator);
/// Allocate a node. Creates a new block if necessary.
KH_STL_API void* AllocatorGet(AllocatorBlock* allocator);
/// Free a node. Does not free any blocks.
KH_STL_API void AllocatorFree(AllocatorBlock* allocator, void* node);

/// %Allocator template class. Allocates objects of a specific class.
template <typename _Ty> class Allocator
{
public:
    /// Construct with optional initial capacity.
    Allocator(size_t capacity = 0) :
        _allocator(nullptr)
    {
        if (capacity)
            Reserve(capacity);
    }
    
    /// Destruct. All objects reserved from this allocator should be freed before this is called.
    ~Allocator()
    {
        Reset();
    }
	/// Prevent copy construction.
	Allocator(const Allocator<_Ty>& rhs) = delete;
	/// Prevent assignment.
	Allocator<_Ty>& operator = (const Allocator<_Ty>& rhs) = delete;
    /// Reserve initial capacity. Only possible before allocating the first object.
    void Reserve(size_t capacity)
    {
        if (!_allocator)
            _allocator = AllocatorInitialize(sizeof(_Ty), capacity);
    }

    /// Allocate and default-construct an object.
    _Ty* Allocate()
    {
        if (!_allocator)
            _allocator = AllocatorInitialize(sizeof(_Ty));
        _Ty* newObject = static_cast<_Ty*>(AllocatorGet(_allocator));
        new(newObject) _Ty();
        
        return newObject;
    }
    
    /// Allocate and copy-construct an object.
    _Ty* Allocate(const _Ty& object)
    {
        if (!_allocator)
            _allocator = AllocatorInitialize(sizeof(_Ty));
        _Ty* newObject = static_cast<_Ty*>(AllocatorGet(_allocator));
        new(newObject) _Ty(object);
        
        return newObject;
    }
    
    /// Destruct and free an object.
    void Free(_Ty* object)
    {
        (object)->~_Ty();
        AllocatorFree(_allocator, object);
    }
    
    /// Free the allocator. All objects reserved from this allocator should be freed before this is called.
    void Reset()
    {
        AllocatorUninitialize(_allocator);
        _allocator = nullptr;
    }
    
private:
    /// Allocator block.
    AllocatorBlock* _allocator;
};

}
