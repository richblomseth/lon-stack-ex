//	RcvCsmd.c	implementing _IsiReceiveCsmd
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

#ifdef	ISI_SUPPORT_CONNECTION_REMOVAL
void _IsiReceiveCsmd(const IsiCsmd* pCsmd)
{
	unsigned Connection;
	IsiConnection ConnectionData;

    _IsiAPIDebug("_IsiReceiveCsmd ");
    _IsiAPIDump("0x", (void *)pCsmd, sizeof(IsiCsmd), "\n");

	for (Connection = 0; _IsiNextConnection(Connection, &ConnectionData); ++Connection)
    {
		if (LON_GET_ATTRIBUTE(ConnectionData,ISI_CONN_STATE) >= isiConnectionStateInUse
		    && !memcmp(&ConnectionData.Header.Cid, &pCsmd->Cid, (unsigned)sizeof(IsiCid)))
        {
			// match. Remove this one locally:
            _IsiRemovePtrConnection(&ConnectionData, ConnectionData.Member);
			_IsiRemovePtrConnection(&ConnectionData, ConnectionData.Host);
			// clear this connection table entry:
			_IsiClearConnection(&ConnectionData, Connection);
		}
	}
    savePersistentData(IsiNvdSegConnectionTable);   

    // tidy-up the address table:
    _IsiSweepAddressTable();
}
#endif	//	ISI_SUPPORT_CONNECTION_REMOVAL

//	end of RcvCsmd.c
