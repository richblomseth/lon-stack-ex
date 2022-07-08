//	DefaultCallback.c	implementing Isi default callback
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.

#include "isi_int.h"
const LonBool isiFilterResponseArrived(const LonResponseAddress* const pAddress, const unsigned tag, 
                        const LonByte code, const LonByte* const pData, const unsigned dataLength)
{
    // The IsiProcessResponse returns FALSE if the response is processed by the ISI engine.
    LonBool retval = !IsiProcessResponse(_IsiGetCurrentType(), code, pData, dataLength);
    _IsiAPIDebug("isiFilterResponseArrived = %d\n", retval);
    return retval;
}

const LonBool isiFilterMsgArrived(const LonReceiveAddress* const pAddress,
                          const LonCorrelator correlator,
                          const LonBool priority,
                          const LonServiceType serviceType,
                          const LonBool authenticated,
                          const LonByte code,
                          const LonByte* const pData, const unsigned dataLength)
{
    LonBool retval = FALSE;
    LonBool isIsiApproveMsg;

    _IsiAPIDebug("Incoming MSG code %02X, length %u, data ", (unsigned)code, dataLength);
    _IsiAPIDump("0x", (void*)pData, dataLength, "\n");

    if (_IsiGetCurrentType() == isiTypeDas)
        isIsiApproveMsg = IsiApproveMsgDas(code, pData, dataLength);
    else
        isIsiApproveMsg = IsiApproveMsg(code, pData, dataLength);

    // The IsiProcessMsg returns FALSE if the message is processed by the ISI engine.  
    if (isIsiApproveMsg && (!IsiProcessMsg(_IsiGetCurrentType(), code, (IsiMessage *)pData, dataLength)
#ifdef	ISI_SUPPORT_CONTROLLED_CONNECTIONS
            || IsiProcessCtrlEnrollmentRequest(code, (IsiMessage *)pData, dataLength, correlator)
#endif
        ))
    {
        retval = TRUE;
    }
    // else the message does not get processed by the ISI engine.  Left for application to deal with.
    _IsiAPIDebug("isiFilterMsgArrivedStart = %d\n", retval);
    return retval;
}

//	end of DefaultCallback.c
