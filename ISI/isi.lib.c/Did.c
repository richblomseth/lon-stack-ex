//	did.c	implementing IsiGetPrimaryDid
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//  Revision 0, January 2005, Bernd Gauweiler

#include "isi_int.h"
#include <stdio.h>

static LonByte DomainID[LON_DOMAIN_ID_MAX_LENGTH] = ISI_DEFAULT_DOMAIN_ID;
static unsigned DIDLen = ISI_DEFAULT_DOMAIN_ID_LEN;

const LonByte* IsiGetPrimaryDid(LonByte* pLength)
{
    *pLength = DIDLen;
    return DomainID;
}

void IsiSetPrimaryDid(const LonByte* pDid, unsigned len)
{
    if (len <= LON_DOMAIN_ID_MAX_LENGTH)
    {
        memset(DomainID, 0, sizeof(DomainID));
        DIDLen = len;
        memcpy(DomainID, pDid, len);
    }
}

// Set the Primary Did based on the local IP address
// The first two bytes of the IP addess represnt the LONTalk services domain ID
// the third byte represents the LONTalk services subnet and the fourth byte 
// represents the LONTalk services node ID
// If the address is not derivabled, ISI will assign a randomly allocated
// subnet and node ID, and set the flag to indicate that that the address is not derivabled
LonBool _IsiEnableAddrMgmt(void)
{
#if defined(IZOT_PLATFORM)
    LonByte localDomainID[LON_DOMAIN_ID_MAX_LENGTH];
    unsigned int localDidLen;
    unsigned int subnetId, nodeId;
#endif

    _IsiSetSubnet(0);
    _IsiSetNode(0);
    gIsiDerivableAddr = 0;

#if defined(IZOT_PLATFORM)
    // Gets the domain, subnet and node Id from the local IP address
    if (LonGetDidFromLocalAddress(localDomainID, &localDidLen, &subnetId, &nodeId) == (LonApiError)IsiApiNoError)
    {
        char s[256];
        int i;
        char *p = s;

        IsiSetPrimaryDid(localDomainID, localDidLen);

        // Check to make sure if the address is derivabled 
        if ((subnetId >= 1 && subnetId <= 255) && 
            (nodeId >= 1 && nodeId <= 127))
        {
            _IsiSetSubnet(subnetId);
            _IsiSetNode(nodeId);
            gIsiDerivableAddr = 1;
        }
        memset(&s, 0, sizeof(s));
        for (i=0; i< (int)localDidLen; ++i)
        {
            sprintf(p, "%2x ", localDomainID[i]);
            p += 3;
        }
        _IsiAPIDebug("IP Address is %s DidLength=%d Did=%s\n",
            gIsiDerivableAddr ? "derivabled" : "not derivabled", localDidLen, s);
        if (gIsiDerivableAddr)
            _IsiAPIDebug("Subnet=%d Node=%d\n", subnetId, nodeId); 
        return TRUE;
    }
#endif
    return FALSE;
}

// Get the DomainId and length from the IP address
// The first two bytes of the IP addess represnt the LONTalk services domain ID
LonBool _GetDomainIdFromAddr(LonByte* pDom, unsigned int* didLen)
{
#if defined(IZOT_PLATFORM)
    unsigned int subnetId, nodeId;

    if (LonGetDidFromLocalAddress(pDom, didLen, &subnetId, &nodeId) == (LonApiError)IsiApiNoError)
        return TRUE;
#endif
    return FALSE;
}
