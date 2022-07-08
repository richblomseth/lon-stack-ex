//	IsCfg.c	implementing IsiIsConfiguredOnline
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"
#include "FtxlApiInternal.h"

#if 0
#include <status.h>
#endif

LonBool IsiIsConfiguredOnline(void)
{
	LonStatus status;
    memset(&status, 0, sizeof(LonStatus)); 
	retrieve_status(&status);

	return status.NodeState == 0x04;
}

//	end of IsCfg.c
