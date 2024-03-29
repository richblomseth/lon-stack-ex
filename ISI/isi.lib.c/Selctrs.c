//	Selctrs.c	implementing _IsiGetSelectors
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

//	Note that this function is only used by a single caller. A byte ot two can be saved
//	by embedding the function body in the caller directly; however, it is important that
//	this function remains a separate function.
//	When testing aspects of the ISI implementation, testers can override this function by
//	providing their own definition, which might produce a deterministic, or less varied,
//	set of results, allowing to increase probability of duplicates of node IDs, subnet
//	IDs, or selector values.

LonWord _IsiGetSelectors(unsigned Width)
{
	LonByte Index;
	unsigned WidthLeft;
	LonWord CurrentSel;
	LonWord NewSel;
	const LonNvEcsConfig* pNv;
    LonByte SelHi;

	// imaginary do-while-loop
	//
	//	imaginary do-while-loop? Here's why: the following code would "normally" constist of two nested do-while loops, a boolean
	//	IsUsed variable, and a few "break" statements. Replacing the break statements with goto eliminates the need of the boolean
	//	variable, and putting the label in the right location also eliminates the formal outer do-while loop. It is still there,
	//	as a de-facto loop.
	//	Unconventional, but saves a few bytes of code.
Restart:
		WidthLeft = Width;
		NewSel = CurrentSel = make_long(rand(), rand() & 0x2Fu);

		do {
			for (Index = 0; Index < NvCount; ++Index)
            {
				pNv = IsiGetNv(Index);
				if (LON_GET_UNSIGNED_WORD(CurrentSel) == LON_GET_UNSIGNED_WORD(make_long(pNv->SelectorLow, LON_GET_ATTRIBUTE_P(pNv,LON_NV_ECS_SELHIGH))))
                {
					goto Restart;
				}
			}

#ifdef	ISI_SUPPORT_ALIAS
			for (Index = 0; Index < AliasCount; ++Index)
            {
				pNv = &IsiGetAlias(Index)->Alias;   //alias_nv;
				// Note that even we check all aliases, even unused ones as it saves a bit of code and takes about
				// the same time.  We assume that all unused alias entries have an all ones selector that will never match
				// this check.  Even if there were a match, worst case is another time through the loop.
                SelHi = LON_GET_ATTRIBUTE_P(pNv,LON_NV_ECS_SELHIGH);
				if (LON_GET_UNSIGNED_WORD(CurrentSel) == LON_GET_UNSIGNED_WORD(make_long(pNv->SelectorLow, SelHi)))
                {
					goto Restart;
				}
			}
#endif	//	ISI_SUPPORT_ALIAS

			CurrentSel = _IsiIncrementSelector(CurrentSel);
		} while	(--WidthLeft);
	// end of imaginary } while (Used); loop
	return NewSel;
}

//	end of Selctrs.c
