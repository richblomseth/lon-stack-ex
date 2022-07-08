//	HaveBdAl.c	implementing _IsiHaveBoundAlias
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

//	HaveBoundAlias returns true of the NV with the given index has an alias that is bound, and associated with the primary NV. This is used by the
//	routine that takes care of heartbeats; ISI connections may end up in situations where the primary NV is unbound while aliases to that NV are
//	still bound.
//	The function returns ISI_NO_INDEX if there is no such alias, and returns an alias table index greater than or equal to AliasIndex otherwise.

#ifdef	ISI_SUPPORT_ALIAS

unsigned _IsiHaveBoundAlias(unsigned Primary, unsigned AliasIndex)
{
	const LonAliasEcsConfig* pAlias;

	while (AliasIndex < AliasCount)
    {
		pAlias = IsiGetAlias(AliasIndex);
		if ((Primary == LON_GET_UNSIGNED_WORD(pAlias->Primary)) && (LON_GET_ATTRIBUTE(pAlias->Alias,LON_NV_ECS_SELHIGH) <= 0x2Fu))
        {
			// got one! get out of here:
			return AliasIndex;
		}
		++AliasIndex;
	}
	return ISI_NO_INDEX;
}

#endif	//	ISI_SUPPORT_ALIAS

//	end of HaveBdAl.c
