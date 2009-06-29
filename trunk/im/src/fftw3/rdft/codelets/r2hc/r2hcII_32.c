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
/* Generated on Sat Jul  5 21:58:28 EDT 2003 */

#include "codelet-rdft.h"

/* Generated by: /homee/stevenj/cvs/fftw3.0.1/genfft/gen_r2hc -compact -variables 4 -n 32 -name r2hcII_32 -dft-II -include r2hcII.h */

/*
 * This function contains 174 FP additions, 82 FP multiplications,
 * (or, 138 additions, 46 multiplications, 36 fused multiply/add),
 * 62 stack variables, and 64 memory accesses
 */
/*
 * Generator Id's : 
 * $Id: r2hcII_32.c,v 1.1 2008-10-17 06:12:34 scuri Exp $
 * $Id: r2hcII_32.c,v 1.1 2008-10-17 06:12:34 scuri Exp $
 * $Id: r2hcII_32.c,v 1.1 2008-10-17 06:12:34 scuri Exp $
 */

#include "r2hcII.h"

static void r2hcII_32(const R *I, R *ro, R *io, stride is, stride ros, stride ios, int v, int ivs, int ovs)
{
     DK(KP471396736, +0.471396736825997648556387625905254377657460319);
     DK(KP881921264, +0.881921264348355029712756863660388349508442621);
     DK(KP634393284, +0.634393284163645498215171613225493370675687095);
     DK(KP773010453, +0.773010453362736960810906609758469800971041293);
     DK(KP290284677, +0.290284677254462367636192375817395274691476278);
     DK(KP956940335, +0.956940335732208864935797886980269969482849206);
     DK(KP995184726, +0.995184726672196886244836953109479921575474869);
     DK(KP098017140, +0.098017140329560601994195563888641845861136673);
     DK(KP555570233, +0.555570233019602224742830813948532874374937191);
     DK(KP831469612, +0.831469612302545237078788377617905756738560812);
     DK(KP195090322, +0.195090322016128267848284868477022240927691618);
     DK(KP980785280, +0.980785280403230449126182236134239036973933731);
     DK(KP382683432, +0.382683432365089771728459984030398866761344562);
     DK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DK(KP707106781, +0.707106781186547524400844362104849039284835938);
     int i;
     for (i = v; i > 0; i = i - 1, I = I + ivs, ro = ro + ovs, io = io + ovs) {
	  E T5, T2D, T1z, T2q, Tc, T2C, T1C, T2n, Tm, T1k, T1J, T26, Tv, T1l, T1G;
	  E T27, T15, T1r, T1Y, T2e, T1c, T1s, T1V, T2d, TK, T1o, T1R, T2b, TR, T1p;
	  E T1O, T2a;
	  {
	       E T1, T2p, T4, T2o, T2, T3;
	       T1 = I[0];
	       T2p = I[WS(is, 16)];
	       T2 = I[WS(is, 8)];
	       T3 = I[WS(is, 24)];
	       T4 = KP707106781 * (T2 - T3);
	       T2o = KP707106781 * (T2 + T3);
	       T5 = T1 + T4;
	       T2D = T2p - T2o;
	       T1z = T1 - T4;
	       T2q = T2o + T2p;
	  }
	  {
	       E T8, T1A, Tb, T1B;
	       {
		    E T6, T7, T9, Ta;
		    T6 = I[WS(is, 4)];
		    T7 = I[WS(is, 20)];
		    T8 = FNMS(KP382683432, T7, KP923879532 * T6);
		    T1A = FMA(KP382683432, T6, KP923879532 * T7);
		    T9 = I[WS(is, 12)];
		    Ta = I[WS(is, 28)];
		    Tb = FNMS(KP923879532, Ta, KP382683432 * T9);
		    T1B = FMA(KP923879532, T9, KP382683432 * Ta);
	       }
	       Tc = T8 + Tb;
	       T2C = Tb - T8;
	       T1C = T1A - T1B;
	       T2n = T1A + T1B;
	  }
	  {
	       E Te, Tk, Th, Tj, Tf, Tg;
	       Te = I[WS(is, 2)];
	       Tk = I[WS(is, 18)];
	       Tf = I[WS(is, 10)];
	       Tg = I[WS(is, 26)];
	       Th = KP707106781 * (Tf - Tg);
	       Tj = KP707106781 * (Tf + Tg);
	       {
		    E Ti, Tl, T1H, T1I;
		    Ti = Te + Th;
		    Tl = Tj + Tk;
		    Tm = FNMS(KP195090322, Tl, KP980785280 * Ti);
		    T1k = FMA(KP195090322, Ti, KP980785280 * Tl);
		    T1H = Tk - Tj;
		    T1I = Te - Th;
		    T1J = FNMS(KP555570233, T1I, KP831469612 * T1H);
		    T26 = FMA(KP831469612, T1I, KP555570233 * T1H);
	       }
	  }
	  {
	       E Tq, Tt, Tp, Ts, Tn, To;
	       Tq = I[WS(is, 30)];
	       Tt = I[WS(is, 14)];
	       Tn = I[WS(is, 6)];
	       To = I[WS(is, 22)];
	       Tp = KP707106781 * (Tn - To);
	       Ts = KP707106781 * (Tn + To);
	       {
		    E Tr, Tu, T1E, T1F;
		    Tr = Tp - Tq;
		    Tu = Ts + Tt;
		    Tv = FMA(KP980785280, Tr, KP195090322 * Tu);
		    T1l = FNMS(KP980785280, Tu, KP195090322 * Tr);
		    T1E = Tt - Ts;
		    T1F = Tp + Tq;
		    T1G = FNMS(KP555570233, T1F, KP831469612 * T1E);
		    T27 = FMA(KP831469612, T1F, KP555570233 * T1E);
	       }
	  }
	  {
	       E TW, T1a, TV, T19, T10, T16, T13, T17, TT, TU;
	       TW = I[WS(is, 31)];
	       T1a = I[WS(is, 15)];
	       TT = I[WS(is, 7)];
	       TU = I[WS(is, 23)];
	       TV = KP707106781 * (TT - TU);
	       T19 = KP707106781 * (TT + TU);
	       {
		    E TY, TZ, T11, T12;
		    TY = I[WS(is, 3)];
		    TZ = I[WS(is, 19)];
		    T10 = FNMS(KP382683432, TZ, KP923879532 * TY);
		    T16 = FMA(KP382683432, TY, KP923879532 * TZ);
		    T11 = I[WS(is, 11)];
		    T12 = I[WS(is, 27)];
		    T13 = FNMS(KP923879532, T12, KP382683432 * T11);
		    T17 = FMA(KP923879532, T11, KP382683432 * T12);
	       }
	       {
		    E TX, T14, T1W, T1X;
		    TX = TV - TW;
		    T14 = T10 + T13;
		    T15 = TX + T14;
		    T1r = TX - T14;
		    T1W = T13 - T10;
		    T1X = T1a - T19;
		    T1Y = T1W - T1X;
		    T2e = T1W + T1X;
	       }
	       {
		    E T18, T1b, T1T, T1U;
		    T18 = T16 + T17;
		    T1b = T19 + T1a;
		    T1c = T18 + T1b;
		    T1s = T1b - T18;
		    T1T = TV + TW;
		    T1U = T16 - T17;
		    T1V = T1T + T1U;
		    T2d = T1U - T1T;
	       }
	  }
	  {
	       E Ty, TP, TB, TO, TF, TL, TI, TM, Tz, TA;
	       Ty = I[WS(is, 1)];
	       TP = I[WS(is, 17)];
	       Tz = I[WS(is, 9)];
	       TA = I[WS(is, 25)];
	       TB = KP707106781 * (Tz - TA);
	       TO = KP707106781 * (Tz + TA);
	       {
		    E TD, TE, TG, TH;
		    TD = I[WS(is, 5)];
		    TE = I[WS(is, 21)];
		    TF = FNMS(KP382683432, TE, KP923879532 * TD);
		    TL = FMA(KP382683432, TD, KP923879532 * TE);
		    TG = I[WS(is, 13)];
		    TH = I[WS(is, 29)];
		    TI = FNMS(KP923879532, TH, KP382683432 * TG);
		    TM = FMA(KP923879532, TG, KP382683432 * TH);
	       }
	       {
		    E TC, TJ, T1P, T1Q;
		    TC = Ty + TB;
		    TJ = TF + TI;
		    TK = TC + TJ;
		    T1o = TC - TJ;
		    T1P = TI - TF;
		    T1Q = TP - TO;
		    T1R = T1P - T1Q;
		    T2b = T1P + T1Q;
	       }
	       {
		    E TN, TQ, T1M, T1N;
		    TN = TL + TM;
		    TQ = TO + TP;
		    TR = TN + TQ;
		    T1p = TQ - TN;
		    T1M = Ty - TB;
		    T1N = TL - TM;
		    T1O = T1M - T1N;
		    T2a = T1M + T1N;
	       }
	  }
	  {
	       E Tx, T1f, T2s, T2u, T1e, T2l, T1i, T2t;
	       {
		    E Td, Tw, T2m, T2r;
		    Td = T5 + Tc;
		    Tw = Tm + Tv;
		    Tx = Td - Tw;
		    T1f = Td + Tw;
		    T2m = T1l - T1k;
		    T2r = T2n + T2q;
		    T2s = T2m - T2r;
		    T2u = T2m + T2r;
	       }
	       {
		    E TS, T1d, T1g, T1h;
		    TS = FMA(KP098017140, TK, KP995184726 * TR);
		    T1d = FNMS(KP995184726, T1c, KP098017140 * T15);
		    T1e = TS + T1d;
		    T2l = T1d - TS;
		    T1g = FNMS(KP098017140, TR, KP995184726 * TK);
		    T1h = FMA(KP995184726, T15, KP098017140 * T1c);
		    T1i = T1g + T1h;
		    T2t = T1h - T1g;
	       }
	       ro[WS(ros, 8)] = Tx - T1e;
	       io[WS(ios, 8)] = T2t - T2u;
	       ro[WS(ros, 7)] = Tx + T1e;
	       io[WS(ios, 7)] = T2t + T2u;
	       ro[WS(ros, 15)] = T1f - T1i;
	       io[WS(ios, 15)] = T2l - T2s;
	       ro[0] = T1f + T1i;
	       io[0] = T2l + T2s;
	  }
	  {
	       E T29, T2h, T2M, T2O, T2g, T2J, T2k, T2N;
	       {
		    E T25, T28, T2K, T2L;
		    T25 = T1z + T1C;
		    T28 = T26 - T27;
		    T29 = T25 + T28;
		    T2h = T25 - T28;
		    T2K = T1J + T1G;
		    T2L = T2C + T2D;
		    T2M = T2K - T2L;
		    T2O = T2K + T2L;
	       }
	       {
		    E T2c, T2f, T2i, T2j;
		    T2c = FMA(KP956940335, T2a, KP290284677 * T2b);
		    T2f = FNMS(KP290284677, T2e, KP956940335 * T2d);
		    T2g = T2c + T2f;
		    T2J = T2f - T2c;
		    T2i = FMA(KP290284677, T2d, KP956940335 * T2e);
		    T2j = FNMS(KP290284677, T2a, KP956940335 * T2b);
		    T2k = T2i - T2j;
		    T2N = T2j + T2i;
	       }
	       ro[WS(ros, 14)] = T29 - T2g;
	       io[WS(ios, 14)] = T2N - T2O;
	       ro[WS(ros, 1)] = T29 + T2g;
	       io[WS(ios, 1)] = T2N + T2O;
	       ro[WS(ros, 9)] = T2h - T2k;
	       io[WS(ios, 9)] = T2J - T2M;
	       ro[WS(ros, 6)] = T2h + T2k;
	       io[WS(ios, 6)] = T2J + T2M;
	  }
	  {
	       E T1n, T1v, T2y, T2A, T1u, T2v, T1y, T2z;
	       {
		    E T1j, T1m, T2w, T2x;
		    T1j = T5 - Tc;
		    T1m = T1k + T1l;
		    T1n = T1j + T1m;
		    T1v = T1j - T1m;
		    T2w = Tv - Tm;
		    T2x = T2q - T2n;
		    T2y = T2w - T2x;
		    T2A = T2w + T2x;
	       }
	       {
		    E T1q, T1t, T1w, T1x;
		    T1q = FMA(KP773010453, T1o, KP634393284 * T1p);
		    T1t = FNMS(KP634393284, T1s, KP773010453 * T1r);
		    T1u = T1q + T1t;
		    T2v = T1t - T1q;
		    T1w = FMA(KP634393284, T1r, KP773010453 * T1s);
		    T1x = FNMS(KP634393284, T1o, KP773010453 * T1p);
		    T1y = T1w - T1x;
		    T2z = T1x + T1w;
	       }
	       ro[WS(ros, 12)] = T1n - T1u;
	       io[WS(ios, 12)] = T2z - T2A;
	       ro[WS(ros, 3)] = T1n + T1u;
	       io[WS(ios, 3)] = T2z + T2A;
	       ro[WS(ros, 11)] = T1v - T1y;
	       io[WS(ios, 11)] = T2v - T2y;
	       ro[WS(ros, 4)] = T1v + T1y;
	       io[WS(ios, 4)] = T2v + T2y;
	  }
	  {
	       E T1L, T21, T2G, T2I, T20, T2H, T24, T2B;
	       {
		    E T1D, T1K, T2E, T2F;
		    T1D = T1z - T1C;
		    T1K = T1G - T1J;
		    T1L = T1D + T1K;
		    T21 = T1D - T1K;
		    T2E = T2C - T2D;
		    T2F = T26 + T27;
		    T2G = T2E - T2F;
		    T2I = T2F + T2E;
	       }
	       {
		    E T1S, T1Z, T22, T23;
		    T1S = FMA(KP881921264, T1O, KP471396736 * T1R);
		    T1Z = FMA(KP881921264, T1V, KP471396736 * T1Y);
		    T20 = T1S - T1Z;
		    T2H = T1S + T1Z;
		    T22 = FNMS(KP471396736, T1V, KP881921264 * T1Y);
		    T23 = FNMS(KP471396736, T1O, KP881921264 * T1R);
		    T24 = T22 - T23;
		    T2B = T23 + T22;
	       }
	       ro[WS(ros, 13)] = T1L - T20;
	       io[WS(ios, 13)] = T2B - T2G;
	       ro[WS(ros, 2)] = T1L + T20;
	       io[WS(ios, 2)] = T2B + T2G;
	       ro[WS(ros, 10)] = T21 - T24;
	       io[WS(ios, 10)] = T2I - T2H;
	       ro[WS(ros, 5)] = T21 + T24;
	       io[WS(ios, 5)] = -(T2H + T2I);
	  }
     }
}

static const kr2hc_desc desc = { 32, "r2hcII_32", {138, 46, 36, 0}, &GENUS, 0, 0, 0, 0, 0 };

void X(codelet_r2hcII_32) (planner *p) {
     X(kr2hcII_register) (p, r2hcII_32, &desc);
}