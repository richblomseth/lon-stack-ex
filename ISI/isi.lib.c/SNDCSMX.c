//	SndCsmx.c	implementing _IsiSendCsmx
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

void _IsiSendCsmx(void) {
	_IsiSendCsmex(TRUE, isiCsmx, 3);
}

//	end of SndCsmx.c
