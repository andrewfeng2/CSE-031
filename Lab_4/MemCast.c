#include <stdio.h>

int main() {
	int i;
	int four_ints[4];
	char* four_c;

	for(i = 0; i < 4; i++)
        four_ints[i] = 2;

	printf("%x\n", four_ints[0]);
	
    four_c = (char*)four_ints;

	for(i = 0; i < 4; i++)
        four_c[i] = 'A' + i; // ASCII value of 'A' is 65 or 0x41 in Hex.
    
    // Add your code for the exercises here:
    printf("%x\n", four_ints[0]);
    printf("%x\n", four_ints[1]);
	
    printf("four_ints: %p\n", (void*)four_ints);
    printf("four_c: %p\n", (void*)four_c);

	for (i = 0; i < 4; i++) {
        printf("four_ints[%d]: address = %p, value = 0x%x\n", 
               i, (void*)&four_ints[i], four_ints[i]);
    }
    

    for (i = 0; i < 16; i++) {  // We use 16 here because four_c points to the same 16 bytes as four_ints
        printf("four_c[%d]: address = %p, value = 0x%02x\n", 
               i, (void*)&four_c[i], (unsigned char)four_c[i]);
    }
    
	return 0;
}