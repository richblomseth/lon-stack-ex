//	fetch.c	implementing IsiFetchDomain
//
//  IsiFetchDomain() kick-starts the domain sniffing process, which is used by a DAS to obtain the current domain ID
//  from any other device in the network. This remote device, the "domain ID donor", does not need to be a DAS itself,
//  since the entire procedure only uses standard messages (service pin and query domain).
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, July 2005, Bernd Gauweiler

#include "isi_int.h"

LonByte donorId[NEURON_ID_LEN];     //  the neuron ID of the donor device, or all zeroes if none

#ifdef  ISI_SUPPORT_DADAS
static void IsiFetchXxx(void)
{
    if (_isiVolatile.Running && !_isiVolatile.State)
    {
        // clear the donor ID:
        memset(donorId, 0, NEURON_ID_LEN);
        _IsiUpdateUiAndStateTimeout(ISI_T_ACQ, isiStateCollect, isiRegistered, 0);
    }
}

const IsiApiError IsiFetchDomain(void)
{
    IsiApiError sts = IsiEngineNotRunning;

    _IsiAPIDebug("Start IsiFetchDomain\n");
    if (_isiVolatile.Running)
    {
        isiDasExtState = isiDasFetchDomain;
        IsiFetchXxx();
        sts = IsiApiNoError;
    }
    _IsiAPIDebug("End IsiFetchDomain=%d\n", sts);
    return sts;
}

const IsiApiError IsiFetchDevice(void)
{
    IsiApiError sts = IsiEngineNotRunning;

    _IsiAPIDebug("Start IsiFetchDevice\n");
    if (_isiVolatile.Running)
    {
        isiDasExtState = isiDasFetchDevice_Query;
        IsiFetchXxx();
        sts = IsiApiNoError;
    }
    _IsiAPIDebug("End IsiFetchDevice=%d\n", sts);
    return sts;
}
#endif  //  ISI_SUPPORT_DADAS

//	end of fetch.c
