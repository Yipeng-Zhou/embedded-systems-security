#include <stdio.h>

int main(void)
{
	const unsigned int key = 0x42424242;
	unsigned int buf[9] = {0x48F20112, 0xC4F60202, 0x48F28001, 0xA2F80F10, 0x0321D170, 0x40F20531, 0XC0F60001, 0X0847FFFF, 0xFFFFFFFF};
	for(int i=0; i<9; i++)
	{
		buf[i] ^= key;
		printf("%08x\n",buf[i]);
	}
}
