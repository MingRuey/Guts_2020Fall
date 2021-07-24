#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


bool is_ascii_char(const char str[], size_t size)
{
    if (size == 0)
        return false;
    for (int i = 0; i < size; i++)
        if (str[i] & 0x80) /* i.e. (unsigned) str[i] >= 128 */
            return false;
    return true;
}


bool is_ascii_array_memcpy(const char str[], size_t size)
{
    if (size == 0)
        return false;
    int i = 0;
    while ((i + 8) <= size) {
        uint64_t payload;
        memcpy(&payload, str + i, 8);
        if (payload & 0x8080808080808080)
            return false;
        i += 8;
    }
    while (i < size) {
        if (str[i] & 0x80)
            return false;
        i++;
    }
    return true;
}

bool is_ascii_array_cast(const char str[], size_t size)
{
    if (size == 0)
        return false;
    int i = 0;
    while ((i + 8) <= size) {
        uint64_t *payload = (uint64_t *) str;
        if (*payload & 0x8080808080808080)
            return false;
        i += 8;
    }
    while (i < size) {
        if (str[i] & 0x80)
            return false;
        i++;
    }
    return true;
}

void main()
{
    char sample[] = "123456789abcdef";
    bool result;
    result = is_ascii_array_memcpy(sample + 1, 15);
    result = is_ascii_array_cast(sample + 1, 15);
}

