/*
 * Copyright (c) 2003 Matteo Frigo
 * Copyright (c) 2003 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Sat Jul  5 21:57:26 EDT 2003 */

#include "codelet-rdft.h"

/* Generated by: /homee/stevenj/cvs/fftw3.0.1/genfft/gen_hc2hc -compact -variables 4 -twiddle-log3 -n 4 -dit -name hf2_4 -include hf.h */

/*
 * This function contains 24 FP additions, 16 FP multiplications,
 * (or, 16 additions, 8 multiplications, 8 fused multiply/add),
 * 21 stack variables, and 16 memory accesses
 */
/*
 * Generator Id's : 
 * $Id: hf2_4.c,v 1.1 2008-10-17 06:12:34 scuri Exp $
 * $Id: hf2_4.c,v 1.1 2008-10-17 06:12:34 scuri Exp $
 * $Id: hf2_4.c,v 1.1 2008-10-17 06:12:34 scuri Exp $
 */

#include "hf.h"

static const R *hf2_4(R *rio, R *iio, const R *W, stride ios, int m, int dist)
{
     int i;
     for (i = m - 2; i > 0; i = i - 2, rio = rio + dist, iio = iio - dist, W = W + 4) {
	  E T1, Tp, Ta, Te, To, Tl, Tk, Th;
	  T1 = rio[0];
	  Tp = iio[-WS(ios, 3)];
	  {
	       E T7, Td, T9, Tc, Tg, Tf, T2, T4, T3, T5, T6, T8;
	       T7 = rio[WS(ios, 2)];
	       Td = iio[-WS(ios, 2)];
	       T9 = iio[-WS(ios, 1)];
	       Tc = rio[WS(ios, 1)];
	       Tg = iio[0];
	       Tf = rio[WS(ios, 3)];
	       T2 = W[2];
	       T4 = W[3];
	       T3 = W[0];
	       T5 = W[1];
	       T6 = FMA(T2, T3, T4 * T5);
	       T8 = FNMS(T4, T3, T2 * T5);
	       Ta = FNMS(T8, T9, T6 * T7);
	       Te = FMA(T3, Tc, T5 * Td);
	       To = FMA(T8, T7, T6 * T9);
	       Tl = FNMS(T4, Tf, T2 * Tg);
	       Tk = FNMS(T5, Tc, T3 * Td);
	       Th = FMA(T2, Tf, T4 * Tg);
	  }
	  {
	       E Tb, Ti, Tn, Tq;
	       Tb = T1 + Ta;
	       Ti = Te + Th;
	       iio[-WS(ios, 2)] = Tb - Ti;
	       rio[0] = Tb + Ti;
	       Tn = Tk + Tl;
	       Tq = To + Tp;
	       rio[WS(ios, 2)] = Tn - Tq;
	       iio[0] = Tn + Tq;
	  }
	  {
	       E Tj, Tm, Tr, Ts;
	       Tj = T1 - Ta;
	       Tm = Tk - Tl;
	       iio[-WS(ios, 3)] = Tj - Tm;
	       rio[WS(ios, 1)] = Tj + Tm;
	       Tr = Th - Te;
	       Ts = Tp - To;
	       rio[WS(ios, 3)] = Tr - Ts;
	       iio[-WS(ios, 1)] = Tr + Ts;
	  }
     }
     return W;
}

static const tw_instr twinstr[] = {
     {TW_COS, 0, 1},
     {TW_SIN, 0, 1},
     {TW_COS, 0, 3},
     {TW_SIN, 0, 3},
     {TW_NEXT, 1, 0}
};

static const hc2hc_desc desc = { 4, "hf2_4", twinstr, {16, 8, 8, 0}, &GENUS, 0, 0, 0 };

void X(codelet_hf2_4) (planner *p) {
     X(khc2hc_dit_register) (p, hf2_4, &desc);
}
