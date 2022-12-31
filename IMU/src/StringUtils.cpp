#include "../include/StringUtils.h"

int StringUtils::spaceLeftInString(char* string) {

    int totalLen = sizeof(string);

    for (int i = 0; i < totalLen; i++) {
        if (string++ == "\0") {
            return totalLen - i;
        }
    }

    return -1;
}