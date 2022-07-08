//	AcceptE.c	implementing _IsiAcceptEnrollment
//
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//  Revision 0, February 2005, Bernd Gauweiler
//  Revision 1, September 2005, Bernd Gauweiler - supporting turnarounds

#ifdef WIN32
#include <control.h>
#endif
#include "isi_int.h"

void _IsiAcceptEnrollment(LonBool Extend, unsigned Assembly)
{
    //  Accepting an enrollment is a member-side operation: the host issues an invitation (CSMO), the receiving nodes pre-approve and might then decide
    //  to enroll - this is the acceptance process. Whether the connection gets established or not is a different matter (CSMC).
    //
    //	To accept an enrollment, do this:
    //	1. Find all pending connection table entries, and set their assembly number to Assembly.
    //	2. Also set their Extend flag according to the Extend parameter
    //	3. Change the local state to isiStateAccepted by cancelling the UI, and updating the UI for this assembly alone.
    //	4. Issue a CSME (which also schedules periodic re-issue of CSMEs)
    unsigned index;
    LonBool notified;
    IsiConnection ConnectionData;

    _IsiAPIDebug("Start _IsiAcceptEnrollment - Extend=%d Assembly=%d\n", Extend, Assembly);
    notified = FALSE;

    for (index = _isiVolatile.pendingConnection; _IsiNextConnection(index, &ConnectionData); ++index) 
    {
        if (LON_GET_ATTRIBUTE(ConnectionData,ISI_CONN_STATE) == isiConnectionStatePending)
        {
            LON_SET_ATTRIBUTE(ConnectionData,ISI_CONN_EXTEND,Extend);   //Extend;
            ConnectionData.Member = Assembly;       //  ... but enrolled.
		    watchdog_update();

#ifdef  ISI_SUPPORT_TURNAROUNDS
            if (ConnectionData.Host != ISI_NO_ASSEMBLY)
            {
                // We're also hosting this connection locally:
                LON_SET_ATTRIBUTE(ConnectionData,ISI_CONN_CSME,1);   // ConnectionData.HaveCsme = 1;
                if (!notified)
                {
                    // clear the UI state so that all assemblies return to normal
	                _IsiUpdateUiNormal();
                    // bring the host into the approved state
                    IsiUpdateUserInterface(isiApprovedHost, ConnectionData.Host);
                    // and the local member into the accepted state
                    _IsiUpdateUiAndStateEnroll(isiStateAccepted | isiStatePlannedParty, isiApproved, Assembly);
                    notified = TRUE;
                }
            }
            else if (!notified)
            {
                // not a local host: clear UI state so that the other assemblies stop flashing
                _IsiUpdateUiNormal();
                // and bring this assembly into the approved state
                _IsiUpdateUiAndStateEnroll(isiStateAccepted, isiApproved, Assembly);
                // also, because the host is remote, also issue a CSME:
                _IsiSendCsme();
                notified = TRUE;
            }
            IsiSetConnection(&ConnectionData, index);
#else
            if (!notified)
            {
                // not a local host: clear UI state so that the other assemblies stop flashing
    	        _IsiUpdateUiNormal();
                // and bring this assembly into the approved state
                _IsiUpdateUiAndStateEnroll(isiStateAccepted, isiApproved, Assembly);
                // also, because the host is remote, also issue a CSME:
                _IsiSendCsme();
                notified = TRUE;
            }
            IsiSetConnection(&ConnectionData, index);
#endif  //  ISI_SUPPORT_TURNAROUNDS
            savePersistentData(IsiNvdSegConnectionTable);
        }
    }
    _IsiAPIDebug("End _IsiAcceptEnrollment\n");
}

//	end of AcceptE.c
