//	Node.c	implementing _IsiAllocNode
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005-2014, Bernd Gauweiler

#include "isi_int.h"

static unsigned customNodeId = 0;
static LonBool useCustomNodeId = FALSE;

//	Note that this function is only used by a single caller. A byte ot two can be saved
//	by embedding the function body in the caller directly; however, it is important that
//	this function remains a separate function.
//	When testing aspects of the ISI implementation, testers can override this function by
//	providing their own definition, which might produce a deterministic, or less varied,
//	set of results, allowing to increase probability of duplicates of node IDs, subnet
//	IDs, or selector values.

unsigned _IsiAllocNode(void)
{
	return _IsiRand(124u, 2);   //  == (random() % 124u) + 2u == 0..123 + 2 = 2..125
}

// Return the node Id to use
// Use the random value if the application does not specified one
unsigned _GetIsiNode(void)
{
    if (useCustomNodeId)
        return customNodeId;
    return _IsiAllocNode();
}

// Set the custom node Id.
// This routine must be called before the IsiStart
void _IsiSetNode(unsigned nodeId)
{
    if (nodeId == 0)
        // Invalid node Id.  Assign to use randomly allocated node Id
        useCustomNodeId = FALSE;
    else
    {
        useCustomNodeId = TRUE;
        customNodeId = nodeId;
    }
}

//	end of Node.c
