#pragma once
#include <cstddef>

namespace KH_STL
{
namespace Detail { 
/**
* @brief : Pointer hash function
*/
template <typename T> unsigned makeHash(T* value)
{
	return (unsigned)((size_t)value / sizeof(T));
}
/**
* @brief : Const pointer hash function
*/
template <typename T> unsigned makeHash(const T* value)
{
	return (unsigned)((size_t)value / sizeof(T));
}
/**
* @brief : Generic hash function
*/
template <typename T> unsigned makeHash(const T& value)
{
	return value.ToHash();
}
/**
* @brief : Void pointer hash function
*/
template <> inline unsigned makeHash(void* value)
{
	return (unsigned)(size_t)value;
}
/**
* @brief : Const void pointer hash function
*/
template <> inline unsigned makeHash(const void* value)
{
	return (unsigned)(size_t)value;
}
/**
* @brief : Long long hash function
*/
template <> inline unsigned makeHash(const long long& value)
{
	return (unsigned)((value >> 32u) | (value & 0xffffffffu));
}
/**
* @brief : Unsigned long long hash function
*/
template <> inline unsigned makeHash(const unsigned long long& value)
{
	return (unsigned)((value >> 32u) | (value & 0xffffffffu));
}
/**
* @brief : Int hash function
*/
template <> inline unsigned makeHash(const int& value)
{
	return (unsigned)value;
}
/**
* @brief : Unsigned hash function
*/
template <> inline unsigned makeHash(const unsigned& value)
{
	return value;
}
/**
* @brief : Short hash function
*/
template <> inline unsigned makeHash(const short& value)
{
	return (unsigned)value;
}
/**
* @brief : Unsigned short hash function
*/
template <> inline unsigned makeHash(const unsigned short& value)
{
	return value;
}
/**
* @brief : Char hash function
*/
template <> inline unsigned makeHash(const char& value)
{
	return (unsigned)value;
}
/**
* @brief : Unsigned char hash function
*/
template <> inline unsigned makeHash(const unsigned char& value)
{
	return value;
}


}
}