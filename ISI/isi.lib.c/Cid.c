// Cid.c	implementing _IsiCreateCid
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler
//	Revision 1, June 2005, Bernd Gauweiler: Introducing compressed CID (saving one Neuron ID byte)
//  August 2013, Modified to use the full UID and single byte serial number for the Cid. No longer
//               using the the compressed CID.


#include "isi_int.h"

LonBool isCidInUse(IsiUniqueCid* pCid);
int getNextSerialAvail(IsiUniqueCid* pCid);

// Creates a new unique connection ID.
// Returns TRUE if successful.  
// Returns FALSE if no more slot available, all serials are in use.
LonBool _IsiCreateCid(void)
{
    LonBool success = FALSE;
    int lastSerial, saveSerial;
    IsiUniqueCid localCid;

    // A new CID is being created here.  Use the device uniqueId for the first 6 bytes (rev2).
    // No longer using the compressed CID.  The rev2 CID supports the the first 6 = 5+1 byte 
    // the UNID, and byte 7 the 1-byte serial number.
    memset(&localCid, 0, sizeof(IsiUniqueCid));
	memcpy(localCid.rev2Cid.UniqueId, read_only_data.UniqueNodeId, (unsigned)sizeof(localCid.rev2Cid.UniqueId));
    lastSerial = getNextSerialAvail(&localCid) % 255;  // range 0..254
    saveSerial = lastSerial;   
    while (TRUE)
    {
        localCid.rev2Cid.SerialNumber = lastSerial;
        if (!isCidInUse(&localCid))
        {
            // found the CID that's not currently in use.
	        memcpy(&isi_out.Msg.Csmo.Header.Cid, &localCid, sizeof(IsiCid));
            success = TRUE;
            break;
        }
        lastSerial = ++lastSerial%255;
        if (lastSerial == saveSerial)
            break;  // no more slot all serials are in use.
    }

    return success;
}

// This routine iterates the connection table and find out the highest serial number
// that's currently in-use.
int getNextSerialAvail(IsiUniqueCid* pCid)
{
    unsigned connectionTableSize = IsiGetConnectionTableSize();
    unsigned index = connectionTableSize;
    int serial;
    IsiUniqueCid localCid;

    index = 0;
    serial = -1;

    while (index < connectionTableSize)
    {
        const IsiConnection* pConnection = (IsiConnection *)IsiGetConnection(index);
        LonByte state = LON_GET_ATTRIBUTE_P(pConnection,ISI_CONN_STATE); 
        if (state > isiConnectionStateUnsed) 
        {
            memcpy(&localCid.rev2Cid, &pConnection->Header.Cid,sizeof(localCid.rev2Cid)); 
            if (!memcmp(pCid->rev2Cid.UniqueId, localCid.rev2Cid.UniqueId, sizeof(pCid->rev2Cid.UniqueId)) &&                
                (localCid.rev2Cid.SerialNumber > serial))
            {
                serial = localCid.rev2Cid.SerialNumber;
            }
        }    
        ++index;
    }
    return ++serial;    // pick the next higher one
}

// Check to find out if the connection ID (CID) is currently in used.
LonBool isCidInUse(IsiUniqueCid* pCid)
{
    unsigned connectionTableSize = IsiGetConnectionTableSize();
    unsigned index = connectionTableSize;
    LonBool inUse = FALSE;

    index = 0;
    while (index < connectionTableSize)
    {
        const IsiConnection* pConnection = (IsiConnection *)IsiGetConnection(index);
        if ((LON_GET_ATTRIBUTE_P(pConnection,ISI_CONN_STATE) > isiConnectionStateUnsed) && 
                  !memcmp(&pConnection->Header.Cid, &pCid, sizeof(IsiCid)))
        {
            // CID is already in use
            inUse = TRUE;
            break;
        }    
        ++index;
    }
    return inUse;
}

//	end of Cid.c
