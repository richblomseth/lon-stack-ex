//	Slot.c	implementing _IsiAllocSlot
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler
//

#include "isi_int.h"

//	 _IsiAllocSlot	re-throws the dice: it randomly picks a slot (a number between 1 and the total number of known ISI devices on the media),
//	and computes the number of ticks to wait until then
#ifdef ISI_SUPPORT_TIMG
unsigned long _IsiAllocSlot(unsigned Devices) {
	return _IsiRand(Devices, 0) * (unsigned long)_isiVolatile.Transport.TicksPerSlot;
}
#else
unsigned long _IsiAllocSlot(void) {
	return _IsiRand(ISI_DEFAULT_DEVICECOUNT, 0) * (unsigned long)_isiVolatile.Transport.TicksPerSlot;
}
#endif	//	ISI_SUPPORT_TIMG
//	end of Slot.c
