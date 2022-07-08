//	MsgS.c	implementing IsiProcessMsgS
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler
//	Revision 1, June 2005, Bernd Gauweiler: Added support for DRUMEX, CSMOEX, CSMAEX, and CSMREX messages


#include "isi_int.h"

LonBool IsiProcessMsgS(const LonByte code, const IsiMessage* msgIn, const unsigned dataLength)
{
#ifdef	ISI_SUPPORT_AUTOMATIC_CONNECTIONS
	LonBool Auto, ShortForm;
	Auto = ShortForm = FALSE;
#else
	LonBool ShortForm;
	ShortForm = FALSE;
#endif	//	ISI_SUPPORT_AUTOMATIC_CONNECTIONS

	// reset the spreading timer:
	_isiVolatile.Spreading = 0;

	switch(msgIn->Header.Code)
    {
		case isiDrumEx:
			// ASSUMES: fall-through because ISI ignores the "Extended" DRUM fields.
		case isiDrum:
			//
			// Receive DRUM	-	Domain Resource Usage Message
			//
			_IsiReceiveDrumS(msgIn);
			break;
#ifdef	ISI_SUPPORT_TIMG
		case isiTimg:
			//
			// Receive TIMG	-	Timing Guideance Message
			//
			_IsiReceiveTimg(msgIn->Msg.Timg.DeviceCountEstimate, msgIn->Msg.Timg.ChannelType);
			break;
#endif	//	ISI_SUPPORT_TIMG
#ifdef	ISI_SUPPORT_AUTOMATIC_CONNECTIONS
		case isiCsmo:
			ShortForm = TRUE;
			goto HandleCsmoX;
		case isiCsma:
		case isiCsmr:
			ShortForm = TRUE;
			// FALL-THROUGH:
		case isiCsmaEx:
		case isiCsmrEx:
			//
			// Receive CSMA + CSMR:	Automatic enrollment + reminder
			//
			Auto = TRUE;
			// FALL THROUGH:
		case isiCsmoEx:
			//
			// Receive CSMO	-	Open Enrollment
			//
HandleCsmoX:
			_IsiReceiveCsmo(Auto, ShortForm, &msgIn->Msg.Csmo);
			break;
#else
		case isiCsmo:
			ShortForm = TRUE;
			// FALL-THROUGH:
		case isiCsmoEx:
			_IsiReceiveCsmo(FALSE, ShortForm, &msgIn->Msg.Csmo);
			break;
#endif	//	ISI_SUPPORT_AUTOMATIC_CONNECTIONS
#ifdef	ISI_SUPPORT_MANUAL_CONNECTIONS
		case isiCsmx:
			//
			// Receive CSMX	-	Cancel pending enrollment
			//
			_IsiReceiveCsmx(&msgIn->Msg.Csmx);
			break;
		case isiCsmc:
			//
			// Receive CSMC	-	Confirm pending enrollment
			//
			_IsiReceiveCsmc(&msgIn->Msg.Csmc);
			break;
		case isiCsme:
			//
			// Receive CSME	-	Accept pending enrollment
			//
			_IsiReceiveCsme(&msgIn->Msg.Csme);
			break;
#endif	//	ISI_SUPPORT_MANUAL_CONNECTIONS
#ifdef ISI_SUPPORT_CONNECTION_REMOVAL
		case isiCsmd:
			//
			// Receive CSMD	-	Delete enrollment
			//
			_IsiReceiveCsmd(&msgIn->Msg.Csmd);
			break;
#endif	//	ISI_SUPPORT_CONNECTION_REMOVAL
		case isiCsmi:
			//
			// Receive CSMI	-	Connection Status Information
			//
			_IsiReceivePtrCsmi(&msgIn->Msg.Csmi);
			break;
		default:
			// message not recognized; return TRUE to indicate a caller may post-process the message (it is still valid)
			return TRUE;
	}
	return FALSE;
}

//	end of MsgS.c
