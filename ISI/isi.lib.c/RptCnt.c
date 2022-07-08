//	RptCnt.c	implementing IsiGetRepeatCount
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//
//	Revision 0, June 2005, Bernd Gauweiler

#include "isi_int.h"

unsigned RepeatCount = ISI_NV_UPDATE_RETRIES;

//	The IsiGetRepeatCount callback gets called whenever the connection table needs initializing: at the first power-up with a new
//	application, or when returning to factory defaults. Applications may override this callback, but only repeat count values 1, 
//	2, or 3 are supported. See _IsiInitialize() for a detailed discussion.

unsigned IsiGetRepeatCount(void)
{
	return RepeatCount;
}
void IsiSetRepeatCount(unsigned Count)
{
    RepeatCount = Count;
}

//	end of RptCnt.c
