//	OpenE.c	implementing IsiOpenEnrollment
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler
//

#include "isi_int.h"
#include <stddef.h>

#ifdef	ISI_SUPPORT_MANUAL_CONNECTIONS
const IsiApiError IsiOpenEnrollment(unsigned Assembly)
{
    IsiApiError sts = IsiEngineNotRunning;

    _IsiAPIDebug("Start IsiOpenEnrollment - Assembly=%d State=%d\n", Assembly,
        _isiVolatile.State);

    if (_isiVolatile.Running)
    {
        sts = IsiApiNoError;
#ifdef ISI_SUPPORT_CONNECTION_REMOVAL
	    if (!_isiVolatile.State) 
#else
	    if (!_isiVolatile.State && !IsiIsConnected(Assembly)) 
#endif
        {
		    if (!_IsiBecomeHost(Assembly, FALSE, NULL))
                sts = IsiNoConnectionSpace;      // No connection space or no more unused serial
	    }
    }
    _IsiAPIDebug("End IsiOpenEnrollment=%d\n", sts);
    return sts;
}
#endif	//	ISI_SUPPORT_MANUAL_CONNECTIONS

//	end of OpenE.c
