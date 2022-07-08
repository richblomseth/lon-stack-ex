//	LeaveE.c	implementing IsiLeaveEnrollment
//
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

#ifdef ISI_SUPPORT_CONNECTION_REMOVAL

const IsiApiError IsiLeaveEnrollment(unsigned Assembly)
{
    IsiApiError sts = IsiEngineNotRunning;
    _IsiAPIDebug("Start IsiLeaveEnrollment - Assembly=%d\n", Assembly);

    if (_isiVolatile.Running)
    {
	    _IsiRemoveConnection(isiStateNormal, Assembly, FALSE);
        sts = IsiApiNoError;
    }
    _IsiAPIDebug("End IsiLeaveEnrollment=%d\n", sts);
    return sts;
}
#endif	//	 ISI_SUPPORT_CONNECTION_REMOVAL

//	end of LeaveE.c
