//	CancelE.c	implementing IsiCancelEnrollment
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//  Revision 0, February 2005, Bernd Gauweiler

#ifdef WIN32
#include <control.h>
#endif
#include "isi_int.h"

const IsiApiError IsiCancelEnrollment(void)
{
    unsigned index;
    IsiConnection connection;
    IsiApiError sts = IsiEngineNotRunning;

    _IsiAPIDebug("Start IsiCancelEnrollment - State=%d\n", _isiVolatile.State); 

    if (_isiVolatile.Running)
    {
	    if (_isiVolatile.State & HOST_STATES)
        {
		    // this happens on the host.
 		    _IsiSendCsmx();
	    }
	    if (_isiVolatile.State & CONNECTION_STATES)
        {
		    // this happens on the guest and host

            //  we clear out the connection table from all pending connections. This is not required stricly speaking; we could just
            //  leave the pending entries behind and set the global state to normal. This is sufficient (and the pending but stale
            //  connection table entries get re-used with the next invitation), but it prevents the engine from accepting the next
            //  resend CSMI that applies to the same connection: this re-send would be recognized as a duplicate, and ignored (see
            //  rcvcsmo.c). Doing this extra bit of cleaning allows to accept assembly #1, then cancel this acceptance, and (a minute
            //  or so later, as soon as the next CSMI came in), to accept assembly #2 instead.
            for (index = _isiVolatile.pendingConnection; _IsiNextConnection(index, &connection); ++index) 
                // if (connection.State == isiConnectionStatePending)
                if (LON_GET_ATTRIBUTE(connection,ISI_CONN_STATE) == isiConnectionStatePending)
                {
                    _IsiClearConnection(&connection, index);
                }
            savePersistentData(IsiNvdSegConnectionTable);   

            //
            // EPR 38983+38960: Part of the problem described in these EPRs is that enrollment cancellation, which might occur automatically as result of
            // receiving a new CSMO/A/R while being the host of another pending enrollment, does not notify the UI upon cancellation, so let's fire the
            // cancellation event instead of the isiNormal event
            _IsiUpdateUi(isiCancelled);
            // ASSUMES: isiStateNormal == 0
		    _isiVolatile.State &= ~CONNECTION_STATES;
	    }
        sts = IsiApiNoError;
    }
    _IsiAPIDebug("End IsiCancelEnrollment=%d\n", sts);
    return sts;
}

//	end of CancelE.c
