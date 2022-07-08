//	updateUI.c	implementing default IsiUpdateUserInterface
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, January 2005, Bernd Gauweiler

#include "isi_int.h"

void isiUpdateUserInterface(IsiEvent Event, LonByte Parameter)
{
    // the default IsiUpdateUserInterface does nothing
};

void _IsiUpdateUiAndState(IsiState State, IsiEvent Event, int Parameter)
{
    _isiVolatile.State = State;
    IsiUpdateUserInterface(Event, Parameter);
};

void _IsiUpdateUiAndStateEnroll(IsiState State, IsiEvent Event, int Parameter)
{
    _isiVolatile.Timeout = ISI_T_ENROLL;
    _isiVolatile.State = State;
    IsiUpdateUserInterface(Event, Parameter);
};

void _IsiUpdateUi(IsiEvent Event)
{
    IsiUpdateUserInterface(Event, ISI_NO_ASSEMBLY);
};

void _IsiUpdateUiNormal(void)
{
    IsiUpdateUserInterface(isiNormal, ISI_NO_ASSEMBLY);
};

void _IsiUpdateUiAndStateTimeout(unsigned long Timeout, IsiState State, IsiEvent Event, int Parameter)
{
    _isiVolatile.Timeout = Timeout;
    _IsiUpdateUiAndState(State, Event, Parameter);
};
