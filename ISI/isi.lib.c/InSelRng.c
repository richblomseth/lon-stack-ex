//	InSelRng.c	implementing _IsiInSelectorRange
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

// the function returns TRUE if Selector is included in [RangeStart...RangeStart+Count], bearing in
// mind that selectors wrap-around at 0x2fffu

LonBool _IsiInSelectorRange(LonWord RangeStart, unsigned Count, LonWord Selector)
{
	LonWord RangeEnd;

	RangeEnd = _IsiAddSelector(RangeStart, Count);

	return (LON_GET_UNSIGNED_WORD(RangeEnd) >= LON_GET_UNSIGNED_WORD(RangeStart)) == ((LON_GET_UNSIGNED_WORD(Selector) >= LON_GET_UNSIGNED_WORD(RangeStart)) + (LON_GET_UNSIGNED_WORD(Selector) <= LON_GET_UNSIGNED_WORD(RangeEnd)) - 1);
}

//	end of InSelRng.c
