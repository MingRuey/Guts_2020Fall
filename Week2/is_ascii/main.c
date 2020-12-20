#include <stdio.h>
#include "is_ascii.c"

void main()
{
    char sample[] = "helloworld";
    bool result;
    result = is_ascii_char(sample, 10);
    printf("%s\n", result ? "true" : "false");
}