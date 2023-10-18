#include "global.h"

void CheckErr(bool done, Message msg)
{
    if(!done) {
        fprintf(stderr, "Error: %s", MsgToStr[msg]);
        exit(9);
    }
}
