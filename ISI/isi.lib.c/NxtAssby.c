//	NxtAssby.c	implementing isiGetNextAssembly
//
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler
//

#include "isi_int.h"

unsigned FWD(IsiGetNextAssembly,isiGetNextAssembly)(const IsiCsmoData* pCsmoData, LonBool Auto, unsigned Assembly)
{
	return Auto ? ISI_NO_ASSEMBLY : _IsiFindLocalNvOfType(pCsmoData, ++Assembly);
#if 0
#pragma ignore_notused Auto			// gets rejected in GetAssembly() already
#endif
}

//	end of NxtAssby.c
