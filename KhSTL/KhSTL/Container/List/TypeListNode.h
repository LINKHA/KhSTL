#ifndef KH_STL_LIST_NODE_H_
#define KH_STL_LIST_NODE_H_

namespace KhSTL {

/**
* Doubly-linked list node base class
*/
struct tListNodeBase
{
	/**
	* @brief : Construct
	*/
	tListNodeBase()
		: prev(nullptr)
		, next(nullptr)
	{}

	/// Previous node.
	tListNodeBase* prev;
	/// Next node.
	tListNodeBase* next;
};

/**
* List node
*/
template<typename _Ty>
struct tListNode : public tListNodeBase
{
	/**
	* @brief : Construct undefined
	*/
	tListNode() = default;
	/**
	* @brief : Construct with value
	*/
	explicit tListNode(const _Ty& tValue)
		: value(tValue)
	{}
	/**
	* @brief : Return next node
	*/
	tListNode* Next() const { return static_cast<tListNode*>(next); }
	/**
	* @brief : Return previous node
	*/
	tListNode* Prev() { return static_cast<tListNode*>(prev); }

	/// Node value
	_Ty value;
};

}
#endif //!KH_STL_LIST_NODE_H_