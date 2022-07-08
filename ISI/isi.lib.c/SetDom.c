//	SetDom.ns implementing _IsiSetDomain
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler
//

#include "isi_int.h"

/***************************************************************************
 *  Function: _IsiSetDomain
 *
 *  Parameters: unsigned Idx, unsigned char Len, const unsigned char* pId
 *              unsigned Subnet, unsigned Node
 *
 *  Operation: ISI Set Domain
 *  Side Effect: When setting the primary domain, the tool also changes the
 *  			node to the configured, online state.
 ***************************************************************************/
LonBool _IsiSetDomain(unsigned Idx, unsigned Len, const LonByte* pId, unsigned Subnet, unsigned Node)
{
	LonDomain Domain;
	LonBool bol;

	memcpy(&Domain, access_domain(Idx), sizeof(Domain));

    LON_SET_ATTRIBUTE(Domain,LON_DOMAIN_ID_LENGTH, Len);
    LON_SET_ATTRIBUTE(Domain,LON_DOMAIN_INVALID, 0);    // set the domain to be valid.  Otherwise, the LTS will reset the length to 7
	Domain.Subnet = Subnet;
	LON_SET_ATTRIBUTE(Domain,LON_DOMAIN_NODE,Node);
	memcpy(Domain.Id, pId, Len);

	bol = FALSE;
    // check if the current domain is the same with the new one
	if (memcmp(&Domain, access_domain(Idx), sizeof(Domain)))
    {
        // Not the same, update the domain table
		if (Idx == ISI_SECONDARY_DOMAIN_INDEX)
        {
            // The second domain must use a clone domain configuration. 
 			update_domain_address(&Domain, ISI_SECONDARY_DOMAIN_INDEX, 0, FALSE);
		}
        else
        {
			IsiSetDomain(&Domain, ISI_PRIMARY_DOMAIN_INDEX);
			set_node_mode(LonChangeState, 4);	// go configured
			set_node_mode(LonApplicationOnLine, 0);	// go online
		}
		bol = TRUE;
	}

	return bol;
};

