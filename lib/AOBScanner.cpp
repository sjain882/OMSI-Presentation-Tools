#include "AOBScanner.h"

//AOB Scanning Class
// WOOT! :D

AOB::AOB()
{
	Size=0;
	Bytes=new BYTE[100];
	Mask=new BYTE[100];
	FoundAddress=0;
	FoundPointer=0;
	OffsetForPointer=0;
	SizeForPointer=4; //default is dword

	if(Bytes)
		ZeroMemory(Bytes,100);
	if(Mask)
		ZeroMemory(Mask,100);
}

AOB::~AOB()
{
	if(Bytes)
		delete Bytes;
	if(Mask)
		delete Mask;
}

AOBScanner::AOBScanner(uintptr_t beginScan=0x00401000,uintptr_t endScan=0xFFFFFFFF)
{
	RegionBegin=(BYTE*)beginScan;
	RegionEnd=(BYTE*)endScan;
}

int AOBScanner::IsHexChar(char hexChar)
{
	if(hexChar>=0x30&&hexChar<=0x39||hexChar>=0x61&&hexChar<=0x66||hexChar>=0x41&&hexChar<=0x46)
		return 1; //it is a hex character... 0-9/a-f/A-F
	else
		return 0;
}

AOB* AOBScanner::ConvertToByteArray(char *TextRepresentation) //In here, we go from hex bytes string to binary byte array... ;)
{
	int TextSize=strlen(TextRepresentation);
	int ao=0;
	long int binarybyte;
	char twobytes[3];

	AOB *NewAOB=new AOB;
	if(NewAOB)
	{
		for(int i=0; i<TextSize; i++)
		{
			while(TextRepresentation[i]==0x20 && i<TextSize) //skip spaces
				i++;
			if(i>=(TextSize-1)) //end of string
				break;

			//support both variations, single ? or double ??, single x or double xx
			if((TextRepresentation[i]=='?' && TextRepresentation[i+1]=='?') || (TextRepresentation[i]=='x' && TextRepresentation[i+1]=='x')) 
			{
				NewAOB->Bytes[ao]=00; //just a null byte, doesn't matter what it is since we aren't checking it
				NewAOB->Mask[ao++]=01; //for mask, 01 == skip checking this byte; 00 == check this byte
				i++;
			}
			else if(TextRepresentation[i]=='?' || TextRepresentation[i]=='x')
			{
				NewAOB->Bytes[ao]=00;
				NewAOB->Mask[ao++]=01;
			}
			else if(IsHexChar(TextRepresentation[i])&&IsHexChar(TextRepresentation[i+1])) //0-9/a-f/A-F
			{
				//The hex string representation of a byte, requires two bytes.
				twobytes[0]=TextRepresentation[i];
				twobytes[1]=TextRepresentation[i+1];
				twobytes[2]=0;
				binarybyte=strtoul(twobytes,0,16);
				NewAOB->Bytes[ao++]=binarybyte;

				//printf("NewAOB->Bytes: %p\n",NewAOB->Bytes);
			}
		}

		NewAOB->Size=ao;
	}

	return NewAOB;
}

BYTE* AOBScanner::Scan(AOB *FindAOB)
{
	int CorrectBytes=0;
	BYTE *Ptr;

	for(BYTE *i=RegionBegin; i<RegionEnd; i++)
	{
		if(i==FindAOB->Bytes) i++; //(Dont locate our own AOB that we're using to scan for the address of the real one lol :))
		if(IsBadReadPtr(i,1)!=0)
		{
			//Don't infinite loop by overflowing back to zero before continuing... add the right amount to end the loop...
			DWORD nearRegionEnd=RegionEnd-i;
			if(nearRegionEnd<0x1000)
				i+=nearRegionEnd-1;
			else
				i+=0xFFF;
			continue;
		}
		for(int a=0; a<FindAOB->Size; a++)
		{
			if(FindAOB->Mask[a]==1)
				goto CheckCorrect;

			if(i>RegionEnd)
				break;

			if(*i==FindAOB->Bytes[a])
			{
				CheckCorrect:
				CorrectBytes++;
				//printf("Checking: %p for: %x, correct bytes: %x\n",i,FindAOB->Bytes[a],CorrectBytes);
				if(CorrectBytes==FindAOB->Size)
				{
					if(FindAOB->OffsetForPointer==0) //just getting a regular address not extracting pointer or offset from a found address...
					{
						FindAOB->FoundAddress=i-a;
						return FindAOB->FoundAddress;
					}
					else //It's a pointer were locating..	.
					{
						FindAOB->FoundAddress=i-a;
						Ptr=FindAOB->FoundAddress;

						//Rather than just locating a piece of code... we are locating
						//a piece of code, then grabbing a value from an instruction like
						//mov eax,[PointerOfInterest] // or
						//mov eax,[ebx+OffsetOfInterest]

						//grab it out of there! (here's where that offset comes in handy!)
						memcpy(&FindAOB->FoundPointer,&Ptr[FindAOB->OffsetForPointer],FindAOB->SizeForPointer);
						return FindAOB->FoundPointer;
					}
				}
				i++;
			}
			else
			{
				CorrectBytes=0;
				break;
			}
		}
	}

	return 0;
}

BYTE* AOBScanner::Scan(const char *bytes)
{
	AOB *NewAOB=ConvertToByteArray((char*)bytes);
	BYTE *FoundAddr=0;
	if(NewAOB)
	{
		FoundAddr=Scan(NewAOB);
		delete NewAOB;
	}

	return FoundAddr;
}

BYTE* AOBScanner::ScanPointer(long offsetforpointer,char *bytes)
{
	AOB *NewAOB=ConvertToByteArray(bytes);
	BYTE *FoundAddr=0;

	if(NewAOB)
	{
		NewAOB->OffsetForPointer=offsetforpointer;
		FoundAddr=Scan(NewAOB);
		delete NewAOB;
	}

	return FoundAddr;
}

BYTE* AOBScanner::ScanPointer(long offsetforpointer,DWORD sizeforpointer,char *bytes)
{
	AOB *NewAOB=ConvertToByteArray(bytes);
	BYTE *FoundAddr=0;
	if(NewAOB)
	{
		if(sizeforpointer>4)
			sizeforpointer=4;

		NewAOB->OffsetForPointer=offsetforpointer;
		NewAOB->SizeForPointer=sizeforpointer;
		FoundAddr=Scan(NewAOB);

		delete NewAOB;
	}
	return FoundAddr;
}