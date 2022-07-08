//	AutoEnro.c	implementing IsiInitiateAutoEnrollment
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//  Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

#ifdef	ISI_SUPPORT_AUTOMATIC_CONNECTIONS
IsiApiError IsiInitiateAutoEnrollment(const IsiCsmoData* pCsmaData, unsigned Assembly)
{
    IsiApiError sts = IsiEngineNotRunning;

    if (_isiVolatile.Running)
    {
        sts = IsiApiNoError;
	    if (_isiVolatile.Startup >= ISI_T_AUTO
	        && !IsiIsAutomaticallyEnrolled(Assembly))
        {
            if (_IsiBecomeHost(Assembly, TRUE, pCsmaData))
            {
			    _isiVolatile.State = isiStatePlannedParty;
			    IsiCreateEnrollment(Assembly);
		    }
            else
                sts = IsiNoConnectionSpace;
    	}
    }
    return sts;
}
#endif	//	ISI_SUPPORT_AUTOMATIC_CONNECTIONS

//	end of AutoEnro.c
