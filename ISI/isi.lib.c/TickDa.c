//	TickDas.c	implementing IsiTickDa
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

#ifdef	ISI_SUPPORT_DADAS

void IsiTickDa(void) {
    // Firstly, do whatever a normal ISI(-S) device is supposed to do with every tick.
    // Notice IsiTickS() also decrements _isiVolatile.Timeout and ShortTimer, regardless
    // of the current state.
    IsiTickS();

    if (_isiVolatile.Running) {
        if (_isiVolatile.Timeout == 1u) {
            // The Timout Timer has expired. Let's see if there is something for us to do:
            if (_isiVolatile.State & (isiStateAwaitDidrx | isiStateAwaitConfirm)) {
                //  isiStateAwaitDidrx: we have b'cast a DIDRQ and are now awaiting at least one DIDRM.
                //
                // isiStateAwaitConfirm: ISI_T_CF has expired prior to the arrival of a DIDCF message.
                // Basically, the user failed to confirm that the correct device executed a wink, or it
                // wasn't the correct device in the first place, or we simply couldn't hear the DIDCF.
                if(_isiVolatile.Group) {
                    // We have yet another retry (out of ISI_DIDRQ_RETRIES), so wait 5*Trm
                    // before firing another DIDRM:
                    _isiVolatile.State = isiStatePause;
                    _isiVolatile.Timeout = ISI_DIDRQ_PAUSE;
                } else {
                    // we have used up all 20 retries. Give up:
                    _IsiUpdateUiAndStateTimeout(0, isiStateNormal, isiAborted, isiAbortUnsuccessful);
                }

            } else if (_isiVolatile.State == isiStatePause) {
                // ISI_DIDRQ_PAUSE has expired. Signal begin of retry, fire another DIDRM,
                // decrement the rety counter (== reused Group field), and return to isiStateAwaitDidrx
                --_isiVolatile.Group;
                _IsiAcquireDomain();
                _IsiUpdateUiAndStateTimeout(ISI_T_RM, isiStateAwaitDidrx, isiRetry, _isiVolatile.Group);

            } else if (_isiVolatile.State == isiStateCollect) {
                // ISI_T_COLL has expired. Since we are still in this state by the time ISI_T_COLL has
                // expired, we know we have received one, or only matching, DIDRM messages in response
                // to our DIDRQ.
                // Now, we must get the application to perform a Wink command, set the ShortTimer to ISI_T_CF,
                // proceed to isiStateAwaitConfirm and await the arrival of a matching DIDCF:
                _IsiUpdateUiAndStateTimeout(ISI_T_CF, isiStateAwaitConfirm, isiWink, 0);

            }
        }
#ifdef  ISI_SUPPORT_AUTOMATIC_CONNECTIONS
        _IsiTcsmr();
#endif
	}
}
#endif	//	ISI_SUPPORT_DADAS

//	end of TickS.c
