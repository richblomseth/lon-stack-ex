//	Csmi.c	implementing _IsiCreateCsmi
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//  Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

void _IsiCreateCsmi(const IsiConnection* pConnection, IsiCsmi* pCsmi)
{
    LonByte Offset = LON_GET_ATTRIBUTE(pConnection->Desc.Bf,ConnectionOffset);
    LonByte Width = LON_GET_ATTRIBUTE_P(pConnection,ISI_CONN_WIDTH);
	memcpy(&pCsmi->Header, &pConnection->Header, (unsigned)sizeof(pConnection->Header));
	//pCsmi->Desc.OffsetCount = (pConnection->Desc.Bf.Offset<<CsmiOffsetShift) | ((pConnection->Width - 1u)<<CsmiCountShift);
    pCsmi->Desc.OffsetCount = (Offset<<CsmiOffset_SHIFT) | ((Width - 1u)<<CsmiCount_SHIFT);
}

//	end of Csmi.c
