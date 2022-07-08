//	Subnet.c	implementing _IsiAllocSubnet
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
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

static unsigned customSubnetId = 0;
static LonBool useCustomSubnetId = FALSE;

// Sets the subnet Id. By default the ISI engine will use the random subnet Id.  
void _IsiSetSubnet(unsigned subnetId)
{
    if (subnetId == 0)
        // Invalid subnet.  Assign to use randomly allocated subnet
        useCustomSubnetId = FALSE;
    else
    {
        useCustomSubnetId = TRUE;
        customSubnetId = subnetId;
    }
}

unsigned _IsiAllocSubnet(void)
{
    return _IsiRand(ISI_SUBNET_BUCKET_SIZE, _isiVolatile.Transport.BaseSubnet);
}

// Returns the subnet to use
// Use the random value if the application does not specified one
unsigned _GetIsiSubnet(void)
{
    if (useCustomSubnetId)
        return customSubnetId;
    return _IsiAllocSubnet();
}

//	end of Subnet.c
