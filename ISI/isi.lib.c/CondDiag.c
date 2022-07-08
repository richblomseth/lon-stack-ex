//	CondDiag.c	implementing _IsiConditionalDiagnostics
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//  Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

//	Note that calls to IsiUpdateDiagnostics are not only made through this
//	conditional forwarder (in order to control overhead uplink traffic for
//	shortstack, or general overhead burden in all cases), but that this is
//	also a feature controlled via the ISI_SUPPORT_DIAGNOSTICS macro, defined in
//	isi_int.h
//	This allows to create a library version with smaller footprint (and without
//	support for IsiUpdateDiagnostics), and a (slightly) larger one that
//	supports this callback.
//	Whether we're going to use this remains to be seen (subject to resulting ISI
//	footprint), but at least it's in place.

void _IsiConditionalDiagnostics(IsiDiagnostic Event, unsigned Parameter) {
	if (_isiVolatile.Flags & isiFlagSupplyDiagnostics) {
		IsiUpdateDiagnostics(Event, Parameter);
	}
}

//	end of CondDiag.c
