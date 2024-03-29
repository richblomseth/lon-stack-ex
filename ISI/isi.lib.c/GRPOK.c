//	GrpOk.c	implementing _IsiIsGroupAcceptable
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

//	_IsiIsGroupAcceptable retunrns ISI_NOT_ACCEPTABLE if the given Group cannot be accepted,
//	or returns a suitable address table index otherwise. A Group is acceptable if the device is already member
// 	of that group, or if a free address table entry is available
//	Set the Join parameter to TRUE if you want the function to have the side effect of also updating the address
//	table entry accordingly.

unsigned _IsiIsGroupAcceptable(unsigned Group, LonBool Join)
{
	signed Index;
	signed FirstEmpty;
	address_struct_alt adr;

	FirstEmpty = -1;

	// Scan table from back to front so that we find either a matching group entry or the
	// first empty entry.
    Index = (signed)_address_table_count();     // getting the value from the stack, instead of from the read_only_data
    while (--Index >= 0)
    {
		// OK, this is a bit sleazy, but we use the non-group structure to look
		// for a group match and just take advantage of our knowledge that the
		// group type always has the MSB set.
		adr = *(const address_struct_alt*)access_address(Index);
		if ((adr.typeSize & ADDR_GROUP_MASK) && adr.group == Group)
        {
			// we are already member of this group:
			return Index;
		}
        else if (adr.typeSize == 0)
        {
			FirstEmpty = Index;
		}
	}

	// Now, we have iterated through the entire address table and found we are not a member of this group. Let's see if
	// we could become a member (an address table entry free?)
    if (FirstEmpty != -1)
    {
        // found an unused address table entry.
        if (Join)
        {
            adr.member = 0;				// Sets domain and member to 0
            adr.typeSize = ADDR_GROUP_MASK;	// Set type MSB (group) and size of 0
            adr.group = Group;				// Sets group number
            // Fixed the problem where the RepeatTimer should be the upper 4 bits
			adr.timer1 = _isiVolatile.Transport.RepeatTimer | _isiPersist.RepeatCount;
			adr.timer2 = (_isiVolatile.Transport.GroupRcvTimer<<LON_ADDRESS_GROUP_RECEIVE_TIMER_SHIFT) | _isiVolatile.Transport.TransmitTimer;
			update_address((LonAddress*)&adr, FirstEmpty);
        }
    }
    // ASSUMES: ISI_NOT_ACCEPTABLE == -1
    return FirstEmpty;
}

//	end of GrpOk.c
