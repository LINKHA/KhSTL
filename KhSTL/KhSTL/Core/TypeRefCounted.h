#pragma once
namespace KhSTL {

class tRefCount
{
	/**
	* @brief : Construct
	*/
	tRefCount() :
		refs(0),
		weakRefs(0)
	{}
	/**
	* @brief : Destruct
	*/
	~tRefCount()
	{
		// Set reference counts below zero to fire Asserts if this object is still accessed
		refs = -1;
		weakRefs = -1;
	}
	/// Reference count. If below zero, the object has been destroyed.
	int refs;
	/// Weak reference count.
	int weakRefs;
};


/**
* Base class for intrusively reference-counted objects.
* These are noncopyable and non-assignable.
*/
class tRefCounted
{
public:
	/**
	* @brief : Construct. Allocate the reference count
	*		structure and set an initial self weak reference.
	*/
	tRefCounted() 
		: _refCount(new tRefCount())
	{
		(_refCount->weakRefs)++;
	}

	/**
	* @brief : Destruct. Mark as expired and also delete the reference
	*		count structure if no outside weak references exist.
	*/
	virtual ~tRefCounted()
	{
		assert(_refCount);
		//Assert(_refCount->refs == 0);
		WarningIfString(_refCount->refs == 0, "ref count is not zero!");
		assert(_refCount->weakRefs > 0);

		_refCount->refs = -1;
		(_refCount->weakRefs)--;
		if (!_refCount->weakRefs)
			delete _refCount;

		_refCount = nullptr;
	}
	/**
	* @brief : Prevent copy construction.
	*/
	tRefCounted(const tRefCounted& rhs) = delete;
	/**
	* @brief : Prevent assignment.
	*/
	tRefCounted& operator =(const tRefCounted& rhs) = delete;

	/**
	* @brief : Increment reference count. Can also be called outside
	*		of a sharedPtr for traditional reference counting.
	*/
	void AddRef()
	{
		Assert(_refCount->refs >= 0);
		(_refCount->refs)++;
	}
	/**
	* @brief : Decrement reference count and delete self if no more
	*		references. Can also be called outside of a sharedPtr for
	*		traditional reference counting.
	*/
	void ReleaseRef()
	{
		Assert(_refCount->refs > 0);
		(_refCount->refs)--;
		if (!_refCount->refs)
			delete this;
	}
	/**
	* @brief : Return reference count.
	*/
	int Refs() const
	{
		return _refCount->refs;
	}
	/**
	* @brief : Return weak reference count.
	*/
	int WeakRefs() const;
	/**
	* @brief : Return pointer to the reference count structure.
	*/
	tRefCount* RefCountPtr() { return _refCount; }

private:
	/// Pointer to the reference count structure.
	tRefCount* _refCount
	{
		return _refCount->weakRefs - 1;
	}
};

}