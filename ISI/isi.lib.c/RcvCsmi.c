//	RcvCsmi.c	implementing _IsiReceivePtrCsmi
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"


void _IsiReceivePtrCsmi(const IsiCsmi* pCsmi)
{
	unsigned Connection, Index, SelectorCorrection, lastPending;
	LonWord Replacement;
	IsiConnection ConnectionData;
	IsiCsmi	turnaroundCsmi;

    _IsiAPIDebug("_IsiReceiveCsmi ");
    _IsiAPIDump("0x", (void *)pCsmi, sizeof(IsiCsmi), "\n");

    for (Connection = 0; _IsiNextConnection(Connection, &ConnectionData); ++Connection)
    {
		if (LON_GET_ATTRIBUTE(ConnectionData,ISI_CONN_STATE) >= isiConnectionStateInUse)
        {
			if (memcmp(&ConnectionData.Header.Cid, &pCsmi->Header.Cid, (unsigned)sizeof(IsiCid))
			    || (LON_GET_ATTRIBUTE(ConnectionData.Desc.Bf, ConnectionOffset) != LON_GET_ATTRIBUTE(pCsmi->Desc.Bf,CsmiOffset)))
            {
                // CID mismatch or offset mismatch:
				// Is this connection using the selector that is reported by the CSMI? If so,
				// resolve the conflict by reallocating a new selector, updating the connection
				// table, and updating all uses of the old selector(s) in NV and alias tables.
				// Finally, if the connection is hosted locally, issue a new CSMI if this is the
				// host of the updated connection.
				for (Index=0; Index <= (unsigned)LON_GET_ATTRIBUTE(pCsmi->Desc.Bf,CsmiCount); ++Index)
                {
					if (_IsiInSelectorRange(ConnectionData.Header.Selector, LON_GET_ATTRIBUTE(ConnectionData,ISI_CONN_WIDTH)-1u, _IsiAddSelector(((IsiCsmi *)pCsmi)->Header.Selector,Index)))
                    {
						// now we must move this connection to a new selector:

						//	1.	find new selector(s) for those currently used by Conflict, using the fixed replacement
						//		selector algorithm:
						LON_SET_UNSIGNED_WORD(Replacement, LON_GET_UNSIGNED_WORD(ConnectionData.Header.Selector) + LON_GET_ATTRIBUTE(ConnectionData,ISI_CONN_WIDTH));    //.Width;
						for (SelectorCorrection = 0; SelectorCorrection < (unsigned)sizeof(IsiCid); ++SelectorCorrection)
                        {
							Replacement = _IsiAddSelector(Replacement, ((const unsigned*)&ConnectionData.Header.Cid)[SelectorCorrection]);
						}

						//	2.	call _IsiReplaceSelectors to execute the selector replacement on local nv and alias tables
                        _IsiReplaceSelectors(ConnectionData.Host, ConnectionData.Header.Selector, Replacement, LON_GET_ATTRIBUTE(ConnectionData,ISI_CONN_WIDTH)-1u);
                        _IsiReplaceSelectors(ConnectionData.Member, ConnectionData.Header.Selector, Replacement, LON_GET_ATTRIBUTE(ConnectionData,ISI_CONN_WIDTH)-1u);

						//	3.	update the connection table, but temporarily mark this connection table entry as PENDING.
						//		this is required for step 5.
						ConnectionData.Header.Selector = Replacement;
						LON_SET_ATTRIBUTE(ConnectionData,ISI_CONN_STATE,isiConnectionStatePending);
						IsiSetConnection(&ConnectionData, Connection);
                        //      Since we temporarily create a faked pending enrollment, we must preserve and fake the pending connection
                        //      index, too - this CSMI might be received in the middle of an actual enrollment process.
                        lastPending = _isiVolatile.pendingConnection;
                        _isiVolatile.pendingConnection = Connection;

						//	4.	if the connection is hosted locally, issue a CSMI
						if (ConnectionData.Host != ISI_NO_ASSEMBLY) {
							_IsiSendCsmi(&ConnectionData);
						}

						//	5.	pretend we received an incoming CSMI using the new connection data. Because step 3 marked this
						//		connection as unused, processing of this faked CSMI doesn't detect the Collision with "self"
						_IsiCreateCsmi(&ConnectionData, &turnaroundCsmi);
						_IsiReceivePtrCsmi(&turnaroundCsmi);
                        //      restore the previous pending connection index:
                        _isiVolatile.pendingConnection = lastPending;

						//	6.	update the connection table once more, to get the state back into "InUse":
                        LON_SET_ATTRIBUTE(ConnectionData,ISI_CONN_STATE,isiConnectionStateInUse);
#ifdef ISI_SUPPORT_DIAGNOSTICS
                        if (ConnectionData.Host != ISI_NO_ASSEMBLY) {
                            _IsiConditionalDiagnostics(isiSelectorDuplicate, ConnectionData.Host);
                        }
                        if (ConnectionData.Member != ISI_NO_ASSEMBLY) {
                            _IsiConditionalDiagnostics(isiSelectorDuplicate, ConnectionData.Member);
                        }
#endif
						goto UpdateConnectionTable;	// Saves a few bytes
					}	// if inselectorrange
				}	// for {count}
			} 
            else if (LON_GET_UNSIGNED_WORD(ConnectionData.Header.Selector) != LON_GET_UNSIGNED_WORD(pCsmi->Header.Selector))
            {
				// CID and offset both match. Does the connection table's selector match the one in the CSMI?
				// If not, follow suit by updating the local selector(s) with the new one(s) from the CSMI.
				// Ignore the CSMI otherwise:
                _IsiReplaceSelectors(ConnectionData.Host, /* old */ConnectionData.Header.Selector, /* new */ pCsmi->Header.Selector, /* 0-based sel-count */ LON_GET_ATTRIBUTE(((IsiCsmi *)pCsmi)->Desc.Bf,CsmiCount));
                _IsiReplaceSelectors(ConnectionData.Member, /* old */ConnectionData.Header.Selector, /* new */ pCsmi->Header.Selector, /* 0-based sel-count */ LON_GET_ATTRIBUTE(((IsiCsmi *)pCsmi)->Desc.Bf,CsmiCount));
				ConnectionData.Header.Selector = pCsmi->Header.Selector;
#ifdef ISI_SUPPORT_DIAGNOSTICS
                if (ConnectionData.Host != ISI_NO_ASSEMBLY) {
                    _IsiConditionalDiagnostics(isiSelectorUpdate, ConnectionData.Host);
                }
                if (ConnectionData.Member != ISI_NO_ASSEMBLY) {
                    _IsiConditionalDiagnostics(isiSelectorUpdate, ConnectionData.Member);
                }
#endif
UpdateConnectionTable:
				IsiSetConnection(&ConnectionData, Connection);
			} // any collission?
		}	// conntab entry in use?
	}	// for each connection
    savePersistentData(IsiNvdSegConnectionTable);
}

//	end of RcvCsmi.c
