//	CreateE.c	implementing IsiCreateEnrollment
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//
//  Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

const IsiApiError IsiCreateEnrollment(unsigned Assembly)
{
    IsiApiError sts = IsiEngineNotRunning;
    _IsiAPIDebug("Start IsiCreateEnrollment - Assembly=%d\n", Assembly);

    if (_isiVolatile.Running)
    {
	    _IsiMakeEnrollment(FALSE, Assembly);
        sts = IsiApiNoError;
    }
    _IsiAPIDebug("End IsiCreateEnrollment=%d\n", sts);

    return sts;
}

//	end of CreateE.c
