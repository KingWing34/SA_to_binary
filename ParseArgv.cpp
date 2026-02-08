/* A little argv parser written in C++ by King_Wing34
 *
 * It's simple, that's all I need.
 *
 */

#include <stdint.h>
#include "ParseArgv.h"


        // Struct holding extra information about the
        // arguments passed to the program.
        // Also Declare a specified amount of structs
        // The "-1" is because we don't need a place for argument '0' aka usually the
        // argument that was passed to run the program
struct {

        // Extra information that can be set to whatever you need
    char* data = nullptr;
    int size {0};

        // Used to determin the type if necessary
    unsigned char id {0};

} ArgData[MAX_ARGUMENT_COUNT - 1];


namespace ARGC {
    unsigned char SavedArguments = {0};
};


int StringSize(char* Argv) {
    int count {0};
    while(Argv[count] != 0) count++;
    return count;
}


        // Sets available arguments. Give the usual argc and argv[],
        // an ID number (0 to 255), prefix to look for and its size,
        // then you can call GetArg() if the function doesn't return (-n).
char FindArg(int argc, char* argv[], unsigned char id, const char* prefix, char PrefixSize) {

        // Prevent buffer overflows, or a weird situation.
    if(argc > (MAX_ARGUMENT_COUNT + 1) || argc == 0) {
        return -2;
    }

        // 'char i' is used to get a specified pointer to a argv.
        // we don't need to check argv[0], because that's
        // usually the command ran to start this program, that's
        // why it's initialized with a 1.
    unsigned char i {1};

    bool FoundArgv {0};

        // Everytime this loop iterates the next argv is checked, after the length of the
        // argument is checked if argv's length matches the argv that is being searched for.
    while(i != argc) {

        char* ArgvDref = argv[i];
        unsigned char n {0};
        int MatchingCharacters {0};
        int CheckArgSize {0};

        while(ArgvDref[CheckArgSize] != 0) {
            CheckArgSize++;
            if(CheckArgSize == MAX_ARGUMENT_VALUE_SIZE) {
                return -1;
            }
        }

        if(CheckArgSize != PrefixSize) {
            i++;
            continue;
        }

        // Everytime this loop iterates, the next character in argv[n] is
        // checked using 'char n'
        while(n != PrefixSize) {

            if(ArgvDref[n] == 0) {
                break;
            }
            if(prefix[n] == ArgvDref[n]) {
                MatchingCharacters++;
            }
            if(MatchingCharacters == PrefixSize) {
                FoundArgv = 1;
                ArgData[ARGC::SavedArguments].id = id;
        // Just don't even try to get a pointer to something that
        // doesn't exist
                if(i + 1 < argc) {
                    ArgData[ARGC::SavedArguments].data = argv[i + 1];
                    ArgData[ARGC::SavedArguments].size = StringSize(argv[i + 1]);
                }
                ARGC::SavedArguments++;
            }
            n++;
        }
        i++;
    }

    if(FoundArgv == 0) {
        return -3;
    }

    return 0;
}


uint8_t FindID(uint8_t id) {

    uint8_t count {0};

    while(count != ARGC::SavedArguments) {
        if(ArgData[count].id == id) {
            break;
        }
        count++;
    }

    if(count == ARGC::SavedArguments) return 0;

    return count;
}


char* GetArgv(uint8_t id) {

    return ArgData[FindID(id)].data;

}


bool CheckArg(uint8_t id) {

    if(FindID(id) == 0) return 0;
    return 1;

}


int GetArgvSize(uint8_t id) {

    return ArgData[FindID(id)].size;

}


