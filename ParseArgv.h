#ifndef PARSEARGV_H
#define PARSEARGV_H
#include <stdint.h>

    // Prevent buffer overflows
#define MAX_ARGUMENT_VALUE_SIZE 100 // In bytes
#define MAX_ARGUMENT_COUNT 16

namespace ARGC {
    extern unsigned char SavedArguments;
};

extern char FindArg(int argc, char* argv[], unsigned char id, const char* prefix, char PrefixSize);
extern uint8_t FindID(uint8_t id);
extern char* GetArgv(uint8_t id);
extern bool CheckArg(uint8_t id);
extern int GetArgvSize(uint8_t id);

#endif // PARSEARGV_H
