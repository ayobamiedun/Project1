/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2016 Sébastien Deronne*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Ayobami Edun <aedun@ufl.edu>
 */

#include "ns3/command-line.h"
#include "ns3/config.h"
#include "ns3/string.h"
#include "ns3/pointer.h"
#include "ns3/log.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ssid.h"
#include "ns3/mobility-helper.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/udp-client-server-helper.h"
#include "ns3/on-off-helper.h"
#include "ns3/yans-wifi-channel.h"
#include "ns3/wifi-net-device.h"
#include "ns3/qos-txop.h"
#include "ns3/wifi-mac.h"
#include "ns3/packet-sink-helper.h"
#include "ns3/packet-sink.h"

//This project is to design a Reliable hybrid multi channel wireless network,
// combining wireless local area network and wireless mesh network, for smart grid NANs

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("HybridNetwork");

int main (int argc, char *argv[])
{
    Time::SetResolution(Time::NS);

    //Create Smart meters as Nodes
    NodeContainer Meters;
    Meters.Create(2000); //Make SMartMeters a parameter

    //create Nodes for Data Aggregation Points
    NodeContainer DAPoints;
    DAPoints.Create(49); //make this a parameter

    //create Net Device containers for the smart meters and DataAggregation points
    NetDeviceContainer SmartMeters;
    NetDeviceContainer DataAggregationPoints;


    MeshHelper mesh;
    mesh.SetRemoteStationManager("ns3::IdealWIfiManager");

    // 802.11g STA
    mesh.SetStandard(WIFI_PHY_STANDARD_80211g);

    
    

    WifiMacHelper mac;
    Ssid ssid = Ssid("ns-3-ssid");

    mac.SetType("ns3::StaWifiMac",
                "Ssid", SsidValue(ssid),
                "ShortSlotTimeSupported", BooleanValue(params.enableShortSlotTime));

    // Configure the PLCP preamble type: long or short
    phy.Set("ShortPlcpPreambleSupported", BooleanValue(params.enableShortPlcpPreamble));
