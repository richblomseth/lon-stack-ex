//	RsndCsmo.c	implementing _IsiResendCsmo
//
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//
//	Revision 0, February 2005, Bernd Gauweiler
//	Revision 1, June 2005, Bernd Gauweiler: Added support for extended messages, EPR 37387
//

#include "isi_int.h"

void _IsiResendCsmo(void)
{
	const IsiConnection *pConnection;

    _IsiAPIDebug("Start _IsiResendCsmo - PendingConnection=%d\n", _isiVolatile.pendingConnection);
	memset(&isi_out, 0, (unsigned)sizeof(IsiMessage));

    if (_isiVolatile.pendingConnection != ISI_NO_INDEX)
    {
        pConnection = IsiGetConnection(_isiVolatile.pendingConnection);
        // The second part of this expression is equivalent to if (ConnectionData.Desc.Host && ConnectionData.Desc.Offset == 0)
        if (!(pConnection->Desc.OffsetAuto & ConnectionOffset_MASK) && pConnection->Host != ISI_NO_ASSEMBLY)
        {
            IsiCreateCsmo(pConnection->Host, &isi_out.Msg.Csmo.Data);
            memcpy(&isi_out.Msg.Csmo.Header, &pConnection->Header, (unsigned)sizeof(IsiConnectionHeader));
            _IsiBroadcast(isiCsmo, ISI_PRIMARY_DOMAIN_INDEX, 1);
        }
    }
    _IsiAPIDebug("End _IsiResendCsmo\n");
}

//	end of RsndCsmo.c
