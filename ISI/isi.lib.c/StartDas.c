//	StartDas.c	implementing IsiStartDas
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

void IsiStartDas(IsiFlags Flags)
{
#ifdef ISI_SUPPORT_DADAS
    _IsiInitDeviceCountEstimation();
    IsiStartDa(Flags);
#endif	//	ISI_SUPPORT_DADAS
#if 0
#pragma ignore_notused Flags
#endif
}

