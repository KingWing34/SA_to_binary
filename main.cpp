#include <iostream>
#include <cstdlib>
#include "PrintInfo.h"
#include "argv.h"
#include "TableParse.h"

    // TableParse.cpp
int FilterCharacters(int c);
int TRead();
int DefTable(int n);

    // At the bottom of this file to look better
void PrintHelp(char argv[]);


    // Convert ASCII codes
int pre_convert(int c) {

    int i = 0;

    // Return EOF if that's whats given
    if(c == EOF) return EOF;

    // ASCII codes: 65-86 are A-V, 48-57 are 0-9
    if(c >= 48 && c <= 57) {
        c = c - 48;
    } else if(c >= 65 && c <= 86) {
        c = c - 55;
    } else {
        return -2;
    }

    while(i < Telements) {

        if(c == Tinput[i]) {
            c = i;
            break;
        }

        i++;

        if(i == Telements) {
            return -2;
        }
    }

    // Return converter result (0-31 for valid characters, -2 for invalid)
    return c;
}


    // Reverse the bit order
int Rbitorder(char bits) {

    unsigned char i = 0b10000000;
    int rbits = 0;
    int shift = 7;

    while(i > 0) {
        rbits = rbits | (((bits & i) << (7 - shift)) >> shift);
        shift = shift - 1;
        i = i >> 1;
    }

    return rbits;
}


    // Invert bits in a byte
int invert(char i) {

    i =~ i;

    return i;
}


    // This is where this program does its things
int main(int argc, char *argv[]) {

    // If too many arguments, tell user to check help and print help!
    if ( argc > 12) {
        PrintHelp(argv[0]);
        PrintError(4);
        return 1;
    }

    // No arguments, print help
    if ( argc == 1) {
        PrintHelp(argv[0]);
        return 1;
    }

    // Set valid arguments
    argv_set(valid, 0, "-h", argc, argv);
    argv_set(valid, 2, "-s", argc, argv);
    argv_set(valid, 3, "-i", argc, argv);
    argv_set(valid, 5, "-in", argc, argv);
    argv_set(valid, 6, "-out", argc, argv);
    argv_set(valid, 7, "-t", argc, argv);
    argv_set(valid, 8, "-e", argc, argv);
    argv_set(valid, 9, "-Table", argc, argv);

    // Print help and exit if -h argument given
    if(argv_get(valid, 0)[0] == '-') {
        PrintHelp(argv[0]);
        return 1;
    }

    // Read -t (default is 2)
    int n;
    if(argv_get(valid, 7)[0]) {
        n = strtol(argv_get(valid, 7), NULL, 10);
        PrintInfoWithVariable(0, 0, &n);
        if(n < 2 || n > 32) {
            PrintError(0);
            return 1;
        }
    } else {
        n = 2;
    }

    // Parse custom table file or create default table
    if(argv_get(valid, 9)[0]) {
        if(TRead() == 1) {
            PrintInfoWithVariable(5, 0, &Telements);
            return 1;
        }
    } else {
        DefTable(n);
    }

    // read -s (default is 0)
    int s;
    if(argv_get(valid, 2)[0]) {
        s = strtol(argv_get(valid, 2), NULL, 10);
        PrintInfoWithVariable(1, 0, &s);
        if (s < 0 || s > 7) {
            PrintError(1);
            return 1;
        }
    } else {
        s = 0;
    }

    // Manage file I/O
    FILE *fp_in, *fp_out;
    char *in_name = argv_get(valid, 5);
    char *out_name = argv_get(valid, 6);

    // Check if input file is readable
    if ((fp_in = fopen(in_name,"rb")) == NULL) {
		PrintError(2);
		return 1;
    }

    // Check if the -out option is given, then check if output
    // file is writable otherwise make output file using default name
    if(argv_get(valid, 6)[0]) {
        if ((fp_out = fopen(out_name,"w")) == NULL) {
		PrintError(3);
		return 1;
        }
    } else if ((fp_out = fopen("converter_out.bin","w")) == NULL) {
        PrintError(3);
    }

    // Variables used in the converter code below
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int used = s;
    int r = 0;
    int size = 0;

    // Loop until all characters are converted
    while(a != EOF) {
        while(a != EOF && used < 8) {
            a = fgetc(fp_in);
            a = pre_convert(a);
            if(a < 0)
                continue;
            size = Tsize[a];
            a = Tvalue[a];
            r = (r << size) | a;
            used = used + size;
        }
        if(used > 8) {
            c = 0;
            while(d != (used - 8)) {
                c = (c << 1) + 1;
                d++;
            }
            b = r & c;
            r = r >> d;
            used = 8;
        }
        if(a == EOF) {
            r = r << (8 - used);
        }
        if((a == EOF && used != 0) || used == 8) {
            if(argv_get(valid, 8)[0] == '-' ) {
                r = Rbitorder(r);
            }
            if(argv_get(valid, 3)[0] == '-' ) {
                r = invert(r);
            }
            fputc((unsigned char) r, fp_out);
            r = 0;
            used = 0;
        }
        if(d != 0) {
            r = b;
            used = d;
            d = 0;
        }
    }


    // Close files and exit
    fclose(fp_in);
    fclose(fp_out);

    return 0;
}


void PrintHelp(char argv[]) {
    printf(
        "SA to binary converter v1.3\n\n"
        "Usage:\n"
        "%s   -in <file_name>\n"
        "%s   -in <file_name> -out <file_name>\n"
        "%s   [option1] ... [option_n] -in <file_name>\n"
        "%s   [option1] ... [option_n] -in <file_name> -out <file_name>\n\n"
        "Options:\n"
        " -in  <file_name>   File input\n"
        " -out <file_name>   File output\n"
        " -Table <file name> (see github for table format)\n"
        // " -c                 Try all combinations\n" // TODO
        " -e                 Reverse bit order\n"
        " -i                 Invert output\n"
        // " -r                 Rotate conversion table (creates more than one file)\n" //TODO
        " -s <n>             Shift bits (where n is 1-7)\n"
        " -t <n>             Type (where n is 2-32)\n"
        " -h                 Prints this help message\n",
        argv,
        argv,
        argv,
        argv
    );
}

