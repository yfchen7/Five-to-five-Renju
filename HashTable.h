
#ifndef HashTable_h
#define HashTable_h
#define HashSize 0x100000
#define mask 0xfffff


struct HashPos
{
	unsigned long long HashVal;
	char mode;
};

extern unsigned long long psunumber[2][225];
extern struct HashPos HashTable[HashSize];

#endif 