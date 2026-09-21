#pragma once
#include <Windows.h>



typedef struct _SOCKET_ADDRESS {
    LPSOCKADDR lpSockaddr;
    INT        iSockaddrLength;
} SOCKET_ADDRESS, * PSOCKET_ADDRESS, * LPSOCKET_ADDRESS;



typedef struct _IP_ADAPTER_GATEWAY_ADDRESS_LH {
    union {
        ULONGLONG Alignment;
        struct {
            ULONG Length;
            DWORD Reserved;
        };
    };
    struct _IP_ADAPTER_GATEWAY_ADDRESS_LH* Next;
    SOCKET_ADDRESS                        Address;
} IP_ADAPTER_GATEWAY_ADDRESS_LH, * PIP_ADAPTER_GATEWAY_ADDRESS_LH;


typedef struct _IP_ADAPTER_ANYCAST_ADDRESS_XP {
    union {
        ULONGLONG Alignment;
        struct {
            ULONG Length;
            DWORD Flags;
        };
    };
    struct _IP_ADAPTER_ANYCAST_ADDRESS_XP* Next;
    SOCKET_ADDRESS                        Address;
} IP_ADAPTER_ANYCAST_ADDRESS_XP, * PIP_ADAPTER_ANYCAST_ADDRESS_XP;

typedef struct _IP_ADAPTER_UNICAST_ADDRESS_LH {
    union {
        ULONGLONG Alignment;
        struct {
            ULONG Length;
            DWORD Flags;
        };
    };
    struct _IP_ADAPTER_UNICAST_ADDRESS_LH* Next;
    SOCKET_ADDRESS                        Address;
    int                      PrefixOrigin;
    int                      SuffixOrigin;
    int                          DadState;
    ULONG                                 ValidLifetime;
    ULONG                                 PreferredLifetime;
    ULONG                                 LeaseLifetime;
    UINT8                                 OnLinkPrefixLength;
} IP_ADAPTER_UNICAST_ADDRESS_LH, * PIP_ADAPTER_UNICAST_ADDRESS_LH;

typedef struct _IP_ADAPTER_MULTICAST_ADDRESS_XP {
    union {
        ULONGLONG Alignment;
        struct {
            ULONG Length;
            DWORD Flags;
        };
    };
    struct _IP_ADAPTER_MULTICAST_ADDRESS_XP* Next;
    SOCKET_ADDRESS                          Address;
} IP_ADAPTER_MULTICAST_ADDRESS_XP, * PIP_ADAPTER_MULTICAST_ADDRESS_XP;


typedef struct _IP_ADAPTER_DNS_SERVER_ADDRESS_XP {
    union {
        ULONGLONG Alignment;
        struct {
            ULONG Length;
            DWORD Reserved;
        };
    };
    struct _IP_ADAPTER_DNS_SERVER_ADDRESS_XP* Next;
    SOCKET_ADDRESS                           Address;
} IP_ADAPTER_DNS_SERVER_ADDRESS_XP, * PIP_ADAPTER_DNS_SERVER_ADDRESS_XP;


typedef struct _IP_ADAPTER_ADDRESSES_LH {
    union {
        ULONGLONG Alignment;
        struct {
            ULONG    Length;
            IF_INDEX IfIndex;
        };
    };
    struct _IP_ADAPTER_ADDRESSES_LH* Next;
    PCHAR                              AdapterName;
    PIP_ADAPTER_UNICAST_ADDRESS_LH     FirstUnicastAddress;
    PIP_ADAPTER_ANYCAST_ADDRESS_XP     FirstAnycastAddress;
    PIP_ADAPTER_MULTICAST_ADDRESS_XP  FirstMulticastAddress;
    PIP_ADAPTER_DNS_SERVER_ADDRESS_XP  FirstDnsServerAddress;
    PWCHAR                             DnsSuffix;
    PWCHAR                             Description;
    PWCHAR                             FriendlyName;
    BYTE                               PhysicalAddress[MAX_ADAPTER_ADDRESS_LENGTH];
    ULONG                              PhysicalAddressLength;
    union {
        ULONG Flags;
        struct {
            ULONG DdnsEnabled : 1;
            ULONG RegisterAdapterSuffix : 1;
            ULONG Dhcpv4Enabled : 1;
            ULONG ReceiveOnly : 1;
            ULONG NoMulticast : 1;
            ULONG Ipv6OtherStatefulConfig : 1;
            ULONG NetbiosOverTcpipEnabled : 1;
            ULONG Ipv4Enabled : 1;
            ULONG Ipv6Enabled : 1;
            ULONG Ipv6ManagedAddressConfigurationSupported : 1;
        };
    };
    ULONG                              Mtu;
    IFTYPE                             IfType;
    IF_OPER_STATUS                     OperStatus;
    IF_INDEX                           Ipv6IfIndex;
    ULONG                              ZoneIndices[16];
    PVOID              FirstPrefix;
    ULONG64                            TransmitLinkSpeed;
    ULONG64                            ReceiveLinkSpeed;
    PVOID FirstWinsServerAddress;
    PIP_ADAPTER_GATEWAY_ADDRESS_LH     FirstGatewayAddress;
    ULONG                              Ipv4Metric;
    ULONG                              Ipv6Metric;
    IF_LUID                            Luid;
    SOCKET_ADDRESS                     Dhcpv4Server;
    NET_IF_COMPARTMENT_ID              CompartmentId;
    NET_IF_NETWORK_GUID                NetworkGuid;
    NET_IF_CONNECTION_TYPE             ConnectionType;
    TUNNEL_TYPE                        TunnelType;
    SOCKET_ADDRESS                     Dhcpv6Server;
    BYTE                               Dhcpv6ClientDuid[MAX_DHCPV6_DUID_LENGTH];
    ULONG                              Dhcpv6ClientDuidLength;
    ULONG                              Dhcpv6Iaid;
    PVOID             FirstDnsSuffix;
} IP_ADAPTER_ADDRESSES_LH, * PIP_ADAPTER_ADDRESSES_LH;







