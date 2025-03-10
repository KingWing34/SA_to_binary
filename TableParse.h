/*
 *
 *
 * Custom table parser
 *
 *
 *
 */

int Tvalue[32];
int Tinput[32];
int Tsize[32];
int Telements = 0;

    //=====================================================
    // Very similar to pre_convert() in main.cpp

int FilterCharacters(int c) {

    // ASCII codes: 32 - space, 10 - new line, 35 - #, 65-86 are A-V, 48-57 are 0-9

    if(c >= 48 && c <= 57) {
        return c - 48;
    }
    if(c >= 65 && c <= 86) {
        return c - 55;
    }
    if(c == EOF) {
        return EOF;
    }
    if(c == 35) {
        return -3;
    }
    if(c == 10) {
        return -4;
    }
    if(c == 32) {
        return -5;
    }
        return -2;
}

    //=====================================================
    // Reads the table file and stores the values in the appropriate array

int TRead() {

    // File related variables

    FILE *table_in;
    char *table_name = argv_get(valid, 9);

    // Check if file can be read

    if ((table_in = fopen(table_name,"rb")) == NULL) {
        std::cout << "ERROR: cannot read table " << table_name << ".\n";
        return 1;
    }

    // More variables for the rest of the code in this function

    int a = 0;
    int count = 0;
    int part = 0;

    // Do some parsing code, uh, I dunno if this is the right way to do it but whatever

    while(a != EOF) {

        // Skip to new line if the character is a "#"

        if(a == -3) {
            while(a != -4 && a != EOF) {
                a = fgetc(table_in);
                a = FilterCharacters(a);
            }
        }

        // Get a character

        a = fgetc(table_in);
        a = FilterCharacters(a);

        // Put the first element from the table into Tinput[] if it doesn't already exist

        if(a >= 0 && part == 0) {
            count = 0;
            while(count < Telements) {
                if(a == Tinput[count]) {
                    std::cout << "ERROR: Duplicate input character\n";
                    return 1;
                }
                count ++;
            }
            Tinput[Telements] = a;
            Tsize[Telements] = 0;
            Tvalue[Telements] = 0;
            a = fgetc(table_in);
            a = FilterCharacters(a);
            part = 1;
        }

        // Make sure that there is at least 1 space before the next element or get another character

        if(a == -5 && part == 1) {
            while(a < 0 && a != EOF) {
                a = fgetc(table_in);
                a = FilterCharacters(a);
            }
            part = 2;
        } else if(part == 1) {
            std::cout << "ERROR: No space or invalid character\n";
            return 1;
        }

        // Put the second element from the table into Tvalue

        if((a == 0 || a == 1) && part == 2) {
            while(a == 0 || a == 1) {
                Tvalue[Telements] = (Tvalue[Telements] << 1) | a ;
                Tsize[Telements]++;
                if(Tsize[Telements] > 8) {
                    std::cout << "ERROR: More than 8 output bits\n";
                    return 1;
                }
                a = fgetc(table_in);
                a = FilterCharacters(a);
            }
        }
        if((a == EOF || a == -4) && part == 2) {
            part = 0;
            Telements++;
        } else if(part == 2 && a != -3) {
            std::cout << "ERROR: invalid character\n";
            return 1;
        }
    }

    std::cout << "Table elements: ";
    printf("%d\n", Telements);

    count = 0;
    std::cout << "Table input,output,size (dec): \n";
    while(count < Telements) {
        printf("%d", Tinput[count]);
        printf(",%d", Tvalue[count]);
        printf(",%d\n", Tsize[count]);
        count++;
    }

    // Close file and exit

    fclose(table_in);
    return 0;
}
    //=====================================================
    // Makes the default table

int DefTable(int n) {

    unsigned char i = 0b10000000;
    int count = 0;
    int size = 0;

    while(((i >> size) | (n - 1)) > (n - 1)) size++;
    size = 8 - size;

    while(count < n) {
        Tvalue[count] = count;
        Tinput[count] = count;
        Tsize[count] = size;
        count++;
    }

    Telements = count;

    return 0;
}
