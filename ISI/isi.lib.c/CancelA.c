//	CancelA.c	implementing IsiCancelAcquisition
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//  Revision 0, July 2005, Bernd Gauweiler

#include "isi_int.h"

// IsiCancelAcquisition() is now available both on ISI-DA and ISI-DAS devices and does just what the name suggests.
// The cancellation applies to both device and domain acquisition. A UI event isiNormal will be fired to assist the
// application with the UI maintenance.

#ifdef  ISI_SUPPORT_DADAS
void IsiCancelAcquisition(void) {
    if (_isiVolatile.Running && (_isiVolatile.State & (isiStateAwaitDidrx | isiStateAwaitConfirm | isiStateCollect | isiStateAwaitQdr))) {
        isiDasExtState = isiDasNormal;
        _IsiUpdateUiAndStateTimeout(0, isiStateNormal, isiNormal, ISI_NO_ASSEMBLY);
    }
}
#endif  //  ISI_SUPPORT_DADAS
        //
//	end of CancelA.c
