//	ApprDas.c	implementing IsiApproveMsgDas
//
// IsiApproveMsgDas() must be used with DAS devices - at least if the IsiFetchDomain() function is used
// (i.e. the domain sniffing process is supported). Technically a DAS may chose not to support sniffing
// and can safe a few bytes by using IsiApproveMsg() therefore, but it is recommended that DAS should
// support sniffing to support DAS replacement and redundancy.
//
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
// Revision 0, July 2005, Bernd Gauweiler
//

#include "isi_int.h"

LonBool IsiApproveMsgDas(const LonByte code, const LonByte* msgIn, const unsigned dataLength)
{
    return (IsiApproveMsg(code, msgIn, dataLength) || (_isiVolatile.Running && (isiDasExtState & isiDasCollect) && (code == LONTALK_SERVICE_PIN_MESSAGE)));
}

//	end of ApprDas.c
