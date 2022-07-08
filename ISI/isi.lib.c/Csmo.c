//	Csmo.c	implementing isiCreateCsmo
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	    Revision 0, February 2005, Bernd Gauweiler
//	    Revision 1, June 2005, Bernd Gauweiler: Adding support for Extended fields

#include "isi_int.h"

// on the caller side and after calling isiCreateCsmo, the following code MUST be added before sending a CSMO or CSMR:
// _IsiCreateCid(&pCsmo->Header.Cid);
// pCsmo->Header.Selector = _IsiGetSelectors(pCsmo->Data.Width)
//	See Host.c
extern unsigned get_nv_si_count(void);

void FWD(IsiCreateCsmo,isiCreateCsmo)(unsigned Assembly, IsiCsmoData* const pCsmoData)
{
	unsigned int NvIdx;

	memset(pCsmoData, 0, sizeof(IsiCsmoData));
	pCsmoData->Group = IsiGetPrimaryGroup(Assembly);
	memcpy(pCsmoData->Extended.Application, read_only_data.ProgramId, ID_STR_LEN-2u);
	LON_SET_ATTRIBUTE_P(pCsmoData,ISI_CSMO_DIR,(LonByte)isiDirectionAny);

	NvIdx = IsiGetNvIndex(Assembly, 0, ISI_NO_INDEX);
	if ((NvIdx < NvCount) && (NvCount == get_nv_si_count()))
    {
		pCsmoData->NvType = (unsigned)get_nv_type(NvIdx);
	}
	LON_SET_ATTRIBUTE_P(pCsmoData,ISI_CSMO_WIDTH,IsiGetWidth(Assembly));
}

//	end of Csmo.c

