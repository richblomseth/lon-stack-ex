//	ClrConn.c	implementing _IsiClearConnection
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//  Revision 0, March 2005, Bernd Gauweiler

#include "isi_int.h"
//#include <mem.h>

void _IsiClearConnection(IsiConnection* pConn, unsigned Index) {
	memset(pConn, 0, (unsigned)sizeof(IsiConnection));
	IsiSetConnection(pConn, Index);
}

//	end of ClrConn.c
