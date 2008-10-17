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
/* Generated on Sat Jul  5 21:57:06 EDT 2003 */

#include "codelet-rdft.h"

/* Generated by: /homee/stevenj/cvs/fftw3.0.1/genfft/gen_hc2hc -compact -variables 4 -n 12 -dit -name hf_12 -include hf.h */

/*
 * This function contains 118 FP additions, 60 FP multiplications,
 * (or, 88 additions, 30 multiplications, 30 fused multiply/add),
 * 47 stack variables, and 48 memory accesses
 */
/*
 * Generator Id's : 
 * $Id: hf_12.c,v 1.1 2008-10-17 06:12:34 scuri Exp $
 * $Id: hf_12.c,v 1.1 2008-10-17 06:12:34 scuri Exp $
 * $Id: hf_12.c,v 1.1 2008-10-17 06:12:34 scuri Exp $
 */

#include "hf.h"

static const R *hf_12(R *rio, R *iio, const R *W, stride ios, int m, int dist)
{
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     int i;
     for (i = m - 2; i > 0; i = i - 2, rio = rio + dist, iio = iio - dist, W = W + 22) {
	  E T1, T1W, T18, T22, Tc, T15, T1V, T23, TA, T1y, T1j, T1B, TL, T1g, T1z;
	  E T1A, Ti, T1S, T1d, T25, Tt, T1a, T1T, T26, TR, T1E, T1o, T1D, T12, T1l;
	  E T1F, T1G;
	  {
	       E T6, T16, Tb, T17;
	       T1 = rio[0];
	       T1W = iio[-WS(ios, 11)];
	       {
		    E T3, T5, T2, T4;
		    T3 = rio[WS(ios, 4)];
		    T5 = iio[-WS(ios, 7)];
		    T2 = W[6];
		    T4 = W[7];
		    T6 = FMA(T2, T3, T4 * T5);
		    T16 = FNMS(T4, T3, T2 * T5);
	       }
	       {
		    E T8, Ta, T7, T9;
		    T8 = rio[WS(ios, 8)];
		    Ta = iio[-WS(ios, 3)];
		    T7 = W[14];
		    T9 = W[15];
		    Tb = FMA(T7, T8, T9 * Ta);
		    T17 = FNMS(T9, T8, T7 * Ta);
	       }
	       T18 = KP866025403 * (T16 - T17);
	       T22 = KP866025403 * (Tb - T6);
	       Tc = T6 + Tb;
	       T15 = FNMS(KP500000000, Tc, T1);
	       T1V = T16 + T17;
	       T23 = FNMS(KP500000000, T1V, T1W);
	  }
	  {
	       E TK, T1i, TF, T1h;
	       {
		    E Tx, Tz, Tw, Ty;
		    Tx = rio[WS(ios, 3)];
		    Tz = iio[-WS(ios, 8)];
		    Tw = W[4];
		    Ty = W[5];
		    TA = FMA(Tw, Tx, Ty * Tz);
		    T1y = FNMS(Ty, Tx, Tw * Tz);
	       }
	       {
		    E TH, TJ, TG, TI;
		    TH = rio[WS(ios, 11)];
		    TJ = iio[0];
		    TG = W[20];
		    TI = W[21];
		    TK = FMA(TG, TH, TI * TJ);
		    T1i = FNMS(TI, TH, TG * TJ);
	       }
	       {
		    E TC, TE, TB, TD;
		    TC = rio[WS(ios, 7)];
		    TE = iio[-WS(ios, 4)];
		    TB = W[12];
		    TD = W[13];
		    TF = FMA(TB, TC, TD * TE);
		    T1h = FNMS(TD, TC, TB * TE);
	       }
	       T1j = KP866025403 * (T1h - T1i);
	       T1B = KP866025403 * (TK - TF);
	       TL = TF + TK;
	       T1g = FNMS(KP500000000, TL, TA);
	       T1z = T1h + T1i;
	       T1A = FNMS(KP500000000, T1z, T1y);
	  }
	  {
	       E Ts, T1c, Tn, T1b;
	       {
		    E Tf, Th, Te, Tg;
		    Tf = rio[WS(ios, 6)];
		    Th = iio[-WS(ios, 5)];
		    Te = W[10];
		    Tg = W[11];
		    Ti = FMA(Te, Tf, Tg * Th);
		    T1S = FNMS(Tg, Tf, Te * Th);
	       }
	       {
		    E Tp, Tr, To, Tq;
		    Tp = rio[WS(ios, 2)];
		    Tr = iio[-WS(ios, 9)];
		    To = W[2];
		    Tq = W[3];
		    Ts = FMA(To, Tp, Tq * Tr);
		    T1c = FNMS(Tq, Tp, To * Tr);
	       }
	       {
		    E Tk, Tm, Tj, Tl;
		    Tk = rio[WS(ios, 10)];
		    Tm = iio[-WS(ios, 1)];
		    Tj = W[18];
		    Tl = W[19];
		    Tn = FMA(Tj, Tk, Tl * Tm);
		    T1b = FNMS(Tl, Tk, Tj * Tm);
	       }
	       T1d = KP866025403 * (T1b - T1c);
	       T25 = KP866025403 * (Ts - Tn);
	       Tt = Tn + Ts;
	       T1a = FNMS(KP500000000, Tt, Ti);
	       T1T = T1b + T1c;
	       T26 = FNMS(KP500000000, T1T, T1S);
	  }
	  {
	       E T11, T1n, TW, T1m;
	       {
		    E TO, TQ, TN, TP;
		    TO = rio[WS(ios, 9)];
		    TQ = iio[-WS(ios, 2)];
		    TN = W[16];
		    TP = W[17];
		    TR = FMA(TN, TO, TP * TQ);
		    T1E = FNMS(TP, TO, TN * TQ);
	       }
	       {
		    E TY, T10, TX, TZ;
		    TY = rio[WS(ios, 5)];
		    T10 = iio[-WS(ios, 6)];
		    TX = W[8];
		    TZ = W[9];
		    T11 = FMA(TX, TY, TZ * T10);
		    T1n = FNMS(TZ, TY, TX * T10);
	       }
	       {
		    E TT, TV, TS, TU;
		    TT = rio[WS(ios, 1)];
		    TV = iio[-WS(ios, 10)];
		    TS = W[0];
		    TU = W[1];
		    TW = FMA(TS, TT, TU * TV);
		    T1m = FNMS(TU, TT, TS * TV);
	       }
	       T1o = KP866025403 * (T1m - T1n);
	       T1D = KP866025403 * (T11 - TW);
	       T12 = TW + T11;
	       T1l = FNMS(KP500000000, T12, TR);
	       T1F = T1m + T1n;
	       T1G = FNMS(KP500000000, T1F, T1E);
	  }
	  {
	       E Tv, T1N, T1Y, T20, T14, T1Z, T1Q, T1R;
	       {
		    E Td, Tu, T1U, T1X;
		    Td = T1 + Tc;
		    Tu = Ti + Tt;
		    Tv = Td + Tu;
		    T1N = Td - Tu;
		    T1U = T1S + T1T;
		    T1X = T1V + T1W;
		    T1Y = T1U + T1X;
		    T20 = T1X - T1U;
	       }
	       {
		    E TM, T13, T1O, T1P;
		    TM = TA + TL;
		    T13 = TR + T12;
		    T14 = TM + T13;
		    T1Z = TM - T13;
		    T1O = T1y + T1z;
		    T1P = T1E + T1F;
		    T1Q = T1O - T1P;
		    T1R = T1O + T1P;
	       }
	       iio[-WS(ios, 6)] = Tv - T14;
	       rio[WS(ios, 6)] = T1R - T1Y;
	       rio[0] = Tv + T14;
	       iio[0] = T1R + T1Y;
	       rio[WS(ios, 3)] = T1N - T1Q;
	       iio[-WS(ios, 3)] = T1Z + T20;
	       iio[-WS(ios, 9)] = T1N + T1Q;
	       rio[WS(ios, 9)] = T1Z - T20;
	  }
	  {
	       E T1t, T1J, T28, T2a, T1w, T21, T1M, T29;
	       {
		    E T1r, T1s, T24, T27;
		    T1r = T15 + T18;
		    T1s = T1a + T1d;
		    T1t = T1r + T1s;
		    T1J = T1r - T1s;
		    T24 = T22 + T23;
		    T27 = T25 + T26;
		    T28 = T24 - T27;
		    T2a = T27 + T24;
	       }
	       {
		    E T1u, T1v, T1K, T1L;
		    T1u = T1g + T1j;
		    T1v = T1l + T1o;
		    T1w = T1u + T1v;
		    T21 = T1v - T1u;
		    T1K = T1B + T1A;
		    T1L = T1D + T1G;
		    T1M = T1K - T1L;
		    T29 = T1K + T1L;
	       }
	       iio[-WS(ios, 10)] = T1t - T1w;
	       rio[WS(ios, 10)] = T29 - T2a;
	       rio[WS(ios, 4)] = T1t + T1w;
	       iio[-WS(ios, 4)] = T29 + T2a;
	       iio[-WS(ios, 7)] = T1J - T1M;
	       rio[WS(ios, 7)] = T21 - T28;
	       rio[WS(ios, 1)] = T1J + T1M;
	       iio[-WS(ios, 1)] = T21 + T28;
	  }
	  {
	       E T1f, T1x, T2e, T2g, T1q, T2f, T1I, T2b;
	       {
		    E T19, T1e, T2c, T2d;
		    T19 = T15 - T18;
		    T1e = T1a - T1d;
		    T1f = T19 + T1e;
		    T1x = T19 - T1e;
		    T2c = T26 - T25;
		    T2d = T23 - T22;
		    T2e = T2c + T2d;
		    T2g = T2d - T2c;
	       }
	       {
		    E T1k, T1p, T1C, T1H;
		    T1k = T1g - T1j;
		    T1p = T1l - T1o;
		    T1q = T1k + T1p;
		    T2f = T1p - T1k;
		    T1C = T1A - T1B;
		    T1H = T1D - T1G;
		    T1I = T1C + T1H;
		    T2b = T1H - T1C;
	       }
	       rio[WS(ios, 2)] = T1f - T1q;
	       iio[-WS(ios, 2)] = T2b + T2e;
	       iio[-WS(ios, 8)] = T1f + T1q;
	       rio[WS(ios, 8)] = T2b - T2e;
	       iio[-WS(ios, 11)] = T1x - T1I;
	       rio[WS(ios, 11)] = T2f - T2g;
	       rio[WS(ios, 5)] = T1x + T1I;
	       iio[-WS(ios, 5)] = T2f + T2g;
	  }
     }
     return W;
}

static const tw_instr twinstr[] = {
     {TW_FULL, 0, 12},
     {TW_NEXT, 1, 0}
};

static const hc2hc_desc desc = { 12, "hf_12", twinstr, {88, 30, 30, 0}, &GENUS, 0, 0, 0 };

void X(codelet_hf_12) (planner *p) {
     X(khc2hc_dit_register) (p, hf_12, &desc);
}
