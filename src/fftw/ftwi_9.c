/*
 * Copyright (c) 1997-1999, 2003 Massachusetts Institute of Technology
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
/* Generated on Mon Mar 24 02:08:32 EST 2003 */

#include "fftw-int.h"
#include "fftw.h"

/* Generated by: /homee/stevenj/cvs/fftw/gensrc/genfft -magic-alignment-check -magic-twiddle-load-all -magic-variables 4 -magic-loopi -twiddleinv 9 */

/*
 * This function contains 96 FP additions, 72 FP multiplications,
 * (or, 60 additions, 36 multiplications, 36 fused multiply/add),
 * 34 stack variables, and 36 memory accesses
 */
static const fftw_real K642787609 =
FFTW_KONST(+0.642787609686539326322643409907263432907559884);
static const fftw_real K766044443 =
FFTW_KONST(+0.766044443118978035202392650555416673935832457);
static const fftw_real K939692620 =
FFTW_KONST(+0.939692620785908384054109277324731469936208134);
static const fftw_real K342020143 =
FFTW_KONST(+0.342020143325668733044099614682259580763083368);
static const fftw_real K984807753 =
FFTW_KONST(+0.984807753012208059366743024589523013670643252);
static const fftw_real K173648177 =
FFTW_KONST(+0.173648177666930348851716626769314796000375677);
static const fftw_real K500000000 =
FFTW_KONST(+0.500000000000000000000000000000000000000000000);
static const fftw_real K866025403 =
FFTW_KONST(+0.866025403784438646763723170752936183471402627);

/*
 * Generator Id's : 
 * $Id: ftwi_9.c,v 1.1 2008-10-17 06:13:18 scuri Exp $
 * $Id: ftwi_9.c,v 1.1 2008-10-17 06:13:18 scuri Exp $
 * $Id: ftwi_9.c,v 1.1 2008-10-17 06:13:18 scuri Exp $
 */

void fftwi_twiddle_9(fftw_complex *A, const fftw_complex *W, int iostride,
		     int m, int dist)
{
     int i;
     fftw_complex *inout;
     inout = A;
     for (i = m; i > 0; i = i - 1, inout = inout + dist, W = W + 8) {
	  fftw_real tmp1;
	  fftw_real tmp99;
	  fftw_real tmp64;
	  fftw_real tmp98;
	  fftw_real tmp105;
	  fftw_real tmp104;
	  fftw_real tmp12;
	  fftw_real tmp61;
	  fftw_real tmp47;
	  fftw_real tmp78;
	  fftw_real tmp89;
	  fftw_real tmp54;
	  fftw_real tmp75;
	  fftw_real tmp90;
	  fftw_real tmp30;
	  fftw_real tmp68;
	  fftw_real tmp86;
	  fftw_real tmp59;
	  fftw_real tmp71;
	  fftw_real tmp87;
	  ASSERT_ALIGNED_DOUBLE;
	  {
	       fftw_real tmp6;
	       fftw_real tmp63;
	       fftw_real tmp11;
	       fftw_real tmp62;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp1 = c_re(inout[0]);
	       tmp99 = c_im(inout[0]);
	       {
		    fftw_real tmp3;
		    fftw_real tmp5;
		    fftw_real tmp2;
		    fftw_real tmp4;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp3 = c_re(inout[3 * iostride]);
		    tmp5 = c_im(inout[3 * iostride]);
		    tmp2 = c_re(W[2]);
		    tmp4 = c_im(W[2]);
		    tmp6 = (tmp2 * tmp3) + (tmp4 * tmp5);
		    tmp63 = (tmp2 * tmp5) - (tmp4 * tmp3);
	       }
	       {
		    fftw_real tmp8;
		    fftw_real tmp10;
		    fftw_real tmp7;
		    fftw_real tmp9;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp8 = c_re(inout[6 * iostride]);
		    tmp10 = c_im(inout[6 * iostride]);
		    tmp7 = c_re(W[5]);
		    tmp9 = c_im(W[5]);
		    tmp11 = (tmp7 * tmp8) + (tmp9 * tmp10);
		    tmp62 = (tmp7 * tmp10) - (tmp9 * tmp8);
	       }
	       tmp64 = K866025403 * (tmp62 - tmp63);
	       tmp98 = tmp63 + tmp62;
	       tmp105 = tmp99 - (K500000000 * tmp98);
	       tmp104 = K866025403 * (tmp6 - tmp11);
	       tmp12 = tmp6 + tmp11;
	       tmp61 = tmp1 - (K500000000 * tmp12);
	  }
	  {
	       fftw_real tmp35;
	       fftw_real tmp50;
	       fftw_real tmp40;
	       fftw_real tmp51;
	       fftw_real tmp45;
	       fftw_real tmp52;
	       fftw_real tmp46;
	       fftw_real tmp53;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp32;
		    fftw_real tmp34;
		    fftw_real tmp31;
		    fftw_real tmp33;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp32 = c_re(inout[2 * iostride]);
		    tmp34 = c_im(inout[2 * iostride]);
		    tmp31 = c_re(W[1]);
		    tmp33 = c_im(W[1]);
		    tmp35 = (tmp31 * tmp32) + (tmp33 * tmp34);
		    tmp50 = (tmp31 * tmp34) - (tmp33 * tmp32);
	       }
	       {
		    fftw_real tmp37;
		    fftw_real tmp39;
		    fftw_real tmp36;
		    fftw_real tmp38;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp37 = c_re(inout[5 * iostride]);
		    tmp39 = c_im(inout[5 * iostride]);
		    tmp36 = c_re(W[4]);
		    tmp38 = c_im(W[4]);
		    tmp40 = (tmp36 * tmp37) + (tmp38 * tmp39);
		    tmp51 = (tmp36 * tmp39) - (tmp38 * tmp37);
	       }
	       {
		    fftw_real tmp42;
		    fftw_real tmp44;
		    fftw_real tmp41;
		    fftw_real tmp43;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp42 = c_re(inout[8 * iostride]);
		    tmp44 = c_im(inout[8 * iostride]);
		    tmp41 = c_re(W[7]);
		    tmp43 = c_im(W[7]);
		    tmp45 = (tmp41 * tmp42) + (tmp43 * tmp44);
		    tmp52 = (tmp41 * tmp44) - (tmp43 * tmp42);
	       }
	       tmp46 = tmp40 + tmp45;
	       tmp53 = tmp51 + tmp52;
	       {
		    fftw_real tmp76;
		    fftw_real tmp77;
		    fftw_real tmp73;
		    fftw_real tmp74;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp47 = tmp35 + tmp46;
		    tmp76 = tmp35 - (K500000000 * tmp46);
		    tmp77 = K866025403 * (tmp52 - tmp51);
		    tmp78 = tmp76 - tmp77;
		    tmp89 = tmp76 + tmp77;
		    tmp54 = tmp50 + tmp53;
		    tmp73 = tmp50 - (K500000000 * tmp53);
		    tmp74 = K866025403 * (tmp40 - tmp45);
		    tmp75 = tmp73 - tmp74;
		    tmp90 = tmp74 + tmp73;
	       }
	  }
	  {
	       fftw_real tmp18;
	       fftw_real tmp55;
	       fftw_real tmp23;
	       fftw_real tmp56;
	       fftw_real tmp28;
	       fftw_real tmp57;
	       fftw_real tmp29;
	       fftw_real tmp58;
	       ASSERT_ALIGNED_DOUBLE;
	       {
		    fftw_real tmp15;
		    fftw_real tmp17;
		    fftw_real tmp14;
		    fftw_real tmp16;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp15 = c_re(inout[iostride]);
		    tmp17 = c_im(inout[iostride]);
		    tmp14 = c_re(W[0]);
		    tmp16 = c_im(W[0]);
		    tmp18 = (tmp14 * tmp15) + (tmp16 * tmp17);
		    tmp55 = (tmp14 * tmp17) - (tmp16 * tmp15);
	       }
	       {
		    fftw_real tmp20;
		    fftw_real tmp22;
		    fftw_real tmp19;
		    fftw_real tmp21;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp20 = c_re(inout[4 * iostride]);
		    tmp22 = c_im(inout[4 * iostride]);
		    tmp19 = c_re(W[3]);
		    tmp21 = c_im(W[3]);
		    tmp23 = (tmp19 * tmp20) + (tmp21 * tmp22);
		    tmp56 = (tmp19 * tmp22) - (tmp21 * tmp20);
	       }
	       {
		    fftw_real tmp25;
		    fftw_real tmp27;
		    fftw_real tmp24;
		    fftw_real tmp26;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp25 = c_re(inout[7 * iostride]);
		    tmp27 = c_im(inout[7 * iostride]);
		    tmp24 = c_re(W[6]);
		    tmp26 = c_im(W[6]);
		    tmp28 = (tmp24 * tmp25) + (tmp26 * tmp27);
		    tmp57 = (tmp24 * tmp27) - (tmp26 * tmp25);
	       }
	       tmp29 = tmp23 + tmp28;
	       tmp58 = tmp56 + tmp57;
	       {
		    fftw_real tmp66;
		    fftw_real tmp67;
		    fftw_real tmp69;
		    fftw_real tmp70;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp30 = tmp18 + tmp29;
		    tmp66 = tmp18 - (K500000000 * tmp29);
		    tmp67 = K866025403 * (tmp57 - tmp56);
		    tmp68 = tmp66 - tmp67;
		    tmp86 = tmp66 + tmp67;
		    tmp59 = tmp55 + tmp58;
		    tmp69 = tmp55 - (K500000000 * tmp58);
		    tmp70 = K866025403 * (tmp23 - tmp28);
		    tmp71 = tmp69 - tmp70;
		    tmp87 = tmp70 + tmp69;
	       }
	  }
	  {
	       fftw_real tmp60;
	       fftw_real tmp13;
	       fftw_real tmp48;
	       fftw_real tmp49;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp60 = K866025403 * (tmp54 - tmp59);
	       tmp13 = tmp1 + tmp12;
	       tmp48 = tmp30 + tmp47;
	       tmp49 = tmp13 - (K500000000 * tmp48);
	       c_re(inout[0]) = tmp13 + tmp48;
	       c_re(inout[3 * iostride]) = tmp49 + tmp60;
	       c_re(inout[6 * iostride]) = tmp49 - tmp60;
	  }
	  {
	       fftw_real tmp101;
	       fftw_real tmp97;
	       fftw_real tmp100;
	       fftw_real tmp102;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp101 = K866025403 * (tmp30 - tmp47);
	       tmp97 = tmp59 + tmp54;
	       tmp100 = tmp98 + tmp99;
	       tmp102 = tmp100 - (K500000000 * tmp97);
	       c_im(inout[0]) = tmp97 + tmp100;
	       c_im(inout[6 * iostride]) = tmp102 - tmp101;
	       c_im(inout[3 * iostride]) = tmp101 + tmp102;
	  }
	  {
	       fftw_real tmp65;
	       fftw_real tmp110;
	       fftw_real tmp80;
	       fftw_real tmp111;
	       fftw_real tmp84;
	       fftw_real tmp109;
	       fftw_real tmp81;
	       fftw_real tmp112;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp65 = tmp61 - tmp64;
	       tmp110 = tmp105 - tmp104;
	       {
		    fftw_real tmp72;
		    fftw_real tmp79;
		    fftw_real tmp82;
		    fftw_real tmp83;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp72 = (K173648177 * tmp68) - (K984807753 * tmp71);
		    tmp79 = (K342020143 * tmp75) + (K939692620 * tmp78);
		    tmp80 = tmp72 - tmp79;
		    tmp111 = K866025403 * (tmp72 + tmp79);
		    tmp82 = (K342020143 * tmp78) - (K939692620 * tmp75);
		    tmp83 = (K173648177 * tmp71) + (K984807753 * tmp68);
		    tmp84 = K866025403 * (tmp82 - tmp83);
		    tmp109 = tmp83 + tmp82;
	       }
	       c_re(inout[2 * iostride]) = tmp65 + tmp80;
	       tmp81 = tmp65 - (K500000000 * tmp80);
	       c_re(inout[8 * iostride]) = tmp81 - tmp84;
	       c_re(inout[5 * iostride]) = tmp81 + tmp84;
	       c_im(inout[2 * iostride]) = tmp109 + tmp110;
	       tmp112 = tmp110 - (K500000000 * tmp109);
	       c_im(inout[5 * iostride]) = tmp111 + tmp112;
	       c_im(inout[8 * iostride]) = tmp112 - tmp111;
	  }
	  {
	       fftw_real tmp85;
	       fftw_real tmp106;
	       fftw_real tmp92;
	       fftw_real tmp107;
	       fftw_real tmp96;
	       fftw_real tmp103;
	       fftw_real tmp93;
	       fftw_real tmp108;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp85 = tmp61 + tmp64;
	       tmp106 = tmp104 + tmp105;
	       {
		    fftw_real tmp88;
		    fftw_real tmp91;
		    fftw_real tmp94;
		    fftw_real tmp95;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp88 = (K766044443 * tmp86) - (K642787609 * tmp87);
		    tmp91 = (K173648177 * tmp89) - (K984807753 * tmp90);
		    tmp92 = tmp88 + tmp91;
		    tmp107 = K866025403 * (tmp88 - tmp91);
		    tmp94 = (K173648177 * tmp90) + (K984807753 * tmp89);
		    tmp95 = (K766044443 * tmp87) + (K642787609 * tmp86);
		    tmp96 = K866025403 * (tmp94 - tmp95);
		    tmp103 = tmp95 + tmp94;
	       }
	       c_re(inout[iostride]) = tmp85 + tmp92;
	       tmp93 = tmp85 - (K500000000 * tmp92);
	       c_re(inout[7 * iostride]) = tmp93 - tmp96;
	       c_re(inout[4 * iostride]) = tmp93 + tmp96;
	       c_im(inout[iostride]) = tmp103 + tmp106;
	       tmp108 = tmp106 - (K500000000 * tmp103);
	       c_im(inout[4 * iostride]) = tmp107 + tmp108;
	       c_im(inout[7 * iostride]) = tmp108 - tmp107;
	  }
     }
}

static const int twiddle_order[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
fftw_codelet_desc fftwi_twiddle_9_desc = {
     "fftwi_twiddle_9",
     (void (*)()) fftwi_twiddle_9,
     9,
     FFTW_BACKWARD,
     FFTW_TWIDDLE,
     209,
     8,
     twiddle_order,
};
