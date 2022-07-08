//	NvValue.c	implementing IsiGetNvValue
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler
//

#include "isi_int.h"
#if 0
#include <modnvlen.h>
#endif

const LonByte* IsiGetNvValue(unsigned Index, unsigned* pLength)
{
	if (pLength) *pLength = get_nv_length(Index);
	return get_nv_value(Index);
}

//	end of NvValue.c
