//	MakeE.c	implementing IsiMakeEnrollment
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"



void _IsiMakeEnrollment(LonBool bExtend, unsigned Assembly) {
    const IsiConnection *pConnection;

    pConnection = IsiGetConnection(_isiVolatile.pendingConnection);

    if ((_isiVolatile.State & isiStateInvited) && pConnection->Host != Assembly) {
        // this happens on the guest, and causes acceptance (but not implementation) of the enrollment
        _IsiAcceptEnrollment(bExtend, Assembly);
    } else if ((_isiVolatile.State & isiStatePlannedParty) && pConnection->Host == Assembly) {
		// this happens on the host.
		// Note that, if two local assemblies are to take part, two calls must be made: one for the local member first,
		// then one for the (local) host. Although it is technically possible to combine both in one (just remove the
		// word "else" in the previous source code line), this would result in behavior different from the normal manual
		// ISI connection paradigm.
		_IsiImplementEnrollment(bExtend, Assembly);
#ifdef  ISI_SUPPORT_TURNAROUNDS
        // if turnaround support is enabled, other local assemblies might still be in waiting. Better clear it all out:
        _IsiUpdateUiAndState(isiStateNormal, isiNormal, ISI_NO_ASSEMBLY);
#endif  //  ISI_SUPPORT_TURNAROUNDS
    }
}

//	end of MakeE.c
