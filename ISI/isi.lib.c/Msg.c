//	msg.c	implementing IsiProcessMsg
//
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, January 2005, Bernd Gauweiler

#include "isi_int.h"

LonBool IsiProcessMsg(IsiType Type, const LonByte code, const IsiMessage* msgIn, const unsigned dataLength)
{
	if (Type == isiTypeDas)
    {
		return IsiProcessMsgDas(code, msgIn, dataLength);
	} 
    else if (Type == isiTypeDa) 
    {
		return IsiProcessMsgDa(code, msgIn, dataLength);
	}
	return IsiProcessMsgS(code, msgIn, dataLength);
}

