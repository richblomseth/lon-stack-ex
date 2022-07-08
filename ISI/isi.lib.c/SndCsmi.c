//	SndCsmi.c	implementing _IsiSendCsmi
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler
//	Revision 1, June 2005, Bernd Gauweiler, using _isiMessageLengthTable to determine total length of outgoing packet


#include "isi_int.h"

void _IsiSendCsmi(const IsiConnection* pConnection)
{
	_IsiCreateCsmi(pConnection, &isi_out.Msg.Csmi);
	_IsiBroadcast(isiCsmi, ISI_PRIMARY_DOMAIN_INDEX, 1);
}
//	end of SndPCsmi.c
