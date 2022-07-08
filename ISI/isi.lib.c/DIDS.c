//	dids.c	implementing _IsiVerifyDomainsS
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//  Revision 0, January 2005, Bernd Gauweiler

#include "isi_int.h"
#include <stddef.h>


//	the function makes sure both domain table entries are set up correctly in the default domains. This is the
//	standard behavior of an ISI-S device, and the default operation for ISI-DA/-DAS devices. Any custom domain
//	ID and length is accounted for by using the IsiGetPrimary*() functions.

//  July 2005, BG: This function now only looks after the primary domain, but does so for all devices ISI-S/DA/DAS.
//  It is no longer called from IsiStart*(), but from within _IsiInitialize(), and it is no longer being called
//  at each and every reset. However, the secondary domain must be taken care of every time, since LNS is pulling
//  the carpet under our feet otherwise. The code to update the secondary domain has therefore been moved from this
//  routine into _IsiInitialize.
void _IsiVerifyDomainsS(void)
{
	LonByte Length;
	const LonByte* pId;

	pId = IsiGetPrimaryDid(&Length);

#ifdef ISI_SUPPORT_DIAGNOSTICS
	if (_IsiSetDomain(ISI_PRIMARY_DOMAIN_INDEX, Length, pId, _GetIsiSubnet(), _GetIsiNode()))
    {
		_IsiConditionalDiagnostics(isiSubnetNodeAllocation, ISI_PRIMARY_DOMAIN_INDEX);
	}
#else
	(void)_IsiSetDomain(ISI_PRIMARY_DOMAIN_INDEX, Length, pId, _GetIsiSubnet(), _GetIsiNode());
#endif
}

