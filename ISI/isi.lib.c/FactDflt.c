//	FactDflt.c	implementing IsiReturnToFactoryDefaults
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"
#ifdef WIN32
#include <control.h>
#endif

const IsiApiError IsiReturnToFactoryDefaults(void)
{
    IsiApiError sts = IsiEngineNotRunning;

    _IsiAPIDebug("Start IsiReturnToFactoryDefaults\n");
	// resetting the NUID to zero forces complete re-initialization:
    if (_isiVolatile.Running) 
    {
	    _isiPersist.BootType = isiReboot;
	    _IsiInitialize(isiFlagNone);
	    node_reset();
        sts = IsiApiNoError;
    }
    _IsiAPIDebug("End IsiReturnToFactoryDefaults=%d\n", sts);
    return sts;
}

//	end of FactDflt.c
    