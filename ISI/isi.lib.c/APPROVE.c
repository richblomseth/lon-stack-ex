//	Approve.c	implementing IsiApproveMsg
//
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//  Revision 0, February 2005, Bernd Gauweiler
//  Revision 1, June 2005, Bernd Gauweiler: replace signature mechanism with code-length validation (EPR 37390)


#include "isi_int.h"

//	return TRUE if this seems like an ISI message: application message code and length OK.

// The LengthTable table contains the size of each possible ISI message 0..isiLastCode. This table is accessed from other routines,
// too: sending DRUM/DRUMEX, CSMA/CSMAEX, CSMO/EX and CSMR/EX access that table to obtain the correct transmit size as a function
// of the message code use.
//	ASSUMES: ISI Message codes are sequential and start at zero.
const unsigned _isiMessageLengthTable[] = {
	// 0-4:
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiDrum) - (unsigned)sizeof(isi_out.Msg.Drum.Extended),		//	DRUM
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiDrum),		//	DRUMEX
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiCsmo) - (unsigned)sizeof(isi_out.Msg.Csmo.Data.Extended),	//	CSMO
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiCsmo),		//	CSMOEX
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiCsma) - (unsigned)sizeof(isi_out.Msg.Csma.Data.Extended),	//	CSMA
	// 5-9:
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiCsma),		//	CSMAEX
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiCsmr) - (unsigned)sizeof(isi_out.Msg.Csmr.Data.Extended),	//	CSMR
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiCsmr),		//	CSMREX
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiDidrq),	//	DIDRQ
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiDidrm),	// 	DIDRM
	// 10-14
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiDidcf),	// 	DIDCF
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiTimg),		//	TIMG
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiCsmx),		//	CSMX
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiCsmc),		// 	CSMC
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiCsme),		//	CSME
	//	15-19:
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiCsmd),		//	CSMD
	(unsigned)sizeof(IsiMessageHeader) + (unsigned)sizeof(IsiCsmi)		//	CSMI
};

// Returns FALSE, if it's not an ISI approve message
// Returns TRUE, otherwise.
LonBool IsiApproveMsg(const LonByte code, const LonByte* msgIn, const unsigned dataLength)
{
    unsigned ActualLength;
    IsiMessageCode ReceivedCode;
    unsigned ExpectedLength;
    LonBool retval = FALSE;

    _IsiAPIDebug("Start IsiApproveMsg - Code=%d Len=%d\n", code, dataLength);
    if (_isiVolatile.Running && code == LonApplicationIsi)
    {
        // This might be a genuine ISI message.
        // Now we need verifying that the incoming message is at least as long as indicated by LengthTable,
        // and no more than 4 bytes more than that. We also verify that the "code" field of the incoming message lies in 
        // the supported range. Because we test the entire code byte rather than just the least signifficant 5 bit, we
        // automatically approve that the protocol version (which might be in the most signifficant 3 bit) is zero.
        // ASSUMES: Three MSB of the code byte are zero (indicating protocol version 1)
        IsiMessage *pIsiMsg  = (IsiMessage*)msgIn;
        ActualLength = dataLength;              // _msg_len_get_ex();
        ReceivedCode = pIsiMsg->Header.Code;    // _IsiGetMsgInDataPtr()->Header.Code;
        _IsiAPIDebug("ReceivedCode=%d\n", ReceivedCode);
        if (ReceivedCode <= isiLastCode)
        {
            ExpectedLength = _isiMessageLengthTable[ReceivedCode];
            _IsiAPIDebug("ExpectedLength=%d ActualLength=%d\n", ExpectedLength, ActualLength);
			// we allow messages that provide the minimum number of bytes required, but also allow a few more bytes.
			// These additional bytes might be required for backwards-compatible changes to the protocol (by appending 
			// new fields to existing structures):		
			retval = (ActualLength >= ExpectedLength) && (ActualLength <= (ExpectedLength + ISI_MESSAGE_HEADROOM));
		}
     	}
    _IsiAPIDebug("End IsiApproveMsg = %d\n", retval);
	return retval;
}

//	end of Approve.c
