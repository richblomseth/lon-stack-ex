//	RcvCsme.c	implementing _IsiReceiveCsme
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

void _IsiReceiveCsme(const IsiCsme* pCsme)
{
	IsiConnection Connection;
    LonByte haveCsme;

    _IsiAPIDebug("_IsiReceiveCsme ");
    _IsiAPIDump("0x", (void *)pCsme, sizeof(IsiCsme), "\n");

    if (_isiVolatile.State & isiStateInviting)
    {
        Connection = *IsiGetConnection(_isiVolatile.pendingConnection);

        haveCsme = LON_GET_ATTRIBUTE(Connection,ISI_CONN_CSME);

        if ( !haveCsme        //        .HaveCsme)
            && (Connection.Host != ISI_NO_ASSEMBLY)
            && !memcmp(&Connection.Header.Cid, &pCsme->Cid, (unsigned)sizeof(IsiCid)) )
        {
            Connection.Attributes1 |= (1 << ISI_CONN_CSME_SHIFT);	// only set this with the first applicable connection table entry! See Implemnt.c for reason
            IsiSetConnection(&Connection, _isiVolatile.pendingConnection);
            savePersistentData(IsiNvdSegConnectionTable);
#ifdef  ISI_SUPPORT_TURNAROUNDS
            IsiUpdateUserInterface(isiApprovedHost, Connection.Host);
            _isiVolatile.State &= ~HOST_STATES;
            _isiVolatile.State |= isiStatePlannedParty;
#else
            _IsiUpdateUiAndState(isiStatePlannedParty, isiApprovedHost, Connection.Host);
#endif  //  ISI_SUPPORT_TURNAROUNDS

		}
	}
}

//	end of RcvCsme.c
