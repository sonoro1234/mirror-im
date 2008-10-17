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
/* Generated on Sat Jul  5 21:29:55 EDT 2003 */

#include "codelet-dft.h"

/* Generated by: /homee/stevenj/cvs/fftw3.0.1/genfft/gen_twiddle -compact -variables 4 -n 6 -name t1_6 -include t.h */

/*
 * This function contains 46 FP additions, 28 FP multiplications,
 * (or, 32 additions, 14 multiplications, 14 fused multiply/add),
 * 23 stack variables, and 24 memory accesses
 */
/*
 * Generator Id's : 
 * $Id: t1_6.c,v 1.1 2008-10-17 06:11:09 scuri Exp $
 * $Id: t1_6.c,v 1.1 2008-10-17 06:11:09 scuri Exp $
 * $Id: t1_6.c,v 1.1 2008-10-17 06:11:09 scuri Exp $
 */

#include "t.h"

static const R *t1_6(R *ri, R *ii, const R *W, stride ios, int m, int dist)
{
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     int i;
     for (i = m; i > 0; i = i - 1, ri = ri + dist, ii = ii + dist, W = W + 10) {
	  E T7, TS, Tv, TO, Tt, TJ, Tx, TF, Ti, TI, Tw, TC;
	  {
	       E T1, TN, T6, TM;
	       T1 = ri[0];
	       TN = ii[0];
	       {
		    E T3, T5, T2, T4;
		    T3 = ri[WS(ios, 3)];
		    T5 = ii[WS(ios, 3)];
		    T2 = W[4];
		    T4 = W[5];
		    T6 = FMA(T2, T3, T4 * T5);
		    TM = FNMS(T4, T3, T2 * T5);
	       }
	       T7 = T1 - T6;
	       TS = TN - TM;
	       Tv = T1 + T6;
	       TO = TM + TN;
	  }
	  {
	       E Tn, TD, Ts, TE;
	       {
		    E Tk, Tm, Tj, Tl;
		    Tk = ri[WS(ios, 4)];
		    Tm = ii[WS(ios, 4)];
		    Tj = W[6];
		    Tl = W[7];
		    Tn = FMA(Tj, Tk, Tl * Tm);
		    TD = FNMS(Tl, Tk, Tj * Tm);
	       }
	       {
		    E Tp, Tr, To, Tq;
		    Tp = ri[WS(ios, 1)];
		    Tr = ii[WS(ios, 1)];
		    To = W[0];
		    Tq = W[1];
		    Ts = FMA(To, Tp, Tq * Tr);
		    TE = FNMS(Tq, Tp, To * Tr);
	       }
	       Tt = Tn - Ts;
	       TJ = TD + TE;
	       Tx = Tn + Ts;
	       TF = TD - TE;
	  }
	  {
	       E Tc, TA, Th, TB;
	       {
		    E T9, Tb, T8, Ta;
		    T9 = ri[WS(ios, 2)];
		    Tb = ii[WS(ios, 2)];
		    T8 = W[2];
		    Ta = W[3];
		    Tc = FMA(T8, T9, Ta * Tb);
		    TA = FNMS(Ta, T9, T8 * Tb);
	       }
	       {
		    E Te, Tg, Td, Tf;
		    Te = ri[WS(ios, 5)];
		    Tg = ii[WS(ios, 5)];
		    Td = W[8];
		    Tf = W[9];
		    Th = FMA(Td, Te, Tf * Tg);
		    TB = FNMS(Tf, Te, Td * Tg);
	       }
	       Ti = Tc - Th;
	       TI = TA + TB;
	       Tw = Tc + Th;
	       TC = TA - TB;
	  }
	  {
	       E TG, Tu, Tz, TR, TT, TU;
	       TG = KP866025403 * (TC - TF);
	       Tu = Ti + Tt;
	       Tz = FNMS(KP500000000, Tu, T7);
	       ri[WS(ios, 3)] = T7 + Tu;
	       ri[WS(ios, 1)] = Tz + TG;
	       ri[WS(ios, 5)] = Tz - TG;
	       TR = KP866025403 * (Tt - Ti);
	       TT = TC + TF;
	       TU = FNMS(KP500000000, TT, TS);
	       ii[WS(ios, 1)] = TR + TU;
	       ii[WS(ios, 3)] = TT + TS;
	       ii[WS(ios, 5)] = TU - TR;
	  }
	  {
	       E TK, Ty, TH, TQ, TL, TP;
	       TK = KP866025403 * (TI - TJ);
	       Ty = Tw + Tx;
	       TH = FNMS(KP500000000, Ty, Tv);
	       ri[0] = Tv + Ty;
	       ri[WS(ios, 4)] = TH + TK;
	       ri[WS(ios, 2)] = TH - TK;
	       TQ = KP866025403 * (Tx - Tw);
	       TL = TI + TJ;
	       TP = FNMS(KP500000000, TL, TO);
	       ii[0] = TL + TO;
	       ii[WS(ios, 4)] = TQ + TP;
	       ii[WS(ios, 2)] = TP - TQ;
	  }
     }
     return W;
}

static const tw_instr twinstr[] = {
     {TW_FULL, 0, 6},
     {TW_NEXT, 1, 0}
};

static const ct_desc desc = { 6, "t1_6", twinstr, {32, 14, 14, 0}, &GENUS, 0, 0, 0 };

void X(codelet_t1_6) (planner *p) {
     X(kdft_dit_register) (p, t1_6, &desc);
}
