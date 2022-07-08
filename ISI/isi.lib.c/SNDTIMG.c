//	SndTimg.c	implementing _IsiSendTimg
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler
//	Revision 1, June 2005, Bernd Gauweiler, using _isiMessageLengthTable to determine total length of outgoing packet

#include "isi_int.h"

unsigned __IsiDasOverride = 0;

//	IsiSendTimg (DAS only) sends timing guideance messages.

void _IsiSendTimg(unsigned DeviceCount)
{
	LON_SET_ATTRIBUTE(isi_out.Msg.Timg,ISI_TIMG_ORIG,8u);
	isi_out.Msg.Timg.DeviceCountEstimate = DeviceCount;
	isi_out.Msg.Timg.ChannelType = _isiVolatile.ChannelType;

	_IsiBroadcast(isiTimg, ISI_PRIMARY_DOMAIN_INDEX, 1);
}

//	end of SndDrum.c
