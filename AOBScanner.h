#ifndef AOBSCANNER_H
#define AOBSCANNER_H
#include <Windows.h>
#include <stdio.h>
//AOB Scanning Class
// WOOT! :D

class AOB
{
public:
    AOB();
    ~AOB();
    int Size;
    BYTE *Bytes;
    BYTE *Mask;
    BYTE *FoundAddress;
    BYTE *FoundPointer;
    long OffsetForPointer; //if it is a pointer/offset being searched for
    DWORD SizeForPointer;  //size of pointer/offset to grab.
};

class AOBScanner
{
private:
    int IsHexChar(char hexChar);
    AOB *ConvertToByteArray(char *TextRepresentation);

public:
    BYTE *RegionBegin;
    BYTE *RegionEnd;
    AOBScanner(uintptr_t beginScan, uintptr_t endScan);
    BYTE *Scan(AOB *FindAOB);
    BYTE *Scan(const char *bytes);
    BYTE *ScanPointer(long offsetforpointer, char *bytes);
    BYTE *ScanPointer(long offsetforpointer, DWORD sizeforpointer, char *bytes);
};

#endif