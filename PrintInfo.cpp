#include <cstdio>
#include <map>

const std::map<int, const char*> ERR_TO_STR = {
    { 0, "Type should be 2-32" },
    { 1, "Shift should be 1-7" },
    { 2, "Cannot read file" },
    { 3, "Cannot write file" },
    { 4, "Too many or too long arguments!\n\nCheck help!" },
    { 5, "Unable to parse table, stopped at element: %d" },
    { 6, "Cannot read table" },
    { 7, "Duplicate input character" },
    { 8, "No space or invalid character" },
    { 9, "More than 8 output bits" },
    { 10, "Invalid character" }
};

const std::map<int, const char*> INFO_TO_STR = {
    { 0, "Converting as: %d" },
    { 1, "Shift output by: %d" },
    { 2, "Table elements: %d" },
    { 3, "Table input,output,size (dec):" }
};

void PrintError(int n) {

    printf("%s", "\033[1;31mERROR: ");
    printf("%s", ERR_TO_STR.at(n));
    printf("%s\n", "!\033[0m");

}

void PrintInfo(int n) {

    printf("%s\n", INFO_TO_STR.at(n));

}

// type == 0 is for int, and 1 for char (not used here.. yet!)
void PrintErrWithVariable(int n, bool type, void* varA) {

    if(type == 0) {
	printf(ERR_TO_STR.at(n), *(int*)varA);
    } else {
	printf(ERR_TO_STR.at(n), *(char*)varA);
    }
    printf("\n");

}

// type == 0 is for int, and 1 for strings (not used here.. yet!)
void PrintInfoWithVariable(int n, bool type, void* varA) {

    if(type == 0) {
	printf(INFO_TO_STR.at(n), *(int*)varA);
    } else {
	printf(INFO_TO_STR.at(n), *(char*)varA);
    }
    printf("\n");

}
