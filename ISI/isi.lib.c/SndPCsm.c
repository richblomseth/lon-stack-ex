//	SndPCsm.c	implementing _IsiSendCsmX
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

void _IsiSendCsmX(const IsiConnection* pConnection, IsiMessageCode Code, unsigned Repeats)
{
    _IsiAPIDebug("Start _IsiSendCsmX - Code=%d Repeats=%d\n", Code, Repeats);
	memcpy(&isi_out.Msg.Csme, &pConnection->Header, (unsigned)sizeof(pConnection->Header));
	_IsiBroadcast(Code, ISI_PRIMARY_DOMAIN_INDEX, Repeats);
    _IsiAPIDebug("End _IsiSendCsmX\n");
}

//	end of SndPCsm.c
