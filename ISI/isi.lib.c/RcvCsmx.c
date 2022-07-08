//	RcvCsmx.c	implementing _IsiReceiveCsmx
//
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

//	Notice the _IsiReceiveCsmx() function is called whenever a CSMX (connection cancellation) message comes in,
//	and when _IsiReceiveCsmc() (CSMC = connection confirmation) detects that we might still be pending for a no
//	longer valid enrollment.

void _IsiReceiveCsmx(const IsiCsmx* pCsmx)
{
    unsigned Connection;
    IsiConnection ConnectionData;

    _IsiAPIDebug("_IsiReceiveCsmx ");
    _IsiAPIDump("0x", (void *)pCsmx, sizeof(IsiCsmx), "\n");

	if (_isiVolatile.State & CONNECTION_STATES)
    {
        for (Connection = 0; _IsiNextConnection(Connection, &ConnectionData); ++Connection)
        {
            if ((LON_GET_ATTRIBUTE(ConnectionData,ISI_CONN_STATE)  == isiConnectionStatePending)
                && !memcmp(&ConnectionData.Header.Cid, &pCsmx->Cid, (unsigned)sizeof(IsiCid)))
            {
                // match. Cancel this one locally - notice we must cancel for all assemblies (hence ISI_NO_ASSEMBLY,
                // which should be read in this context as "no specific assembly". This is required because, subject
                // to this device's local enrollment status, specific assemblies might not yet be known and registered
                // in the connection table record.
                IsiUpdateUserInterface(isiCancelled, ISI_NO_ASSEMBLY);
                _isiVolatile.State &= ~CONNECTION_STATES;
            }
        }
	}
}

//	end of RcvCsmx.c
