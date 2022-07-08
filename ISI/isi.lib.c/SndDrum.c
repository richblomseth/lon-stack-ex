//	SndDrum.c	implementing _IsiSendDrum
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler
//	Revision 1, June 2005, Bernd Gauweiler: added support for short and extended DRUM/DRUMEX messages


#include "isi_int.h"

//	  _IsiSendDrum, guess what, sends a DRUM message. Note the function always reports the current details from the primary domain, even if writing
//	 to the primary domain has been disabled by overriding IsiSetDomain. Thus, this function never reports what ISI thinks or thought it should have,
//	 but only reports the network address that it actually has.

void _IsiSendDrum(void)
{
	unsigned Length;
	const LonDomain* pDomain;

    _IsiAPIDebug("Start _IsiSendDrum\n");
	memset(&isi_out, 0x00, (unsigned)sizeof(isi_out));

	pDomain = access_domain(ISI_PRIMARY_DOMAIN_INDEX);
	Length = LON_GET_ATTRIBUTE_P(pDomain,LON_DOMAIN_ID_LENGTH) & 0x07u;
    //isi_out.Msg.Drum.DidLength = Length;
    LON_SET_ATTRIBUTE(isi_out.Msg.Drum,ISI_DID_LENGTH,Length);
    memcpy(isi_out.Msg.Drum.DomainId, pDomain->Id, Length);

	isi_out.Msg.Drum.SubnetId = pDomain->Subnet;
	isi_out.Msg.Drum.NodeId = LON_GET_ATTRIBUTE_P(pDomain,LON_DOMAIN_NODE);
	memcpy(isi_out.Msg.Drum.NeuronId, read_only_data.UniqueNodeId, NEURON_ID_LEN);
	isi_out.Msg.Drum.Nuid = _isiPersist.Nuid;
	isi_out.Msg.Drum.ChannelType = read_only_data.ProgramId[6];
	// copy device class AND usage byte in one step:
    memcpy(&isi_out.Msg.Drum.Extended.DeviceClass, &read_only_data.ProgramId[3], 3u);
    _IsiAPIDebug("Msg: DomainID  = %x %x %x %x %x %x, Length=%d, Subnet=%d, Node=%d\n", 
                isi_out.Msg.Drum.DomainId[0],isi_out.Msg.Drum.DomainId[1],isi_out.Msg.Drum.DomainId[2],isi_out.Msg.Drum.DomainId[3],
                isi_out.Msg.Drum.DomainId[4],isi_out.Msg.Drum.DomainId[5], LON_GET_ATTRIBUTE(isi_out.Msg.Drum,ISI_DRUM_DIDLENGTH), isi_out.Msg.Drum.SubnetId, 
                isi_out.Msg.Drum.NodeId);
 
    _IsiAPIDebug("Msg: NeuronID=%x %x %x %x %x %x Nuid=%d ChannelType=%d ExDeviceClass = %d %d\n", 
                isi_out.Msg.Drum.NeuronId[0],isi_out.Msg.Drum.NeuronId[1],isi_out.Msg.Drum.NeuronId[2],
                isi_out.Msg.Drum.NeuronId[3],isi_out.Msg.Drum.NeuronId[4],isi_out.Msg.Drum.NeuronId[5],
                isi_out.Msg.Drum.Nuid, isi_out.Msg.Drum.ChannelType,
                LON_GET_UNSIGNED_WORD(isi_out.Msg.Drum.Extended.DeviceClass), isi_out.Msg.Drum.Extended.Usage);


 	_IsiBroadcast(isiDrum, ISI_SECONDARY_DOMAIN_INDEX, 1);
    _IsiAPIDebug("End _IsiSendDrum\n");
}

void IsiSendDrum(void)
{
    _IsiSendDrum();
}

//	end of SndDrum.c
