//	IsConn.c	implementing IsiIsConnected and IsiIsAutomaticallyEnrolled
//
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"
#include <stddef.h>

/*
 * Function: IsiIsConnected
 * Returns the status of the specified assembly whether is currently enrolled in a connection or not. 
 *
 * Parameters:
 * assembly - assembly for which the connection status needs to be queried.
 *
 * Returns:
 * True - if the specified assembly is enrolled in a connection.
 * False - if the ISI engine is stopped.
 *
 * Remarks:
 * The function operates whether the ISI engine is running or not. 
 */
LonBool IsiIsConnected(unsigned Assembly)
{
	unsigned Index;
	IsiConnection ConnectionData;

	for(Index=0; _IsiNextConnection(Index, &ConnectionData); ++Index)
    {
        if (LON_GET_ATTRIBUTE(ConnectionData,ISI_CONN_STATE) >= isiConnectionStateInUse &&
            (ConnectionData.Host == Assembly || ConnectionData.Member == Assembly))
        {
            return TRUE;
        }
	}
	return FALSE;
}

/*
 * Function: IsiIsAutomaticallyEnrolled
 * Returns the status of the specified assembly whether is currently connected and if that
 * connection was made with automatic enrollment.
 *
 * Parameters:
 * assembly - assembly for which the connection status needs to be queried.
 *
 * Returns:
 * True - if the specified assembly is enrolled in a connection and the connection was made with 
 *        automatic enrollment.
 * False - if the ISI engine is stopped or if the connection was not made with automatic enrollment.
 *
 * Remarks:
 * The function operates whether the ISI engine is running or not. 
 */
LonBool IsiIsAutomaticallyEnrolled(unsigned Assembly)
{
	unsigned Index;
	IsiConnection ConnectionData;

	for(Index=0; _IsiNextConnection(Index, &ConnectionData); ++Index)
    {
        // Finds out if the assembly is enrolled in a connection and the connection was made
        // with automatic enrollment. We'd be looking for a connection table record with offset
		// zero though; higher order records are irrelevant (and can't appear in automatic
		// connections - see rcvcsmo.c for details about that).
        if (LON_GET_ATTRIBUTE(ConnectionData,ISI_CONN_STATE) >= isiConnectionStateInUse &&
            (ConnectionData.Host == Assembly || ConnectionData.Member == Assembly) &&
            ConnectionData.Desc.OffsetAuto == ConnectionAuto_MASK)
        {
        	return TRUE;
        }
	}
	return FALSE;
}    

//	end of IsConn.c
