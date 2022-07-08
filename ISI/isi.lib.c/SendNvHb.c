//	SendNvHb.c	implementing _IsiSendNvHb
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, March 2005, Bernd Gauweiler

#ifdef WIN32
#include <control.h>
#endif
#include "isi_int.h"

#ifdef	ISI_SUPPORT_HEARTBEATS

static unsigned nextNv = 0;

LonBool _IsiIsHeartbeatCandidate(unsigned nv)
{
    union
    {
        const LonNvEcsConfig *pNv;
        const LonAliasEcsConfig *pAlias;
    } data;

#ifdef  ISI_SUPPORT_ALIAS
    unsigned aliasIndex;
#endif  //  ISI_SUPPORT_ALIAS

    data.pNv = IsiGetNv(nv);

    if (LON_GET_ATTRIBUTE_P(data.pNv, LON_NV_ECS_DIRECTION))    
    {
        // Say Yes (in principle) to output network variables
        if (LON_GET_ATTRIBUTE_P(data.pNv,LON_NV_ECS_SELHIGH) < 0x30u)
        {
            // the primary is bound. OK
            return TRUE;
        }
#ifdef  ISI_SUPPORT_ALIAS
        for (aliasIndex = 0; aliasIndex < AliasCount; ++aliasIndex)
        {
            data.pAlias = IsiGetAlias(aliasIndex);
            if (LON_GET_UNSIGNED_WORD(data.pAlias->Primary) == nv)
            {
                return TRUE;
            }
            watchdog_update();
        }
#endif  //  ISI_SUPPORT_ALIAS
    }
    return FALSE;
}

LonBool _IsiSendNvHb(void) {
    unsigned visited;
	LonBool hadOne;

    visited = hadOne = FALSE;

    while (!hadOne && visited++ < NvCount)
    {
        // _IsiIsHeartbeatCandidate says TRUE if the NV is an output and if the NV, or any of its aliases, is bound.
        if (_IsiIsHeartbeatCandidate(nextNv))
        {
            // IsiQueryHeartbeat is a callback typically overridden by the application. The default always says false
            // and never issues a heartbeat. The typical application override verifies that the NV index is good for
            // heartbeats and, if so, call IsiIssueHeartbeat() for this index. IsiIssueHeartbeat() must be called from
            // the application-defined override so that this code does not get linked to the application image unless
            // it is actually used.
            hadOne = IsiQueryHeartbeat(nextNv);
        }
        watchdog_update();
        ++nextNv;
        nextNv = nextNv % NvCount;
    }
	return hadOne;
}
#endif	//	ISI_SUPPORT_HEARTBEATS

//	end of SendNvHb.c
