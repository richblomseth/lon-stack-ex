//	SweepAdr.c	implementing _IsiSweepAddressTable
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.//
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

void _IsiSweepAddressTable(void)
{
	unsigned AddressIndex, UserIndex, Users;
	const LonNvEcsConfig* pNv;
	LonAddress Adr;
    unsigned int address_count =_address_table_count();

    for (AddressIndex=0; AddressIndex < address_count; ++AddressIndex)
    {
		Adr = *access_address(AddressIndex);
		if (Adr.Broadcast.Type)
        {
			// this address table space is in use. Find out if any NV or alias refers to it:
			Users = 0;
			for (UserIndex=0; UserIndex<NvCount; ++UserIndex)
            {
				pNv = IsiGetNv(UserIndex);
				if ((LON_GET_ATTRIBUTE_P(pNv,LON_NV_ECS_SELHIGH) < 0x30u) && 
                        (LON_GET_UNSIGNED_WORD(pNv->AddressIndex) == AddressIndex))
                {
					// found a user of this address table entry. We're done here.
					++Users;
					break;
				}
			}

#ifdef	ISI_SUPPORT_ALIAS
			if (!Users)
            {
				const LonAliasEcsConfig* pAlias;
				for (UserIndex=0; UserIndex<AliasCount; ++UserIndex)
                {
					pAlias = IsiGetAlias(UserIndex);
					if ((LON_GET_UNSIGNED_WORD(pAlias->Primary) != ISI_ALIAS_UNUSED) && 
                        (LON_GET_UNSIGNED_WORD(pAlias->Alias.AddressIndex) == AddressIndex))  //(pAlias->alias_nv.nv_addr_index == AddressIndex))
                    {
						// in use by this alias.
						++Users;
						break;
					}
				}
			}
#endif //	ISI_SUPPORT_ALIAS

			if (!Users)
            {
				// no users for this address table entry. Free it:
				Adr.Broadcast.Type = 0;
				update_address((const LonAddress*)&Adr, AddressIndex);
			}
		}
	}
}

//	end of SweepAdr.c
