#include "utils.hpp"

String binaryString(uint32_t num, int digitsCount)
{
    String result = "";
    for (int i = 0; i < digitsCount; i++)
    {
        result = String(num & 1) + result;
        num = num >> 1;
    }
    return result;
}