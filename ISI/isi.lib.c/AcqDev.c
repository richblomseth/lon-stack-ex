//	AcqDev.c	implementing IsiStartDeviceAcquisition
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//  Revision 0, February 2005, Bernd Gauweiler
//  Revision 1, July 2005, Bernd: Now we are actually implementing it...

#include "isi_int.h"

#ifdef  ISI_SUPPORT_DADAS
void IsiStartDeviceAcquisition(void)
{
    _IsiAPIDebug("Start IsiStartDeviceAcquisition - Running=%d State=%d\n", _isiVolatile.Running, _isiVolatile.State);
    if (_isiVolatile.Running)
    {
        if (!_isiVolatile.State)
        {
            // Start the device acquisition process.
            goto StartAcquisition;
        }
        else if (_isiVolatile.State & isiStateAwaitConfirm)
        {
            // In this state, this function call is the second in a row and serves as a confirmation that the correct device
            // has winked. That is, we're good to go and can fire the confirmation message, notify the application, and
            // retrigger device acquisition:
            _IsiSendDidrm(isiDidcf);
            _IsiUpdateUi(isiRegistered);
StartAcquisition:
            _IsiUpdateUiAndStateTimeout(ISI_T_ACQ, isiStateAwaitDidrx, isiRegistered, 0);
        }
	}
    _IsiAPIDebug("End IsiStartDeviceAcquisition\n");
}
#endif  //  ISI_SUPPORT_DADAS

//	end of AcqDev.c
