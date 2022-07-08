//	EstRead.c	implementing _IsiGetDasDeviceCountEst
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

// undocumented. Used for unit- and system testing. This allows the application to read back the current device count
// extimation. The function works for any device, DAS or not. On a DAS, it always returnes the current estimate (and
// never the override). On any other device, it returns the current estimate (there is no override).
LonByte _IsiGetDasDeviceCountEst(void) 
{
#ifdef ISI_SUPPORT_TIMG
	return _isiPersist.Devices;
#else
	return ISI_DEFAULT_DEVICECOUNT;
#endif	//	ISI_SUPPORT_TIMG
}

void _IsiSetDasDeviceCountEst(LonByte number)
{
#ifdef ISI_SUPPORT_TIMG
	_isiPersist.Devices = number;
#else
	_isiPersist.Devices = ISI_DEFAULT_DEVICECOUNT;
#endif
    if (IsiIsRunning())
        savePersistentData(IsiNvdSegPersistent);
}
