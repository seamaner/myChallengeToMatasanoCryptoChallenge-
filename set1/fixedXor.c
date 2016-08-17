#include <stdio.h>

static unsigned char char2val(unsigned char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return 0;
}

void xor(const char *src1, const char *src2)
{
	char hex[] = "0123456789abcdef";
	unsigned char c1,c2,tmp;
	do {
		c1 = char2val(*src1);
		c2 = char2val(*src2);
		tmp = (c1 ^ c2) & 0x0f;
		printf("%c", hex[tmp]);
	}while(*++src1 && *++src2);
	printf("\n");
}

int main(int rc, void *argc[])
{
	printf("%s\n%s\nXOR:\n", (char*)argc[1], (char*)argc[2]);
	xor((char*)argc[1], (char*)argc[2]);
	return 0;
}
