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
/* Generated on Sat Jul  5 22:12:11 EDT 2003 */

#include "codelet-rdft.h"

/* Generated by: /homee/stevenj/cvs/fftw3.0.1/genfft/gen_hc2r -compact -variables 4 -sign 1 -n 15 -name hc2rIII_15 -dft-III -include hc2rIII.h */

/*
 * This function contains 64 FP additions, 26 FP multiplications,
 * (or, 49 additions, 11 multiplications, 15 fused multiply/add),
 * 47 stack variables, and 30 memory accesses
 */
/*
 * Generator Id's : 
 * $Id: hc2rIII_15.c,v 1.1 2008-10-17 06:12:08 scuri Exp $
 * $Id: hc2rIII_15.c,v 1.1 2008-10-17 06:12:08 scuri Exp $
 * $Id: hc2rIII_15.c,v 1.1 2008-10-17 06:12:08 scuri Exp $
 */

#include "hc2rIII.h"

static void hc2rIII_15(const R *ri, const R *ii, R *O, stride ris, stride iis, stride os, int v, int ivs, int ovs)
{
     DK(KP1_732050807, +1.732050807568877293527446341505872366942805254);
     DK(KP433012701, +0.433012701892219323381861585376468091735701313);
     DK(KP968245836, +0.968245836551854221294816349945599902708230426);
     DK(KP587785252, +0.587785252292473129168705954639072768597652438);
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DK(KP1_647278207, +1.647278207092663851754840078556380006059321028);
     DK(KP1_018073920, +1.018073920910254366901961726787815297021466329);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DK(KP2_000000000, +2.000000000000000000000000000000000000000000000);
     DK(KP1_118033988, +1.118033988749894848204586834365638117720309180);
     DK(KP1_175570504, +1.175570504584946258337411909278145537195304875);
     DK(KP1_902113032, +1.902113032590307144232878666758764286811397268);
     int i;
     for (i = v; i > 0; i = i - 1, ri = ri + ivs, ii = ii + ivs, O = O + ovs) {
	  E Tv, TD, T5, Ts, TC, T6, Tf, TW, TK, Td, Tg, TP, To, TN, TA;
	  E TO, TQ, Tt, Tu, T12, Te, T11;
	  Tt = ii[WS(iis, 4)];
	  Tu = ii[WS(iis, 1)];
	  Tv = FMA(KP1_902113032, Tt, KP1_175570504 * Tu);
	  TD = FNMS(KP1_175570504, Tt, KP1_902113032 * Tu);
	  {
	       E T1, T4, Tq, T2, T3, Tr;
	       T1 = ri[WS(ris, 7)];
	       T2 = ri[WS(ris, 4)];
	       T3 = ri[WS(ris, 1)];
	       T4 = T2 + T3;
	       Tq = KP1_118033988 * (T2 - T3);
	       T5 = FMA(KP2_000000000, T4, T1);
	       Tr = FNMS(KP500000000, T4, T1);
	       Ts = Tq + Tr;
	       TC = Tr - Tq;
	  }
	  {
	       E Tc, TJ, T9, TI;
	       T6 = ri[WS(ris, 2)];
	       {
		    E Ta, Tb, T7, T8;
		    Ta = ri[WS(ris, 3)];
		    Tb = ri[WS(ris, 6)];
		    Tc = Ta + Tb;
		    TJ = Ta - Tb;
		    T7 = ri[0];
		    T8 = ri[WS(ris, 5)];
		    T9 = T7 + T8;
		    TI = T7 - T8;
	       }
	       Tf = KP559016994 * (T9 - Tc);
	       TW = FNMS(KP1_647278207, TJ, KP1_018073920 * TI);
	       TK = FMA(KP1_647278207, TI, KP1_018073920 * TJ);
	       Td = T9 + Tc;
	       Tg = FNMS(KP250000000, Td, T6);
	  }
	  {
	       E Tn, TM, Tk, TL;
	       TP = ii[WS(iis, 2)];
	       {
		    E Tl, Tm, Ti, Tj;
		    Tl = ii[WS(iis, 3)];
		    Tm = ii[WS(iis, 6)];
		    Tn = Tl - Tm;
		    TM = Tl + Tm;
		    Ti = ii[0];
		    Tj = ii[WS(iis, 5)];
		    Tk = Ti + Tj;
		    TL = Ti - Tj;
	       }
	       To = FMA(KP951056516, Tk, KP587785252 * Tn);
	       TN = KP968245836 * (TL - TM);
	       TA = FNMS(KP587785252, Tk, KP951056516 * Tn);
	       TO = TL + TM;
	       TQ = FMA(KP433012701, TO, KP1_732050807 * TP);
	  }
	  T12 = KP1_732050807 * (TP - TO);
	  Te = T6 + Td;
	  T11 = Te - T5;
	  O[0] = FMA(KP2_000000000, Te, T5);
	  O[WS(os, 10)] = T12 - T11;
	  O[WS(os, 5)] = T11 + T12;
	  {
	       E TE, TG, TB, TF, TY, T10, Tz, TX, TV, TZ;
	       TE = TC - TD;
	       TG = TC + TD;
	       Tz = Tg - Tf;
	       TB = Tz + TA;
	       TF = TA - Tz;
	       TX = TN + TQ;
	       TY = TW - TX;
	       T10 = TW + TX;
	       O[WS(os, 12)] = FMA(KP2_000000000, TB, TE);
	       O[WS(os, 3)] = FMS(KP2_000000000, TF, TG);
	       TV = TE - TB;
	       O[WS(os, 2)] = TV + TY;
	       O[WS(os, 7)] = TY - TV;
	       TZ = TF + TG;
	       O[WS(os, 8)] = TZ - T10;
	       O[WS(os, 13)] = -(TZ + T10);
	  }
	  {
	       E Tw, Ty, Tp, Tx, TS, TU, Th, TR, TH, TT;
	       Tw = Ts - Tv;
	       Ty = Ts + Tv;
	       Th = Tf + Tg;
	       Tp = Th + To;
	       Tx = Th - To;
	       TR = TN - TQ;
	       TS = TK + TR;
	       TU = TR - TK;
	       O[WS(os, 9)] = -(FMA(KP2_000000000, Tp, Tw));
	       O[WS(os, 6)] = FMA(KP2_000000000, Tx, Ty);
	       TH = Tx - Ty;
	       O[WS(os, 11)] = TH - TS;
	       O[WS(os, 1)] = TH + TS;
	       TT = Tw - Tp;
	       O[WS(os, 4)] = TT - TU;
	       O[WS(os, 14)] = TT + TU;
	  }
     }
}

static const khc2r_desc desc = { 15, "hc2rIII_15", {49, 11, 15, 0}, &GENUS, 0, 0, 0, 0, 0 };

void X(codelet_hc2rIII_15) (planner *p) {
     X(khc2rIII_register) (p, hc2rIII_15, &desc);
}
