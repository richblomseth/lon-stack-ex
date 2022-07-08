//	EstOverr.c	implementing _IsiSetDasDeviceCountOverride
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//  Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

extern unsigned __IsiDasOverride;

//	undocumented. Used for unit- and system testing. It allows overriding the current DAS' device count estimation
//	for the purpose of testing. This function can only be used with DAS devices; using it on other devices will result
//	in erratic behavior.
void _IsiSetDasDeviceCountOverride(unsigned Value) {
	__IsiDasOverride = Value;
	if (Value) {
		// we override the estimation. this forces us to re-allocate the slot,
		// as we might be sitting forever otherwise (forever meaning: according
		// to the previous estimation or override).
#ifdef	ISI_SUPPORT_TIMG
		_isiVolatile.Wait =	_IsiAllocSlot(Value);
#else
		_isiVolatile.Wait =	_IsiAllocSlot();
#endif	//	ISI_SUPPORT_TIMG
	}
}

