/*--------------------------------*-C-*---------------------------------*
 * File:	graphics.c
 *
 * This module is all new by Rob Nation
 * <nation@rocket.sanders.lockheed.com>
 *
 * Modifications by mj olesen <olesen@me.QueensU.CA>
 * and Raul Garcia Garcia <rgg@tid.es>
 *----------------------------------------------------------------------*/
/*{{{ includes, defines */
#include "main.h"

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <X11/cursorfont.h>

#include "command.h"		/* for tt_printf() */
#include "debug.h"
#include "graphics.h"
#include "screen.h"

/* commands:
 * 'C' = Clear
 * 'F' = Fill
 * 'G' = Geometry
 * 'L' = Line
 * 'P' = Points
 * 'T' = Text
 * 'W' = Window
 */

#ifndef GRX_SCALE
#define GRX_SCALE	10000
#endif
/*}}} */
/* extern functions referenced */
/* extern variables referenced */
/* extern variables declared here */

