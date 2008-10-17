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
/* Generated on Sat Jul  5 22:11:58 EDT 2003 */

#include "codelet-rdft.h"

/* Generated by: /homee/stevenj/cvs/fftw3.0.1/genfft/gen_hc2r -compact -variables 4 -sign 1 -n 6 -name hc2rIII_6 -dft-III -include hc2rIII.h */

/*
 * This function contains 12 FP additions, 6 FP multiplications,
 * (or, 10 additions, 4 multiplications, 2 fused multiply/add),
 * 15 stack variables, and 12 memory accesses
 */
/*
 * Generator Id's : 
 * $Id: hc2rIII_6.c,v 1.1 2008-10-17 06:12:08 scuri Exp $
 * $Id: hc2rIII_6.c,v 1.1 2008-10-17 06:12:08 scuri Exp $
 * $Id: hc2rIII_6.c,v 1.1 2008-10-17 06:12:08 scuri Exp $
 */

#include "hc2rIII.h"

static void hc2rIII_6(const R *ri, const R *ii, R *O, stride ris, stride iis, stride os, int v, int ivs, int ovs)
{
     DK(KP2_000000000, +2.000000000000000000000000000000000000000000000);
     DK(KP1_732050807, +1.732050807568877293527446341505872366942805254);
     int i;
     for (i = v; i > 0; i = i - 1, ri = ri + ivs, ii = ii + ivs, O = O + ovs) {
	  E T1, T6, T4, T5, T9, Tb, Ta, Tc;
	  T1 = ri[WS(ris, 1)];
	  T6 = ii[WS(iis, 1)];
	  {
	       E T2, T3, T7, T8;
	       T2 = ri[WS(ris, 2)];
	       T3 = ri[0];
	       T4 = T2 + T3;
	       T5 = KP1_732050807 * (T2 - T3);
	       T7 = ii[WS(iis, 2)];
	       T8 = ii[0];
	       T9 = T7 + T8;
	       Tb = KP1_732050807 * (T7 - T8);
	  }
	  O[0] = KP2_000000000 * (T1 + T4);
	  O[WS(os, 3)] = KP2_000000000 * (T6 - T9);
	  Ta = FMA(KP2_000000000, T6, T9);
	  O[WS(os, 1)] = -(T5 + Ta);
	  O[WS(os, 5)] = T5 - Ta;
	  Tc = FMS(KP2_000000000, T1, T4);
	  O[WS(os, 2)] = Tb - Tc;
	  O[WS(os, 4)] = Tc + Tb;
     }
}

static const khc2r_desc desc = { 6, "hc2rIII_6", {10, 4, 2, 0}, &GENUS, 0, 0, 0, 0, 0 };

void X(codelet_hc2rIII_6) (planner *p) {
     X(khc2rIII_register) (p, hc2rIII_6, &desc);
}
