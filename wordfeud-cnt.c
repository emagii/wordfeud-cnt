#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>		/* size_t */

ESC = 0xC3;
#define	_AA 0x85
#define	_AE 0x84
#define	_OE 0x96

int	keys = 0;
int	chartab[256];
int	charcnt[256] = {
	['A'] = 9,
	['B'] = 2,
	['C'] = 1,
	['D'] = 5,
	['E'] = 8,
	['F'] = 2,
	['G'] = 3,
	['H'] = 2,
	['I'] = 5,
	['J'] = 1,
	['K'] = 3,
	['L'] = 5,
	['M'] = 3,
	['N'] = 6,
	['O'] = 6,
	['P'] = 2,
	['R'] = 8,
	['S'] = 8,
	['T'] = 9,
	['U'] = 3,
	['V'] = 2,
	['X'] = 1,
	['Y'] = 1,
	['Z'] = 1,
	[_AA] = 2,	// Ä
	[_AE] = 2,	// Å
	[_OE] = 2,	// Ö
	['*'] = 2
};
#if 0
char charimage[256];
#endif

void test()
{
	int	c = '.';
	int	i = 0;
	while ((c = getchar()) != EOF) {
		if (((c >= 'A') && (c <= 'Z')) || (c == '*')) {
			putchar(c);
			chartab[c]++;
			keys++;

		} else if (c == ESC) {
			c = getchar();
			switch (c) {
		  	case _AA:	// 'Å':
		  	case _AE:	// 'Ä':
		  	case _OE:	// 'Ö':
				putchar(ESC);
				putchar(c);
				chartab[c]++;
				keys++;
		  		break;
			default:
			  	break;
			}
		} else {
			putchar(c);
		}	  
	}
}


int main(void)
{
	int remainder;

	test();

	printf("\nKeys: %d\n\n", keys);
#if	0
	for (int i = 0; i < 256 ; i++) {
		charimage[i] = i;
	}
	charimage[_AA] = 'Ä';
#endif
	keys = 0;
	for (int i = 0; i < 256 ; i++) {
		keys += chartab[i];
		if (charcnt[i] != 0) {
			
			printf("['");
			if (i & 0x80)
				putchar(ESC);
			printf("%c']", i);
			printf(" = %d (MAX(%d))", chartab[i], charcnt[i]);
			if(chartab[i] > charcnt[i]) {
				printf("*");
			} else {
				printf(" ");
			}
			if(chartab[i] < charcnt[i]) {
				remainder = charcnt[i] - chartab[i];
				printf("REMAINING %d", remainder);
			}
			printf("\n");
		}
	}
	printf("\nRemaining characters: ");
	for (int i = 0; i < 256 ; i++) {
		int count = (charcnt[i] - chartab[i]);
		while (count > 0) {
			if (i & 0x80)
				putchar(ESC);
			putchar(i);
			count--;
		}
	}
	printf("\n");
	exit(0);
}
