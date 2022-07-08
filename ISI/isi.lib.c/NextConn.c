//	NextConn.c	implementing _IsiNextConnection
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler
//

#ifdef WIN32
#include <control.h>
#endif
#include "isi_int.h"

LonBool _IsiNextConnection(unsigned index, IsiConnection* pConn) {
	LonBool rv;

	rv = index < _isiVolatile.ConnectionTableSize;

	if (rv) {
		*pConn = *IsiGetConnection(index);
	}
    watchdog_update();
	return rv;
}

//	end of NextConn.c
