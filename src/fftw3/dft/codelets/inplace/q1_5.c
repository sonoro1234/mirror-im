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
/* Generated on Sat Jul  5 21:39:14 EDT 2003 */

#include "codelet-dft.h"

/* Generated by: /homee/stevenj/cvs/fftw3.0.1/genfft/gen_twidsq -compact -variables 4 -reload-twiddle -dif -n 5 -name q1_5 -include q.h */

/*
 * This function contains 200 FP additions, 140 FP multiplications,
 * (or, 130 additions, 70 multiplications, 70 fused multiply/add),
 * 75 stack variables, and 100 memory accesses
 */
/*
 * Generator Id's : 
 * $Id: q1_5.c,v 1.1 2008-10-17 06:11:08 scuri Exp $
 * $Id: q1_5.c,v 1.1 2008-10-17 06:11:08 scuri Exp $
 * $Id: q1_5.c,v 1.1 2008-10-17 06:11:08 scuri Exp $
 */

#include "q.h"

static const R *q1_5(R *rio, R *iio, const R *W, stride is, stride vs, int m, int dist)
{
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DK(KP587785252, +0.587785252292473129168705954639072768597652438);
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     int i;
     for (i = m; i > 0; i = i - 1, rio = rio + dist, iio = iio + dist, W = W + 8) {
	  E T1, Ta, TG, Tv, T8, Tb, Tp, Tj, TD, To, Tq, Tr, TN, TW, T1s;
	  E T1h, TU, TX, T1b, T15, T1p, T1a, T1c, T1d, T1z, T1I, T2e, T23, T1G, T1J;
	  E T1X, T1R, T2b, T1W, T1Y, T1Z, T3v, T3p, T3J, T3u, T3w, T3x, T37, T3g, T3M;
	  E T3B, T3e, T3h, T2l, T2u, T30, T2P, T2s, T2v, T2J, T2D, T2X, T2I, T2K, T2L;
	  {
	       E T7, Tu, T4, Tt;
	       T1 = rio[0];
	       {
		    E T5, T6, T2, T3;
		    T5 = rio[WS(is, 2)];
		    T6 = rio[WS(is, 3)];
		    T7 = T5 + T6;
		    Tu = T5 - T6;
		    T2 = rio[WS(is, 1)];
		    T3 = rio[WS(is, 4)];
		    T4 = T2 + T3;
		    Tt = T2 - T3;
	       }
	       Ta = KP559016994 * (T4 - T7);
	       TG = FNMS(KP587785252, Tt, KP951056516 * Tu);
	       Tv = FMA(KP951056516, Tt, KP587785252 * Tu);
	       T8 = T4 + T7;
	       Tb = FNMS(KP250000000, T8, T1);
	  }
	  {
	       E Ti, Tn, Tf, Tm;
	       Tp = iio[0];
	       {
		    E Tg, Th, Td, Te;
		    Tg = iio[WS(is, 2)];
		    Th = iio[WS(is, 3)];
		    Ti = Tg - Th;
		    Tn = Tg + Th;
		    Td = iio[WS(is, 1)];
		    Te = iio[WS(is, 4)];
		    Tf = Td - Te;
		    Tm = Td + Te;
	       }
	       Tj = FMA(KP951056516, Tf, KP587785252 * Ti);
	       TD = FNMS(KP587785252, Tf, KP951056516 * Ti);
	       To = KP559016994 * (Tm - Tn);
	       Tq = Tm + Tn;
	       Tr = FNMS(KP250000000, Tq, Tp);
	  }
	  {
	       E TT, T1g, TQ, T1f;
	       TN = rio[WS(vs, 1)];
	       {
		    E TR, TS, TO, TP;
		    TR = rio[WS(vs, 1) + WS(is, 2)];
		    TS = rio[WS(vs, 1) + WS(is, 3)];
		    TT = TR + TS;
		    T1g = TR - TS;
		    TO = rio[WS(vs, 1) + WS(is, 1)];
		    TP = rio[WS(vs, 1) + WS(is, 4)];
		    TQ = TO + TP;
		    T1f = TO - TP;
	       }
	       TW = KP559016994 * (TQ - TT);
	       T1s = FNMS(KP587785252, T1f, KP951056516 * T1g);
	       T1h = FMA(KP951056516, T1f, KP587785252 * T1g);
	       TU = TQ + TT;
	       TX = FNMS(KP250000000, TU, TN);
	  }
	  {
	       E T14, T19, T11, T18;
	       T1b = iio[WS(vs, 1)];
	       {
		    E T12, T13, TZ, T10;
		    T12 = iio[WS(vs, 1) + WS(is, 2)];
		    T13 = iio[WS(vs, 1) + WS(is, 3)];
		    T14 = T12 - T13;
		    T19 = T12 + T13;
		    TZ = iio[WS(vs, 1) + WS(is, 1)];
		    T10 = iio[WS(vs, 1) + WS(is, 4)];
		    T11 = TZ - T10;
		    T18 = TZ + T10;
	       }
	       T15 = FMA(KP951056516, T11, KP587785252 * T14);
	       T1p = FNMS(KP587785252, T11, KP951056516 * T14);
	       T1a = KP559016994 * (T18 - T19);
	       T1c = T18 + T19;
	       T1d = FNMS(KP250000000, T1c, T1b);
	  }
	  {
	       E T1F, T22, T1C, T21;
	       T1z = rio[WS(vs, 2)];
	       {
		    E T1D, T1E, T1A, T1B;
		    T1D = rio[WS(vs, 2) + WS(is, 2)];
		    T1E = rio[WS(vs, 2) + WS(is, 3)];
		    T1F = T1D + T1E;
		    T22 = T1D - T1E;
		    T1A = rio[WS(vs, 2) + WS(is, 1)];
		    T1B = rio[WS(vs, 2) + WS(is, 4)];
		    T1C = T1A + T1B;
		    T21 = T1A - T1B;
	       }
	       T1I = KP559016994 * (T1C - T1F);
	       T2e = FNMS(KP587785252, T21, KP951056516 * T22);
	       T23 = FMA(KP951056516, T21, KP587785252 * T22);
	       T1G = T1C + T1F;
	       T1J = FNMS(KP250000000, T1G, T1z);
	  }
	  {
	       E T1Q, T1V, T1N, T1U;
	       T1X = iio[WS(vs, 2)];
	       {
		    E T1O, T1P, T1L, T1M;
		    T1O = iio[WS(vs, 2) + WS(is, 2)];
		    T1P = iio[WS(vs, 2) + WS(is, 3)];
		    T1Q = T1O - T1P;
		    T1V = T1O + T1P;
		    T1L = iio[WS(vs, 2) + WS(is, 1)];
		    T1M = iio[WS(vs, 2) + WS(is, 4)];
		    T1N = T1L - T1M;
		    T1U = T1L + T1M;
	       }
	       T1R = FMA(KP951056516, T1N, KP587785252 * T1Q);
	       T2b = FNMS(KP587785252, T1N, KP951056516 * T1Q);
	       T1W = KP559016994 * (T1U - T1V);
	       T1Y = T1U + T1V;
	       T1Z = FNMS(KP250000000, T1Y, T1X);
	  }
	  {
	       E T3o, T3t, T3l, T3s;
	       T3v = iio[WS(vs, 4)];
	       {
		    E T3m, T3n, T3j, T3k;
		    T3m = iio[WS(vs, 4) + WS(is, 2)];
		    T3n = iio[WS(vs, 4) + WS(is, 3)];
		    T3o = T3m - T3n;
		    T3t = T3m + T3n;
		    T3j = iio[WS(vs, 4) + WS(is, 1)];
		    T3k = iio[WS(vs, 4) + WS(is, 4)];
		    T3l = T3j - T3k;
		    T3s = T3j + T3k;
	       }
	       T3p = FMA(KP951056516, T3l, KP587785252 * T3o);
	       T3J = FNMS(KP587785252, T3l, KP951056516 * T3o);
	       T3u = KP559016994 * (T3s - T3t);
	       T3w = T3s + T3t;
	       T3x = FNMS(KP250000000, T3w, T3v);
	  }
	  {
	       E T3d, T3A, T3a, T3z;
	       T37 = rio[WS(vs, 4)];
	       {
		    E T3b, T3c, T38, T39;
		    T3b = rio[WS(vs, 4) + WS(is, 2)];
		    T3c = rio[WS(vs, 4) + WS(is, 3)];
		    T3d = T3b + T3c;
		    T3A = T3b - T3c;
		    T38 = rio[WS(vs, 4) + WS(is, 1)];
		    T39 = rio[WS(vs, 4) + WS(is, 4)];
		    T3a = T38 + T39;
		    T3z = T38 - T39;
	       }
	       T3g = KP559016994 * (T3a - T3d);
	       T3M = FNMS(KP587785252, T3z, KP951056516 * T3A);
	       T3B = FMA(KP951056516, T3z, KP587785252 * T3A);
	       T3e = T3a + T3d;
	       T3h = FNMS(KP250000000, T3e, T37);
	  }
	  {
	       E T2r, T2O, T2o, T2N;
	       T2l = rio[WS(vs, 3)];
	       {
		    E T2p, T2q, T2m, T2n;
		    T2p = rio[WS(vs, 3) + WS(is, 2)];
		    T2q = rio[WS(vs, 3) + WS(is, 3)];
		    T2r = T2p + T2q;
		    T2O = T2p - T2q;
		    T2m = rio[WS(vs, 3) + WS(is, 1)];
		    T2n = rio[WS(vs, 3) + WS(is, 4)];
		    T2o = T2m + T2n;
		    T2N = T2m - T2n;
	       }
	       T2u = KP559016994 * (T2o - T2r);
	       T30 = FNMS(KP587785252, T2N, KP951056516 * T2O);
	       T2P = FMA(KP951056516, T2N, KP587785252 * T2O);
	       T2s = T2o + T2r;
	       T2v = FNMS(KP250000000, T2s, T2l);
	  }
	  {
	       E T2C, T2H, T2z, T2G;
	       T2J = iio[WS(vs, 3)];
	       {
		    E T2A, T2B, T2x, T2y;
		    T2A = iio[WS(vs, 3) + WS(is, 2)];
		    T2B = iio[WS(vs, 3) + WS(is, 3)];
		    T2C = T2A - T2B;
		    T2H = T2A + T2B;
		    T2x = iio[WS(vs, 3) + WS(is, 1)];
		    T2y = iio[WS(vs, 3) + WS(is, 4)];
		    T2z = T2x - T2y;
		    T2G = T2x + T2y;
	       }
	       T2D = FMA(KP951056516, T2z, KP587785252 * T2C);
	       T2X = FNMS(KP587785252, T2z, KP951056516 * T2C);
	       T2I = KP559016994 * (T2G - T2H);
	       T2K = T2G + T2H;
	       T2L = FNMS(KP250000000, T2K, T2J);
	  }
	  rio[0] = T1 + T8;
	  iio[0] = Tp + Tq;
	  rio[WS(is, 1)] = TN + TU;
	  iio[WS(is, 1)] = T1b + T1c;
	  rio[WS(is, 2)] = T1z + T1G;
	  iio[WS(is, 2)] = T1X + T1Y;
	  iio[WS(is, 4)] = T3v + T3w;
	  rio[WS(is, 4)] = T37 + T3e;
	  rio[WS(is, 3)] = T2l + T2s;
	  iio[WS(is, 3)] = T2J + T2K;
	  {
	       E Tk, Ty, Tw, TA, Tc, Ts;
	       Tc = Ta + Tb;
	       Tk = Tc + Tj;
	       Ty = Tc - Tj;
	       Ts = To + Tr;
	       Tw = Ts - Tv;
	       TA = Tv + Ts;
	       {
		    E T9, Tl, Tx, Tz;
		    T9 = W[0];
		    Tl = W[1];
		    rio[WS(vs, 1)] = FMA(T9, Tk, Tl * Tw);
		    iio[WS(vs, 1)] = FNMS(Tl, Tk, T9 * Tw);
		    Tx = W[6];
		    Tz = W[7];
		    rio[WS(vs, 4)] = FMA(Tx, Ty, Tz * TA);
		    iio[WS(vs, 4)] = FNMS(Tz, Ty, Tx * TA);
	       }
	  }
	  {
	       E TE, TK, TI, TM, TC, TH;
	       TC = Tb - Ta;
	       TE = TC - TD;
	       TK = TC + TD;
	       TH = Tr - To;
	       TI = TG + TH;
	       TM = TH - TG;
	       {
		    E TB, TF, TJ, TL;
		    TB = W[2];
		    TF = W[3];
		    rio[WS(vs, 2)] = FMA(TB, TE, TF * TI);
		    iio[WS(vs, 2)] = FNMS(TF, TE, TB * TI);
		    TJ = W[4];
		    TL = W[5];
		    rio[WS(vs, 3)] = FMA(TJ, TK, TL * TM);
		    iio[WS(vs, 3)] = FNMS(TL, TK, TJ * TM);
	       }
	  }
	  {
	       E T2c, T2i, T2g, T2k, T2a, T2f;
	       T2a = T1J - T1I;
	       T2c = T2a - T2b;
	       T2i = T2a + T2b;
	       T2f = T1Z - T1W;
	       T2g = T2e + T2f;
	       T2k = T2f - T2e;
	       {
		    E T29, T2d, T2h, T2j;
		    T29 = W[2];
		    T2d = W[3];
		    rio[WS(vs, 2) + WS(is, 2)] = FMA(T29, T2c, T2d * T2g);
		    iio[WS(vs, 2) + WS(is, 2)] = FNMS(T2d, T2c, T29 * T2g);
		    T2h = W[4];
		    T2j = W[5];
		    rio[WS(vs, 3) + WS(is, 2)] = FMA(T2h, T2i, T2j * T2k);
		    iio[WS(vs, 3) + WS(is, 2)] = FNMS(T2j, T2i, T2h * T2k);
	       }
	  }
	  {
	       E T3K, T3Q, T3O, T3S, T3I, T3N;
	       T3I = T3h - T3g;
	       T3K = T3I - T3J;
	       T3Q = T3I + T3J;
	       T3N = T3x - T3u;
	       T3O = T3M + T3N;
	       T3S = T3N - T3M;
	       {
		    E T3H, T3L, T3P, T3R;
		    T3H = W[2];
		    T3L = W[3];
		    rio[WS(vs, 2) + WS(is, 4)] = FMA(T3H, T3K, T3L * T3O);
		    iio[WS(vs, 2) + WS(is, 4)] = FNMS(T3L, T3K, T3H * T3O);
		    T3P = W[4];
		    T3R = W[5];
		    rio[WS(vs, 3) + WS(is, 4)] = FMA(T3P, T3Q, T3R * T3S);
		    iio[WS(vs, 3) + WS(is, 4)] = FNMS(T3R, T3Q, T3P * T3S);
	       }
	  }
	  {
	       E T1S, T26, T24, T28, T1K, T20;
	       T1K = T1I + T1J;
	       T1S = T1K + T1R;
	       T26 = T1K - T1R;
	       T20 = T1W + T1Z;
	       T24 = T20 - T23;
	       T28 = T23 + T20;
	       {
		    E T1H, T1T, T25, T27;
		    T1H = W[0];
		    T1T = W[1];
		    rio[WS(vs, 1) + WS(is, 2)] = FMA(T1H, T1S, T1T * T24);
		    iio[WS(vs, 1) + WS(is, 2)] = FNMS(T1T, T1S, T1H * T24);
		    T25 = W[6];
		    T27 = W[7];
		    rio[WS(vs, 4) + WS(is, 2)] = FMA(T25, T26, T27 * T28);
		    iio[WS(vs, 4) + WS(is, 2)] = FNMS(T27, T26, T25 * T28);
	       }
	  }
	  {
	       E T2E, T2S, T2Q, T2U, T2w, T2M;
	       T2w = T2u + T2v;
	       T2E = T2w + T2D;
	       T2S = T2w - T2D;
	       T2M = T2I + T2L;
	       T2Q = T2M - T2P;
	       T2U = T2P + T2M;
	       {
		    E T2t, T2F, T2R, T2T;
		    T2t = W[0];
		    T2F = W[1];
		    rio[WS(vs, 1) + WS(is, 3)] = FMA(T2t, T2E, T2F * T2Q);
		    iio[WS(vs, 1) + WS(is, 3)] = FNMS(T2F, T2E, T2t * T2Q);
		    T2R = W[6];
		    T2T = W[7];
		    rio[WS(vs, 4) + WS(is, 3)] = FMA(T2R, T2S, T2T * T2U);
		    iio[WS(vs, 4) + WS(is, 3)] = FNMS(T2T, T2S, T2R * T2U);
	       }
	  }
	  {
	       E T2Y, T34, T32, T36, T2W, T31;
	       T2W = T2v - T2u;
	       T2Y = T2W - T2X;
	       T34 = T2W + T2X;
	       T31 = T2L - T2I;
	       T32 = T30 + T31;
	       T36 = T31 - T30;
	       {
		    E T2V, T2Z, T33, T35;
		    T2V = W[2];
		    T2Z = W[3];
		    rio[WS(vs, 2) + WS(is, 3)] = FMA(T2V, T2Y, T2Z * T32);
		    iio[WS(vs, 2) + WS(is, 3)] = FNMS(T2Z, T2Y, T2V * T32);
		    T33 = W[4];
		    T35 = W[5];
		    rio[WS(vs, 3) + WS(is, 3)] = FMA(T33, T34, T35 * T36);
		    iio[WS(vs, 3) + WS(is, 3)] = FNMS(T35, T34, T33 * T36);
	       }
	  }
	  {
	       E T3q, T3E, T3C, T3G, T3i, T3y;
	       T3i = T3g + T3h;
	       T3q = T3i + T3p;
	       T3E = T3i - T3p;
	       T3y = T3u + T3x;
	       T3C = T3y - T3B;
	       T3G = T3B + T3y;
	       {
		    E T3f, T3r, T3D, T3F;
		    T3f = W[0];
		    T3r = W[1];
		    rio[WS(vs, 1) + WS(is, 4)] = FMA(T3f, T3q, T3r * T3C);
		    iio[WS(vs, 1) + WS(is, 4)] = FNMS(T3r, T3q, T3f * T3C);
		    T3D = W[6];
		    T3F = W[7];
		    rio[WS(vs, 4) + WS(is, 4)] = FMA(T3D, T3E, T3F * T3G);
		    iio[WS(vs, 4) + WS(is, 4)] = FNMS(T3F, T3E, T3D * T3G);
	       }
	  }
	  {
	       E T1q, T1w, T1u, T1y, T1o, T1t;
	       T1o = TX - TW;
	       T1q = T1o - T1p;
	       T1w = T1o + T1p;
	       T1t = T1d - T1a;
	       T1u = T1s + T1t;
	       T1y = T1t - T1s;
	       {
		    E T1n, T1r, T1v, T1x;
		    T1n = W[2];
		    T1r = W[3];
		    rio[WS(vs, 2) + WS(is, 1)] = FMA(T1n, T1q, T1r * T1u);
		    iio[WS(vs, 2) + WS(is, 1)] = FNMS(T1r, T1q, T1n * T1u);
		    T1v = W[4];
		    T1x = W[5];
		    rio[WS(vs, 3) + WS(is, 1)] = FMA(T1v, T1w, T1x * T1y);
		    iio[WS(vs, 3) + WS(is, 1)] = FNMS(T1x, T1w, T1v * T1y);
	       }
	  }
	  {
	       E T16, T1k, T1i, T1m, TY, T1e;
	       TY = TW + TX;
	       T16 = TY + T15;
	       T1k = TY - T15;
	       T1e = T1a + T1d;
	       T1i = T1e - T1h;
	       T1m = T1h + T1e;
	       {
		    E TV, T17, T1j, T1l;
		    TV = W[0];
		    T17 = W[1];
		    rio[WS(vs, 1) + WS(is, 1)] = FMA(TV, T16, T17 * T1i);
		    iio[WS(vs, 1) + WS(is, 1)] = FNMS(T17, T16, TV * T1i);
		    T1j = W[6];
		    T1l = W[7];
		    rio[WS(vs, 4) + WS(is, 1)] = FMA(T1j, T1k, T1l * T1m);
		    iio[WS(vs, 4) + WS(is, 1)] = FNMS(T1l, T1k, T1j * T1m);
	       }
	  }
     }
     return W;
}

static const tw_instr twinstr[] = {
     {TW_FULL, 0, 5},
     {TW_NEXT, 1, 0}
};

static const ct_desc desc = { 5, "q1_5", twinstr, {130, 70, 70, 0}, &GENUS, 0, 0, 0 };

void X(codelet_q1_5) (planner *p) {
     X(kdft_difsq_register) (p, q1_5, &desc);
}
