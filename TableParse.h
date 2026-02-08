#ifndef TABLEPARSE_H
#define TABLEPARSE_H

extern int Tvalue[32];
extern int Tinput[32];
extern int Tsize[32];
extern int Telements;

extern int FilterCharacters(int c);
extern int TRead(char *table_name);
extern int DefTable(int n);

#endif
