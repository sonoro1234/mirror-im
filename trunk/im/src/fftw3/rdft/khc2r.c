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

/* $Id: khc2r.c,v 1.1 2008-10-17 06:11:29 scuri Exp $ */

#include "rdft.h"

void X(khc2r_register)(planner *p, khc2r codelet, const khc2r_desc *desc)
{
     REGISTER_SOLVER(p, X(mksolver_rdft_hc2r_direct)(codelet, desc));
     REGISTER_SOLVER(p, X(mksolver_rdft2_hc2r_direct)(codelet, desc));
}
