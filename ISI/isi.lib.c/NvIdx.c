//	GetNvIdx.c	implementing isiGetNvIndex
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler
//

#include "isi_int.h"

unsigned FWD(IsiGetNvIndex,isiGetNvIndex)(unsigned Assembly, unsigned Offset, unsigned PreviousIndex)
{
    // Combine the isiGetNvIndex and isiGetNextNvIndex into one by specifying ISI_NO_INDEX for the previous argument in the first call.
    if (PreviousIndex == ISI_NO_INDEX)
	    return Assembly+Offset;
    else
        return isiGetNextNvIndex(Assembly, Offset, PreviousIndex);
}

//	end of GetNvIdx.c
