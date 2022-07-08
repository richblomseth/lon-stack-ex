//	SendMsg.c	implementing IsiMsgSend
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, July 2005, Bernd Gauweiler

#include "isi_int.h"

//  IsiMsgSend simply calls _IsiSendIsi with the parameters in the right stack order. The IsiMsgSend API may be used by
//  those applications that extened ISI in some useful way, but it is not used by the library internally. Internally,
//  we use the _IsiSendIsi function or anyhthing that layers on top of that (see send.ns). The fact that IsiMsgSend() was
//  defined, implemented and documented with an inconvenient parameter order was discovered late in the game; changing
//  the API a few days short of version 1 RTM didn't seem a good choice.
//  This function used to be documented because we had it anyway (on the rather off chance that someone might find it
//  useful), and now we don't use it anymore internally and provide it because it's documented.
void IsiMsgSend(const IsiMessage* pMsg, unsigned IsiMessageLength, LonServiceType Service, LonSendAddress* pDestination)
{
    _IsiSendIsi(Service, pMsg, IsiMessageLength, pDestination);
}

//	end of SendMsg.c
