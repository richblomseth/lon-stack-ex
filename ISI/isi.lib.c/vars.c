//	var.c	implementing the ISI internal variables
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//

#include "isi_int.h"
#include <stddef.h>

// eeprom 
IsiPersist _isiPersist = {
#ifdef	ISI_SUPPORT_TIMG
	ISI_DEFAULT_DEVICECOUNT,	// est. device count
#endif	//	ISI_SUPPORT_TIMG
	0,							// local nuid - this could also be in RAM, but RAM might be more expensive on Shortstack.
	1,							// serial number for CID creation
	isiReset,					// BootType
	ISI_NV_UPDATE_RETRIES		// default repeat count for implicit addressing
};

IsiVolatile _isiVolatile;

IsiMessage isi_out;

IsiType gIsiType = isiTypeS;        // default to ISI Type S
IsiFlags gIsiFlags;
unsigned char gIsiDerivableAddr = 0;  // flag to indicate that the IP address is derivabled or not


LonReadOnlyData read_only_data;
LonConfigData config_data;
LonDomain domainTable[MAX_DOMAINS];  // retrieve using LonQueryDomainConfig(const unsigned index, LonDomain* const pDomain);
LonAddress addrTable;   // [NUM_ADDR_TBL_ENTRIES];    // retrieve using LonQueryAddressConfig(const unsigned index, LonAddress* const pAddress);
// LonNvEcsConfig nvConfigTable[NV_TABLE_SIZE];
LonNvEcsConfig nv_config;
LonAliasEcsConfig alias_config;

unsigned char globalExtended = 0;


