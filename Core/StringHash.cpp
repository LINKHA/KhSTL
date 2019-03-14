#include "StringHash.h"

#include <cstdio>



namespace KhSTL
{

const StringHash StringHash::ZERO;

String StringHash::ToString() const
{
    char tempBuffer[CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%08X", _value);
    return String(tempBuffer);
}

}
