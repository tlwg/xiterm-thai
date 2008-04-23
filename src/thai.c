#include "main.h"
#include "thai.h"

static unsigned char movetab[] = {
 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, /* 00..0F */
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, /* 10..1F */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 20..2F */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 30..3F */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 40..4F */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 50..5F */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 60..6F */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 70..7F */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 80..8F */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 90..9F */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* A0..AF */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* B0..BF */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* C0..CF */
 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, /* D0..DF */
 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, /* E0..EF */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* F0..FF */
};

extern text_t *drawn_text;
int thai_spcount = 2;

static int thai_colinc(unsigned char c, int *udcount, int *spcount)
{
  int ret=0;

  if(c==0) /* Initialize */
     *udcount=*spcount=0;
  else {
    if(!movetab[c]) {
      ret = 1;
      if(c == ' ') {
	(*spcount)++;
	if(*spcount == thai_spcount) {
	  *spcount = 0;
	  ret += *udcount;
	  *udcount = 0;
	}
      }
      else {
	*spcount = 0;
      }
    }
    else {
      (*udcount)++;
      *spcount = 0;
      ret = 0; 
    }
  }
  return ret;
}

static int thai_colinc1(unsigned char c)
{
  static int ud1,sp1;
  return thai_colinc(c,&ud1,&sp1);
}

static int thai_colinc2(unsigned char c)
{
  static int ud2,sp2;
  return thai_colinc(c,&ud2,&sp2);
}

static int thaistrlen(unsigned char *from, unsigned char *to)
{
  int j;

  j=0;
  if(thai_spcount) {
    thai_colinc1(0);
    while(from!=to) {
      j+= thai_colinc1(*from);
      from++;
    }
  }
  else {
    while(from!=to) {
      if(!movetab[*from]) j++;
      from++;
    }
  }
  return j;
}

int thai_compare(text_t *d, text_t *s, 
		 rend_t *dr, rend_t *sr,
		 int *result, int *mcol, int *mcolcount)
{
  int i, j, len;
  int col[TermWin.ncol+1];
  unsigned int col_d [2*TermWin.ncol+4];
  unsigned int col_s [2*TermWin.ncol+4];
  int ptr_d, ptr_s, ptr;
  int s1, s2;

  /* Column starts from 1 ... 80  (not 0 ... 79) */
  /* Use 2 bytes/column */
  *mcolcount = 0;

  i=2*TermWin.ncol+4;
  while(i>0) {
    i--;
    col_d[i]=col_s[i]=0;
  }

  /* Convert string into Thai columns */
  len = ptr_d = ptr_s = 0;
  thai_colinc1(0);
  thai_colinc2(0);

  mcol [ TermWin.ncol ] = 0;
  for(i=0;i<TermWin.ncol;i++) {
    result[i] = 0;
    mcol[i] = 0;
    s1 = thai_colinc1(s[i]);
    len += s1;
    ptr_s += s1*2;
    if(!movetab[s[i]]) {
      col_s[ptr_s] = s[i] + sr[i];
    }
    else {
      col_s[ptr_s+1] += s[i] + sr[i];
    }
    col[i] = len;

    s2 = thai_colinc2(d[i]);
    ptr_d += s2*2;
    if(!movetab[d[i]]) {
      col_d[ptr_d] = d[i] + dr[i];
    }
    else {
      col_d[ptr_d+1] += d[i] + dr[i];
    }
  }

  for(i=1,ptr=2;i<=TermWin.ncol;i++,ptr+=2) {
    if((col_d[ptr] != col_s[ptr]) ||  
       (col_d[ptr+1] != col_s[ptr+1])) {
      mcol[i] = 1; 
      (*mcolcount)++;
    }
    else if( !col_s[ptr] ) { /* No Data : Necessary to clear cursor */
      mcol[i] = 1; 
      (*mcolcount)++;
    }
  }

  for(i=0;i<TermWin.ncol;i++) {
    if((j = mcol[col[i]])!=0) {
      result[i] = 1;
      if(j==1) {
	(*mcolcount)--;
	mcol[col[i]] = 2;
      }
    }
  }
  return len;
}

int thai_isupper(unsigned char c)
{
  return movetab[c];
}

static int levtable[] = {
  0,2,0,0,2,2,2,2,1,1,1,2,0,0,0,0,
  0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

int thai_level(unsigned char c)
{
  return  (c>0xD0)?levtable[c-0xd0]:0;
}


/* int ThaiCol2Pixel(c, &screen.text[roffset]); */
int ThaiCol2Pixel(int c, unsigned char *start)
{
  return thaistrlen(start, start+c)*TermWin.fwidth + TermWin_internalBorder;
}

/* ThaiWidth2Pixel (count,start_text), Height2Pixel (1), 0) */
int ThaiWidth2Pixel (int c, unsigned char *start)
{
  return thaistrlen(start, start+c)*TermWin.fwidth;
}

int ThaiPixel2Col(int x, int y)
{
  int doffset = Pixel2Row(y) * (TermWin.ncol + 1);
  unsigned char *start = &drawn_text[doffset];
  int col=0, cx=0;
  x -= TermWin_internalBorder;
  if(thai_spcount) {
    thai_colinc1(0);
    while(cx<=x) {
      cx += TermWin.fwidth * thai_colinc1(start[col]);
      col++;
    }
  }
  else {
    while(cx<=x) {
      if(!movetab[start[col]])
	cx += TermWin.fwidth;
      col++;
    }
  }
  return col-1;
}

int ThaiPixel2Col2(int x, int y)
{
  int doffset = Pixel2Row(y) * (TermWin.ncol + 1);
  unsigned char *start = &drawn_text[doffset];
  int col=0, cx=0;
  x -= TermWin_internalBorder;
  if(thai_spcount) {
    thai_colinc1(0);
    while(cx<=x) {
      cx += TermWin.fwidth * thai_colinc1(start[col]);
      col++;
    }
  }
  else {
    while(cx<=x) {
      if(!movetab[start[col]])
	cx += TermWin.fwidth;
      col++;
    }
  }

  while(movetab[start[col]] && col < TermWin.ncol)
    col++;
  return col-1;
}

