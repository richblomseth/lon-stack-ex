//	Assembly.c	implementing isiGetAssembly
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//  Revision 0, February 2005, Bernd Gauweiler
//

#include "isi_int.h"

unsigned FWD(IsiGetAssembly,isiGetAssembly)(const IsiCsmoData* pCsmoData, LonBool Auto, unsigned Assembly)
{
    // Combine the isiGetAssembly and isiGetNextAssembly into one by specifying ISI_NO_ASSEMBLY for the previous assembly in the first call.
    if (Assembly == ISI_NO_ASSEMBLY)
    {
	    // Default implementation returns the assembly number of a compatible NV, if the CSMO relates to a simple
	    // connection with a known NV type.
        LonByte Acknowledged = LON_GET_ATTRIBUTE(pCsmoData->Extended,ISI_CSMO_ACK);
        LonByte Poll = LON_GET_ATTRIBUTE(pCsmoData->Extended,ISI_CSMO_POLL);
        LonByte Width = LON_GET_ATTRIBUTE_P(pCsmoData,ISI_CSMO_WIDTH);
        LonByte Scope = LON_GET_ATTRIBUTE(pCsmoData->Extended,ISI_CSMO_SCOPE);

        if (!Auto						    // don't accept automatic connections be default
    	    && !Acknowledged		        // default implementation doesn't do acknowledged unicasts
	        && !Poll				        // default implementation supports, but does not accept, polled connections
	        && Width == 1u					// only accept simple connections by default
	        && !Scope				        // NV type must be in the standard (i.e. SNVT_*)
	        && !pCsmoData->Variant			// Variant must be 0
	        && pCsmoData->NvType)
        {   // NV Type must be distinct
    		// this could be acceptable. See if we have a matching NV:
            return _IsiFindLocalNvOfType(pCsmoData, 0);
	    }
        return ISI_NO_ASSEMBLY;
    }
    else
    {
        return isiGetNextAssembly(pCsmoData, Auto, Assembly);
    }
}

//	end of Assembly.c
