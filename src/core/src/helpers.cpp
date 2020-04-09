
#include <macros.hpp>

char *strtolower(char *str, unsigned int len)
{
    for (unsigned int i = 0; i < len; i++) {
        if ((str[i] >= 'A') && (str[i] <= 'Z')) {
            str[i] += 32;
        }
    }
    return str;
}

char *strtoupper(char *str, unsigned int len)
{
    for (unsigned int i = 0; i < len; i++) {
        if ((str[i] >= 'a') && (str[i] <= 'z')) {
            str[i] -= 32;
        }
    }
    return str;
}
