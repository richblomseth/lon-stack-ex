//	Send.c	implementing implementing IsiMsgSend and IsiBroadcast
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//

#include "isi_int.h"
#include "FtxlApiInternal.h"
#ifdef WIN32
#include <control.h>
#endif

void _IsiBroadcast(IsiMessageCode code, unsigned domain, unsigned repeats)
{
	LonSendAddress destination;

	if (code < isiLastEx)
        code += (_isiVolatile.Flags & isiFlagExtended);
	isi_out.Header.Code = code;
	destination.Broadcast.Type = LonAddressBroadcast;
    // domain = domain
    // backlog = 0
    LON_SET_ATTRIBUTE(destination.Broadcast,LON_SENDBCAST_DOMAIN, domain);
    LON_SET_ATTRIBUTE(destination.Broadcast,LON_SENDBCAST_BACKLOG, 0);
	//destination.bc.rpt_timer = _isiVolatile.Transport.RepeatTimer;
	//destination.bc.retry = repeats;
    LON_SET_ATTRIBUTE(destination.Broadcast,LON_SENDBCAST_REPEAT_TIMER,_isiVolatile.Transport.RepeatTimer>>4);
    LON_SET_ATTRIBUTE(destination.Broadcast,LON_SENDBCAST_RETRY,repeats);

    // destination.bc.tx_timer = 0;
    destination.Broadcast.RsvdTransmit = 0;
	// destination.bc.subnet = 0;
    destination.Broadcast.Subnet = 0;
    _IsiAPIDebug("_IsiBroadcast IsiMessageCode = %d Message: \n", code);
    _IsiAPIDump("0x", &isi_out.Msg, sizeof(isi_out.Msg), "\n");
    _IsiAPIDebug("_IsiBroadcast IsiMessageCode = %d Header: \n", code);
    _IsiAPIDump("0x", &isi_out.Header, sizeof(isi_out.Header), "\n");

 	IsiMsgSend(&isi_out, _isiMessageLengthTable[code], LonServiceUnacknowledged, &destination);
}

void _IsiSendIsi(LonServiceType serviceType, const void* pOut, unsigned len, LonSendAddress* pDestination)
{
    _IsiSend(ISI_MESSAGE_CODE, serviceType, pOut, len, pDestination);
}

void _IsiSend(unsigned LonTalkCode, LonServiceType serviceType, const void* pOut, unsigned len, const LonSendAddress* pDestination)
{
    //msg_out.service = serviceType;
    //msg_out.code = LonTalkCode;
    //msg_out.tag = ISI_MESSAGE_TAG;
//  IsiMsgDeliver(pOut, len, pDestination);
    _IsiAPIDebug("Start _IsiSend - LonTalkCode=%d LonServiceType=%d Len=%d\n", LonTalkCode,serviceType,len);

    LonSendMsg(ISI_MESSAGE_TAG,         /* const unsigned tag, */
                FALSE,                   /* const LonBool priority, */
                serviceType,            /* const LonServiceType st, */ 
                TRUE,                   /* const LonBool authenticated, */
                pDestination,           /* const LonSendAddress* const pDestAddr, */
                LonTalkCode,            /* const LonByte code, */
                pOut,                   /* const LonByte* const pData, */
                len);                   /* const unsigned length) */
    _IsiAPIDebug("End _IsiSend\n", LonTalkCode,serviceType,len);
}

// _IsiNidDestination requires ShiftedDomainIndex, i.e. 0 for the primary domain, but 0x80 (1 << 7) for the secondary. We can pass this as a constant and
// safe some code by not having to shift in the _IsiNidDestination routine.
void _IsiNidDestination(LonSendAddress* pDestination, unsigned ShiftedDomainIndex, unsigned repeats, const LonByte* pNid)
{
    // Notice the "ShiftedDomainIndex" parameter. In the C equivalent implementation, we'd use 0 or 1 for the domain index,
    // and assign this value to pDestination->nrnid.domain. This field is a bitfield, with the remainder of the byte being
    // zero. Thus, in the assembly routine, we just take the value for the entire byte (0x00 for the primary and 0x80 for
    // the secondary domain) and -unlike the C implementation- safe some shifts one way or the other.

    pDestination->UniqueId.Type = LonAddressUniqueId;
    pDestination->UniqueId.Domain = ShiftedDomainIndex >> 7;
    LON_SET_ATTRIBUTE(pDestination->UniqueId, LON_SENDNID_REPEAT_TIMER, _isiVolatile.Transport.RepeatTimer >> 4);
    LON_SET_ATTRIBUTE(pDestination->UniqueId, LON_SENDNID_RETRY, repeats);
    LON_SET_ATTRIBUTE(pDestination->UniqueId, LON_SENDNID_TRANSMIT_TIMER,_isiVolatile.Transport.TransmitTimer);
    pDestination->UniqueId.Subnet = 0;
    memcpy(pDestination->UniqueId.NeuronId, pNid, NEURON_ID_LEN);
}


//	end of send.c
