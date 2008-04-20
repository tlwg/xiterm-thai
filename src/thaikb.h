/*
 * thaikb.h - Thai keyboard maps
 * Created: 22 Jul 1999 (split from command.c)
 * Author:  Theppitak Karoonboonyanan <thep@links.nectec.or.th>
 */

#ifndef _THAIKB_H
#define _THAIKB_H

#include <X11/Xfuncproto.h>

#define THAI_KB_KETMANEE      0
#define THAI_KB_TIS820_2538   1

_XFUNCPROTOBEGIN

extern void thai_set_keyboard(int thai_kbmode);
extern char thai_map_qwerty(unsigned char c);

_XFUNCPROTOEND

#endif /* whole file */
/*----------------------- end-of-file (C header) -----------------------*/
 
