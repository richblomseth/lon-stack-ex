//	SndCsmr.c	implementing _IsiSendCsmr
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//
//	Revision 0, February 2005, Bernd Gauweiler
//	Revision 1, June 2005, Bernd Gauweiler: added support for CSMR and CSMREX short and extended messages


#include "isi_int.h"
//#include <mem.h>

void _IsiSendCsmr(unsigned Index, const IsiConnection* pConnection)
{
#ifdef  ISI_SUPPORT_DADAS
    IsiConnection connection = *pConnection;

    _IsiAPIDebug("Start _IsiSendCsmr - Index=%d ConnectionState=%d\n", Index, LON_GET_ATTRIBUTE_P(pConnection,ISI_CONN_STATE));

    IsiCreateCsmo(connection.Host, &isi_out.Msg.Csmr.Data);
    memcpy(&isi_out.Msg.Csmr.Header, &connection.Header, (unsigned)sizeof(connection.Header));
    // A device supporting automatic connections and ISI-DA or ISI-DAS is supposed to monitor DIDCF messages,
    // and Tcsmr after receiving a Tcsmr message, to broadcast all CSMR messages - the idea is to speed up the
    // automatic connection process when a new device is registered on the domain. To do so, each ISI-DA(S)
    // device receiving a DIDCF flags all automatic, locally hosted, connections with that new state.
    // Whenever the regular broadcaster sends a CSMR, it resets this connections's state to isiConnectionStateInUse.
    // When the Tcsmr timer expires following the receipt of a DIDCF, the TickDA and TickDas routines broadcast
    // each remaining CSMR.
    if (LON_GET_ATTRIBUTE_P(pConnection,ISI_CONN_STATE) > isiConnectionStateInUse)
    {
        LON_SET_ATTRIBUTE(connection,ISI_CONN_STATE,isiConnectionStateInUse);
        IsiSetConnection(&connection, Index);
        savePersistentData(IsiNvdSegConnectionTable);
    }
#else
    IsiCreateCsmo(pConnection->Host, &isi_out.Msg.Csmr.Data);
    memcpy(&isi_out.Msg.Csmr.Header, &pConnection->Header, (unsigned)sizeof(pConnection->Header));
#   pragma  ignore_notused  Index
#endif
    _IsiBroadcast(isiCsmr, ISI_PRIMARY_DOMAIN_INDEX, 1);
    _IsiAPIDebug("End _IsiSendCsmr\n");
}

//	end of SndCsmr.c
