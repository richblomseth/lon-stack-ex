//	Stop.c	implementing IsiStop
//
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

const IsiApiError IsiStop(void)
{
    _IsiAPIDebug("Start IsiStop\n");

	memset(&_isiVolatile, 0, (unsigned)sizeof(IsiVolatile));
	IsiUpdateUserInterface(isiRun, 0);

    savePersistentData(IsiNvdSegConnectionTable);
    savePersistentData(IsiNvdSegPersistent);

    IsiDeregisterAllCallbacks();

    // Close the trace file
    IsiSetTracefile(NULL, FALSE);

    return IsiApiNoError;
}

//	end of Stop.c
