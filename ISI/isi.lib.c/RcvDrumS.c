//	RcvDrumS.c	implementing _IsiReceiveDrumS
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

//	_IsiReceiveDrumS: receive a DRUM, detect and resolve collisions:

void _IsiReceiveDrumS(const IsiMessage* msgIn)
{
	const IsiDrum* pDrum;
	const LonDomain* pDomain;
	unsigned DomainIdLength;

	pDrum = &((const IsiMessage*)msgIn)->Msg.Drum;

    _IsiAPIDebug("_IsiReceiveDrumS ");
    _IsiAPIDump("0x", (void *)pDrum, sizeof(IsiDrum), "\n");

	if (memcmp(pDrum->NeuronId, read_only_data.UniqueNodeId, NEURON_ID_LEN))
    {
		// it's not from us. Let's see if it's for us:
		pDomain = access_domain(ISI_PRIMARY_DOMAIN_INDEX);
		DomainIdLength = pDomain->InvalidIdLength & 0x07u;

		if (LON_GET_ATTRIBUTE_P(pDrum,ISI_DRUM_DIDLENGTH) == DomainIdLength
		    && !memcmp(pDrum->DomainId, pDomain->Id, DomainIdLength) ) 
        {
			// heck - it's for us, and from someone else:
#ifdef ISI_SUPPORT_DIAGNOSTICS
			_IsiConditionalDiagnostics(isiReceiveDrum, 0);
#endif
			if (pDrum->SubnetId == pDomain->Subnet && pDrum->NodeId == LON_GET_ATTRIBUTE_P(pDomain,LON_DOMAIN_NODE) && !gIsiDerivableAddr)
            {
				// collision. Only try to resolve if the LONTalk Services subnet and node ID cannot be derived from the IP address
				if (_IsiSetDomain(ISI_PRIMARY_DOMAIN_INDEX, DomainIdLength, (const LonByte *)pDrum->DomainId, _IsiAllocSubnet(), _IsiAllocNode())) {
#ifdef ISI_SUPPORT_DIAGNOSTICS
					_IsiConditionalDiagnostics(isiSubnetNodeDuplicate, ISI_PRIMARY_DOMAIN_INDEX);
#endif
					_IsiSendDrum();
				}
			}
		}
	}
}

//	end of RcvDrumS.c
