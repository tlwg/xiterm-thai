#ifndef _THAI_H
#define _THAI_H

typedef unsigned char text_t;
typedef unsigned int rend_t;

int thai_compare(text_t *d, text_t *s, 
		 rend_t *dr, rend_t *sr,
		 int *result, int *mcol, int *mcolcount);

int thai_isupper(unsigned char c);
int thai_level(unsigned char c);

int ThaiCol2Pixel(int c, unsigned char *start);
int ThaiWidth2Pixel (int c, unsigned char *start);
int ThaiPixel2Col(int x, int y);
int ThaiPixel2Col2(int x, int y);

#endif /* _THAI_H */

