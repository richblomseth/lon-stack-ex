//	appper.c	implementing IsiCreatePeriodicMsg
//
//	This is the default implementation, which always says "no".
//	Notice the ISI implementation calls _IsiConditionalPeriodic()
//	function, which conditionally forwards to this function.
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, January 2005, Bernd Gauweiler

#include "isi_int.h"

LonBool isiCreatePeriodicMsg(void)
{
	return FALSE;
}

