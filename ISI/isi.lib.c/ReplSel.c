//	ReplSel.c	implementing _IsiReplaceSelectors
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler
//

#include "isi_int.h"

//	_IsiReplaceSelectors replaces any selectors [Old..Old+Count] with [New..New+Count]
//	in alias and nv tables. The caller is in charge of updating the connection table
#if 1
#define _IsiReplaceThisSelector(New, Distance, nv) {	\
	SelectorType Replacement;							\
	Replacement.Long = LON_GET_UNSIGNED_WORD(_IsiAddSelector(New, Distance));	\
	LON_SET_ATTRIBUTE(nv,LON_NV_ECS_SELHIGH,Replacement.Byte[0]);			\
	nv.SelectorLow = Replacement.Byte[1];			\
}
#endif

#if 0
void _IsiReplaceThisSelector(LonWord New, unsigned Distance, LonNvEcsConfig nv)
{	
	SelectorType Replacement;							
	Replacement.Long = LON_GET_UNSIGNED_WORD(_IsiAddSelector(New, Distance));	
	LON_SET_ATTRIBUTE(nv,LON_NV_ECS_SELHIGH,Replacement.Byte[0]);			
	nv.SelectorLow = Replacement.Byte[1];			
}
#endif

#define Current make_long(Alias.Alias.SelectorLow, SelHi)

void _IsiReplaceSelectors(unsigned Assembly, LonWord Old, LonWord New, unsigned Count)
{
	unsigned Primary;
	LonByte SelHi;
	signed LocalCount;
#ifdef	ISI_SUPPORT_ALIAS
	unsigned Index;
#endif	//	ISI_SUPPORT_ALIAS
	LonAliasEcsConfig Alias;	 // used for processing of both NV and Alias tables

    //  16-Sept-2005 BG the function may now be called with ISI_NO_ASSEMBLY, meaning "do nothing". The issue covered here
    //  is that, as of ISI phase 3, the Host or the Member assembly may not be a valid assembly, and we take the burden from
    //  multiple caller-side checks to one check in here.
    if (Assembly != ISI_NO_ASSEMBLY)
    {
    	LocalCount = (signed)Count;
    	while (LocalCount >= 0)
        {
    		Primary = IsiGetNvIndex(Assembly, LocalCount,ISI_NO_INDEX);
    		while (Primary != ISI_NO_INDEX)
            {
    			// This NV might be affected:
    			Alias.Alias = *IsiGetNv(Primary);
                SelHi = LON_GET_ATTRIBUTE(Alias.Alias,LON_NV_ECS_SELHIGH);      // .alias_nv.nv_selector_hi
    			if (SelHi <= 0x2fu)
                {
    				// nv is bound:
    				if (_IsiInSelectorRange(Old, Count, Current))
                    {
    					// this one needs replacing. The new value is New + Current - Old, wrapped around at ISI_SELECTOR_MASK (0x2FFF)
                        unsigned Increment = LON_GET_UNSIGNED_WORD(Current) - LON_GET_UNSIGNED_WORD(Old);
    					_IsiReplaceThisSelector(New, Increment, Alias.Alias);     //.alias_nv);
    					IsiSetNv(&Alias.Alias, Primary);
    				}
    			}
#   ifdef	ISI_SUPPORT_ALIAS
    			// alias table:
    			for (Index = 0; Index < AliasCount; ++Index)
                {
    				Alias = *IsiGetAlias(Index);
    				if (LON_GET_UNSIGNED_WORD(Alias.Primary) == Primary)
                    {
    					// alias is in use with this primary
                        SelHi = LON_GET_ATTRIBUTE(Alias.Alias,LON_NV_ECS_SELHIGH);
    					if (SelHi <= 0x2fu)
                        {
    						// ... and bound
    						if (_IsiInSelectorRange(Old, Count, Current))
                            {
    							// this one needs replacing. The new value is New + Current - Old, wrapped around at ISI_SELECTOR_MASK (0x2FFF)
    							_IsiReplaceThisSelector(New, (unsigned)(LON_GET_UNSIGNED_WORD(Current)-LON_GET_UNSIGNED_WORD(Old)), Alias.Alias);     //.alias_nv);
    							IsiSetAlias(&Alias, Index);
    						}
    					}
    				}
    			}
#   endif	//	ISI_SUPPORT_ALIAS
    			Primary = IsiGetNvIndex(Assembly, LocalCount, Primary);
    		}
    		--LocalCount;
    	}	// while (LocalCount...)
    }   // if assembly...
}

//	end of ReplSel.c
