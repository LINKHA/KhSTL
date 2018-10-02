#ifndef KH_STL_TYPE_HASH_MAP_H_
#define KH_STL_TYPE_HASH_MAP_H_
#include "../../Utility/TypeHashBase.h"
#include "../../Utility/TypePair.h"
#include "../Vector/TypeVector.h"
#include "../../Utility/TypeIterator.h"
#include "../../Algorithm/TypeAlgorithm.h"

#include <initializer_list>

namespace KhSTL {

template <typename _Key
	, typename _Ty> 
	class tHashMap : public tHashBase 
{
	using KeyType = _Key;
	using ValueType = _Ty;
public:
	/**
	* Hash map key-value pair with const key
	*/
	class KeyValue
	{
	public:
		/**
		* @brief : Construct with default key
		*/
		KeyValue() 
			: first(_Key())
		{}
		/**
		* @brief : Construct with key and value
		*/
		KeyValue(const _Key& sfirst, const _Ty& ssecond)
			: first(sfirst)
			, second(ssecond)
		{}
		/**
		* @brief : Copy-construct
		*/
		KeyValue(const KeyValue& value) 
			: first(value.first)
			, second(value.second)
		{}
		/**
		* @brief : Prevent assignment
		*/
		KeyValue& operator =(const KeyValue& rhs) = delete;
		/**
		* @brief : _Keyest for equality with another pair
		*/
		bool operator ==(const KeyValue& rhs) const { return first == rhs.first && second == rhs.second; }
		/**
		* @brief : _Keyest for inequality with another pair
		*/
		bool operator !=(const KeyValue& rhs) const { return first != rhs.first || second != rhs.second; }

		/// Map key
		const _Key first;
		/// Map value
		_Ty second;
	};
	/// Hash map node.
	struct Node : public tHashNodeBase
	{
		/**
		* @brief : Construct undefined
		*/
		Node() = default;
		/**
		* @brief : Construct with key and value
		*/
		Node(const _Key& key, const _Ty& value) 
			: pair(key, value)
		{
		}

		/// Key-value pair.
		KeyValue pair;

		/// Return next node.
		Node* Next() const { return static_cast<Node*>(next); }

		/// Return previous node.
		Node* Prev() const { return static_cast<Node*>(prev); }

		/// Return next node in the bucket.
		Node* Down() const { return static_cast<Node*>(down); }
	};
	/**
	* Hash map node iterator
	*/
	struct Iterator : public tHashIteratorBase
	{
		/**
		* @brief : Construct
		*/
		Iterator() = default;
		/**
		* @brief : Construct with a node pointer
		*/
		explicit Iterator(Node* ptr) :
			tHashIteratorBase(ptr)
		{
		}
		/**
		* @brief : Preincrement the pointer
		*/
		Iterator& operator ++()
		{
			GotoNext();
			return *this;
		}
		/**
		* @brief : Postincrement the pointer
		*/
		Iterator operator ++(int)
		{
			Iterator it = *this;
			GotoNext();
			return it;
		} 
		/**
		* @brief : Predecrement the pointer
		*/
		Iterator& operator --()
		{
			GotoPrev();
			return *this;
		}
		/**
		* @brief : Postdecrement the pointer
		*/
		Iterator operator --(int)
		{
			Iterator it = *this;
			GotoPrev();
			return it;
		}
		/**
		* @brief : Point to the pair
		*/
		KeyValue* operator ->() const { return &(static_cast<Node*>(ptr))->pair; }
		/**
		* @brief : Dereference the pair
		*/
		KeyValue& operator *() const { return (static_cast<Node*>(ptr))->pair; }
	};
	/**
	* Hash map node const iterator
	*/
	struct ConstIterator : public tHashIteratorBase
	{
		/**
		* @brief : Construct
		*/
		ConstIterator() = default;
		/**
		* @brief : Construct with a node pointer
		*/
		explicit ConstIterator(Node* ptr) :
			tHashIteratorBase(ptr)
		{
		}
		/**
		* @brief : Construct from a non-const iterator
		*/
		ConstIterator(const Iterator& rhs) :        // NOLIN_Key(google-explicit-constructor)
			tHashIteratorBase(rhs.ptr)
		{}
		/**
		* @brief : Assign from a non-const iterator
		*/
		ConstIterator& operator =(const Iterator& rhs)
		{
			ptr = rhs.ptr;
			return *this;
		}
		/**
		* @brief : Preincrement the pointer
		*/
		ConstIterator& operator ++()
		{
			GotoNext();
			return *this;
		}
		/**
		* @brief : Postincrement the pointer
		*/
		ConstIterator operator ++(int)
		{
			ConstIterator it = *this;
			GotoNext();
			return it;
		}
		/**
		* @brief : Predecrement the pointer
		*/
		ConstIterator& operator --()
		{
			GotoPrev();
			return *this;
		}
		/**
		* @brief : Postdecrement the pointer
		*/
		ConstIterator operator --(int)
		{
			ConstIterator it = *this;
			GotoPrev();
			return it;
		}
		/**
		* @brief : Point to the pair
		*/
		const KeyValue* operator ->() const { return &(static_cast<Node*>(ptr))->pair; }
		/**
		* @brief : Dereference the pair
		*/
		const KeyValue& operator *() const { return (static_cast<Node*>(ptr))->pair; }
	};

	/**
	* Construct empty
	*/
	tHashMap()
	{
		// Reserve the tail node
		_allocator = AllocatorInitialize((unsigned)sizeof(Node));
		_head = _tail = ReserveNode();
	}
	/**
	* @brief : Construct from another hash map
	*/
	tHashMap(const tHashMap<_Key, _Ty>& map)
	{
		// Reserve the tail node + initial capacity according to the map's size
		_allocator = AllocatorInitialize((unsigned)sizeof(Node), map.Size() + 1);
		_head = _tail = ReserveNode();
		*this = map;
	}
	/**
	* @brief : Move-construct from another hash map
	*/
	tHashMap(tHashMap<_Key, _Ty> && map) noexcept
	{
		Swap(map);
	}
	/**
	* @brief : Aggregate initialization constructor
	*/
	tHashMap(const std::initializer_list<tPair<_Key, _Ty>>& list) : tHashMap()
	{
		for (auto it = list.begin(); it != list.end(); it++)
		{
			Insert(*it);
		}
	}
	/**
	* @brief : Destruct
	*/
	~tHashMap()
	{
		if (_allocator)
		{
			Clear();
			FreeNode(Tail());
			AllocatorUninitialize(_allocator);
			delete[] _ptrs;
		}
	}
	/**
	* @brief : Assign a hash map
	*/
	tHashMap& operator =(const tHashMap<_Key, _Ty>& rhs)
	{
		// In case of self-assignment do nothing
		if (&rhs != this)
		{
			Clear();
			Insert(rhs);
		}
		return *this;
	}
	/**
	* @brief : Move-assign a hash map
	*/
	tHashMap& operator =(tHashMap<_Key, _Ty> && rhs) noexcept
	{
		assert(&rhs != this);
		Swap(rhs);
		return *this;
	}
	/**
	* @brief : Add-assign a pair
	*/
	tHashMap& operator +=(const tPair<_Key, _Ty>& rhs)
	{
		Insert(rhs);
		return *this;
	}
	/**
	* @brief : Add-assign a hash map
	*/
	tHashMap& operator +=(const tHashMap<_Key, _Ty>& rhs)
	{
		Insert(rhs);
		return *this;
	}
	/**
	* @brief : _Keyest for equality with another hash map
	*/
	bool operator ==(const tHashMap<_Key, _Ty>& rhs) const
	{
		if (rhs.Size() != Size())
			return false;

		ConstIterator i = Begin();
		while (i != End())
		{
			ConstIterator j = rhs.Find(i->first);
			if (j == rhs.End() || j->second != i->second)
				return false;
			++i;
		}

		return true;
	}
	/**
	* @brief : _Keyest for inequality with another hash map
	*/
	bool operator !=(const tHashMap<_Key, _Ty>& rhs) const
	{
		if (rhs.Size() != Size())
			return true;

		ConstIterator i = Begin();
		while (i != End())
		{
			ConstIterator j = rhs.Find(i->first);
			if (j == rhs.End() || j->second != i->second)
				return true;
			++i;
		}

		return false;
	}
	/**
	* @brief : Index the map. Create a new pair if key not found
	*/
	_Ty& operator [](const _Key& key)
	{
		if (!_ptrs)
			return InsertNode(key, _Ty(), false)->pair.second;

		unsigned hashKey = Hash(key);

		Node* node = FindNode(key, hashKey);
		return node ? node->pair.second : InsertNode(key, _Ty(), false)->pair.second;
	}
	/**
	* @brief : Index the map. Return null if key is not found, does not create a new pair
	*/
	_Ty* operator [](const _Key& key) const
	{
		if (!_ptrs)
			return 0;

		unsigned hashKey = Hash(key);

		Node* node = FindNode(key, hashKey);
		return node ? &node->pair.second : 0;
	}
	/**
	* @brief : Populate the map using variadic template. _Keyhis handles the base case
	*/
	tHashMap& Populate(const _Key& key, const _Ty& value)
	{
		this->operator [](key) = value;
		return *this;
	};
	/**
	* @brief : Populate the map using variadic template
	*/
	template <typename... Args> tHashMap& Populate(const _Key& key, const _Ty& value, const Args&... args)
	{
		this->operator [](key) = value;
		return Populate(args...);
	};
	/**
	* @brief : Insert a pair. Return an iterator to it
	*/
	Iterator Insert(const tPair<_Key, _Ty>& pair)
	{
		return Iterator(InsertNode(pair.first, pair.second));
	}
	/**
	* @brief : Insert a pair. Return iterator and set exists flag according to 
	*			whether the key already existed.
	*/
	Iterator Insert(const tPair<_Key, _Ty>& pair, bool& exists)
	{
		unsigned oldSize = Size();
		Iterator ret(InsertNode(pair.first, pair.second));
		exists = (Size() == oldSize);
		return ret;
	}
	/**
	* @brief : Insert a map
	*/
	void Insert(const tHashMap<_Key, _Ty>& map)
	{
		ConstIterator it = map.Begin();
		ConstIterator end = map.End();
		while (it != end)
		{
			InsertNode(it->first, it->second);
			++it;
		}
	}
	/**
	* @brief : Insert a pair by iterator. Return iterator to the value
	*/
	Iterator Insert(const ConstIterator& it) 
	{ 
		return Iterator(InsertNode(it->first, it->second)); 
	}
	/**
	* @brief : Insert a range by iterators
	*/
	void Insert(const ConstIterator& start, const ConstIterator& end)
	{
		ConstIterator it = start;
		while (it != end)
			InsertNode(*it++);
	}
	/**
	* @brief : Erase a pair by key. Return true if was found
	*/
	bool Erase(const _Key& key)
	{
		if (!_ptrs)
			return false;

		unsigned hashKey = Hash(key);

		Node* previous;
		Node* node = FindNode(key, hashKey, previous);
		if (!node)
			return false;

		if (previous)
			previous->down = node->down;
		else
			ptrs()[hashKey] = node->down;

		EraseNode(node);
		return true;
	}
	/**
	* @brief : Erase a pair by iterator. Return iterator to the next pair
	*/
	Iterator Erase(const Iterator& it)
	{
		if (!_ptrs || !it.ptr)
			return End();

		auto* node = static_cast<Node*>(it.ptr);
		Node* next = node->Next();

		unsigned hashKey = Hash(node->pair.first);

		Node* previous = 0;
		auto* current = static_cast<Node*>(ptrs()[hashKey]);
		while (current && current != node)
		{
			previous = current;
			current = current->Down();
		}

		assert(current == node);

		if (previous)
			previous->down = node->down;
		else
			ptrs()[hashKey] = node->down;

		EraseNode(node);
		return Iterator(next);
	}
	/**
	* @brief : Clear the map
	*/
	void Clear()
	{
		// Prevent Find() from returning anything while the map is being cleared
		resetPtrs();

		if (Size())
		{
			for (Iterator i = Begin(); i != End();)
			{
				FreeNode(static_cast<Node*>(i++.ptr));
				i.ptr->prev = 0;
			}

			_head = _tail;
			setSize(0);
		}
	}
	/**
	* @brief : Sort pairs. After sorting the map can be iterated in order
	*			until new elements are inserted
	*/
	void Sort()
	{
		unsigned numKeys = Size();
		if (!numKeys)
			return;

		auto** ptrs = new Node*[numKeys];
		Node* ptr = Head();

		for (unsigned i = 0; i < numKeys; ++i)
		{
			ptrs[i] = ptr;
			ptr = ptr->Next();
		}

		Sort(tIterator<Node*>(ptrs), tIterator<Node*>(ptrs + numKeys), CompareNodes);

		_head = ptrs[0];
		ptrs[0]->prev = 0;
		for (unsigned i = 1; i < numKeys; ++i)
		{
			ptrs[i - 1]->next = ptrs[i];
			ptrs[i]->prev = ptrs[i - 1];
		}
		ptrs[numKeys - 1]->next = _tail;
		_tail->prev = ptrs[numKeys - 1];

		delete[] ptrs;
	}
	/**
	* @brief : Rehash to a specific bucket count, which must be a power of two. Return true if successful
	*/
	bool Rehash(unsigned numBuckets)
	{
		if (numBuckets == NumBuckets())
			return true;
		if (!numBuckets || numBuckets < Size() / MAX_LOAD_FACTOR)
			return false;

		// Check for being power of two
		unsigned check = numBuckets;
		while (!(check & 1u))
			check >>= 1;
		if (check != 1)
			return false;

		allocateBuckets(Size(), numBuckets);
		Rehash();
		return true;
	}
	/**
	* @brief : Return iterator to the pair with key, or end iterator if not found
	*/
	Iterator Find(const _Key& key)
	{
		if (!_ptrs)
			return End();

		unsigned hashKey = Hash(key);
		Node* node = FindNode(key, hashKey);
		if (node)
			return Iterator(node);
		else
			return End();
	}
	/**
	* @brief : Return const iterator to the pair with key, or end iterator if not found
	*/
	ConstIterator Find(const _Key& key) const
	{
		if (!_ptrs)
			return End();

		unsigned hashKey = Hash(key);
		Node* node = FindNode(key, hashKey);
		if (node)
			return ConstIterator(node);
		else
			return End();
	}
	/**
	* @brief : Return whether contains a pair with key
	*/
	bool Contains(const _Key& key) const
	{
		if (!_ptrs)
			return false;

		unsigned hashKey = Hash(key);
		return FindNode(key, hashKey) != 0;
	}
	/**
	* @brief : try to copy value to output. Return true if was found
	*/
	bool TryGetValue(const _Key& key, _Ty& out) const
	{
		if (!_ptrs)
			return false;
		unsigned hashKey = Hash(key);
		Node* node = FindNode(key, hashKey);
		if (node)
		{
			out = node->pair.second;
			return true;
		}
		else
			return false;
	}
	/**
	* @brief : Return all the keys
	*/
	tVector<_Key> Keys() const
	{
		tVector<_Key> result;
		result.Reserve(Size());
		for (ConstIterator i = Begin(); i != End(); ++i)
			result.Push(i->first);
		return result;
	}
	/**
	* @brief : Return all the values
	*/
	tVector<_Ty> Values() const
	{
		tVector<_Ty> result;
		result.Reserve(Size());
		for (ConstIterator i = Begin(); i != End(); ++i)
			result.Push(i->second);
		return result;
	}
	/**
	* @brief : Return iterator to the beginning
	*/
	Iterator Begin() { return Iterator(Head()); }
	/**
	* @brief : Return iterator to the beginning
	*/
	ConstIterator Begin() const { return ConstIterator(Head()); }
	/**
	* @brief : Return iterator to the end
	*/
	Iterator End() { return Iterator(Tail()); }
	/**
	* @brief : Return iterator to the end
	*/
	ConstIterator End() const { return ConstIterator(Tail()); }
	/**
	* @brief : Return first pair
	*/
	const KeyValue& Front() const { return *Begin(); }
	/**
	* @brief : Return last pair
	*/
	const KeyValue& Back() const { return *(--End()); }

private:
	/**
	* @brief : Return the head node
	*/
	Node* Head() const { return static_cast<Node*>(_head); }
	/**
	* @brief : Return the tail node
	*/
	Node* Tail() const { return static_cast<Node*>(_tail); }
	/**
	* @brief : Find a node from the buckets. Do not call if the buckets have not been allocated
	*/
	Node* FindNode(const _Key& key, unsigned hashKey) const
	{
		auto* node = static_cast<Node*>(ptrs()[hashKey]);
		while (node)
		{
			if (node->pair.first == key)
				return node;
			node = node->Down();
		}

		return 0;
	}
	/**
	* @brief : Find a node and the previous node from the buckets. Do not call if the buckets have not been allocated
	*/
	Node* FindNode(const _Key& key, unsigned hashKey, Node*& previous) const
	{
		previous = 0;

		auto* node = static_cast<Node*>(ptrs()[hashKey]);
		while (node)
		{
			if (node->pair.first == key)
				return node;
			previous = node;
			node = node->Down();
		}

		return 0;
	}
	/**
	* @brief : Insert a key and value and return either the new or existing node
	*/
	Node* InsertNode(const _Key& key, const _Ty& value, bool findExisting = true)
	{
		// If no pointers yet, allocate with minimum bucket count
		if (!_ptrs)
		{
			allocateBuckets(Size(), MIN_BUCKETS);
			Rehash();
		}

		unsigned hashKey = Hash(key);

		if (findExisting)
		{
			// If exists, just change the value
			Node* existing = FindNode(key, hashKey);
			if (existing)
			{
				existing->pair.second = value;
				return existing;
			}
		}

		Node* newNode = InsertNode(Tail(), key, value);
		newNode->down = ptrs()[hashKey];
		ptrs()[hashKey] = newNode;

		// Rehash if the maximum load factor has been exceeded
		if (Size() > NumBuckets() * MAX_LOAD_FACTOR)
		{
			allocateBuckets(Size(), NumBuckets() << 1);
			Rehash();
		}

		return newNode;
	}
	/**
	* @brief : Insert a node into the list. Return the new node
	*/
	Node* InsertNode(Node* dest, const _Key& key, const _Ty& value)
	{
		if (!dest)
			return 0;

		Node* newNode = ReserveNode(key, value);
		Node* prev = dest->Prev();
		newNode->next = dest;
		newNode->prev = prev;
		if (prev)
			prev->next = newNode;
		dest->prev = newNode;

		// Reassign the head node if necessary
		if (dest == Head())
			_head = newNode;

		setSize(Size() + 1);

		return newNode;
	}
	/**
	* @brief : Erase a node from the list. Return pointer to the next element, 
	*			or to the end if could not erase
	*/
	Node* EraseNode(Node* node)
	{
		// _Keyhe tail node can not be removed
		if (!node || node == _tail)
			return Tail();

		Node* prev = node->Prev();
		Node* next = node->Next();
		if (prev)
			prev->next = next;
		next->prev = prev;

		// Reassign the head node if necessary
		if (node == Head())
			_head = next;

		FreeNode(node);
		setSize(Size() - 1);

		return next;
	}
	/**
	* @brief : Reserve a node
	*/
	Node* ReserveNode()
	{
		auto* newNode = static_cast<Node*>(AllocatorReserve(_allocator));
		new(newNode) Node();
		return newNode;
	}
	/**
	* @brief : Reserve a node with specified key and value
	*/
	Node* ReserveNode(const _Key& key, const _Ty& value)
	{
		auto* newNode = static_cast<Node*>(AllocatorReserve(_allocator));
		new(newNode) Node(key, value);
		return newNode;
	}
	/**
	* @brief : Free a nod
	*/
	void FreeNode(Node* node)
	{
		(node)->~Node();
		AllocatorFree(_allocator, node);
	}
	/**
	* @brief : Rehash the buckets
	*/
	void Rehash()
	{
		for (Iterator i = Begin(); i != End(); ++i)
		{
			auto* node = static_cast<Node*>(i.ptr);
			unsigned hashKey = Hash(i->first);
			node->down = ptrs()[hashKey];
			ptrs()[hashKey] = node;
		}
	}

	/**
	* @brief : Compare two nodes
	*/
	static bool CompareNodes(Node*& lhs, Node*& rhs) { return lhs->pair.first < rhs->pair.first; }
	/**
	* @brief : Compute a hash based on the key and the bucket size
	*/
	unsigned Hash(const _Key& key) const { return MakeHash(key) & (NumBuckets() - 1); }
};

template <typename _Key, typename _Ty> typename tHashMap<_Key, _Ty>::ConstIterator begin(const tHashMap<_Key, _Ty>& v) { return v.Begin(); }

template <typename _Key, typename _Ty> typename tHashMap<_Key, _Ty>::ConstIterator end(const tHashMap<_Key, _Ty>& v) { return v.End(); }

template <typename _Key, typename _Ty> typename tHashMap<_Key, _Ty>::Iterator begin(tHashMap<_Key, _Ty>& v) { return v.Begin(); }

template <typename _Key, typename _Ty> typename tHashMap<_Key, _Ty>::Iterator end(tHashMap<_Key, _Ty>& v) { return v.End(); }


}
#endif //!KH_STL_TYPE_HASH_MAP_H_