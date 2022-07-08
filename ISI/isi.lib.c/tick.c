//	tick.c	implementing isiTick
//
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, January 2005, Bernd Gauweiler

#include "isi_int.h"

const IsiApiError IsiTick()
{
    IsiApiError sts = IsiApiNoError;

    IsiType Type = _IsiGetCurrentType();
#ifdef	ISI_SUPPORT_DADAS
	if (Type == isiTypeDas)
    {
		IsiTickDas();
	} else if (Type == isiTypeDa) 
    {
		IsiTickDa();
	} else
    {
		IsiTickS();
	}
#else
	if (Type == isiTypeS) {
		IsiTickS();
	}
#endif	//	ISI_SUPPORT_DADAS

    return sts;
}

