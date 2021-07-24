#include <ctype.h>
#include <stddef.h>
#include <stdint.h>

/* in-place implementation for converting all characters into lowercase. */
void strlower(char *s, size_t n)
{
    for (size_t j = 0; j < n; j++) {
        if (s[j] >= 'A' && s[j] <= 'Z')
            s[j] ^= 1 << 5;
        else if ((unsigned) s[j] >= '\x7f') /* extended ASCII */
            s[j] = tolower(s[j]);
    }
}

#define PACKED_BYTE(b) (((uint64_t)(b) & (0xff)) * 0x0101010101010101u)

/* vectorized implementation for in-place strlower */
void strlower_vector(char *s, size_t n)
{
    size_t k = n / 8;
    for (size_t i = 0; i < k; i++, s += 8) {
        uint64_t *chunk = (uint64_t*) s;
        if ((*chunk & PACKED_BYTE(0x80)) == 0) { /* is ASCII? */
            uint64_t A = *chunk + PACKED_BYTE(128 - 'A');
            uint64_t Z = *chunk + PACKED_BYTE(128 - 'Z' - 1);
            uint64_t mask = ((A ^ Z) & PACKED_BYTE(0x80)) >> 2;
            *chunk ^= mask;
        } else {
            strlower(s, 8);
        }
    }

    k = n % 8;
    if (k)
        strlower(s, k);
}
