//	ExtendE.c	implementing IsiExtendEnrollment
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

#ifdef	ISI_SUPPORT_MANUAL_CONNECTIONS
#ifdef 	ISI_SUPPORT_ALIAS
const IsiApiError IsiExtendEnrollment(unsigned Assembly)
{
    IsiApiError sts = IsiEngineNotRunning;

    _IsiAPIDebug("Start IsiExtendEnrollment - Assembly %d\n", Assembly);
    if (_isiVolatile.Running)
    {
	    _IsiMakeEnrollment(TRUE, Assembly);
        sts = IsiApiNoError;
    }
    _IsiAPIDebug("End IsiExtendEnrollment=%d\n", sts);
    return sts;
}
#endif	//	ISI_SUPPORT_ALIAS
#endif	//	ISI_SUPPORT_MANUAL_CONNECTIONS

//	end of ExtendE.c
