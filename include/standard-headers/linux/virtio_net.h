#ifndef _LINUX_VIRTIO_NET_H
#define _LINUX_VIRTIO_NET_H
/* This header is BSD licensed so anyone can use the definitions to implement
 * compatible drivers/servers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of IBM nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL IBM OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE. */
#include "standard-headers/linux/types.h"
#include "standard-headers/linux/virtio_ids.h"
#include "standard-headers/linux/virtio_config.h"
#include "standard-headers/linux/virtio_types.h"
#include "standard-headers/linux/if_ether.h"

/* The feature bitmap for virtio net */
#define VIRTIO_NET_F_CSUM	0	/* Host handles pkts w/ partial csum */
#define VIRTIO_NET_F_GUEST_CSUM	1	/* Guest handles pkts w/ partial csum */
#define VIRTIO_NET_F_CTRL_GUEST_OFFLOADS 2 /* Dynamic offload configuration. */
#define VIRTIO_NET_F_MTU	3	/* Initial MTU advice */
#define VIRTIO_NET_F_MAC	5	/* Host has given MAC address. */
#define VIRTIO_NET_F_GUEST_TSO4	7	/* Guest can handle TSOv4 in. */
#define VIRTIO_NET_F_GUEST_TSO6	8	/* Guest can handle TSOv6 in. */
#define VIRTIO_NET_F_GUEST_ECN	9	/* Guest can handle TSO[6] w/ ECN in. */
#define VIRTIO_NET_F_GUEST_UFO	10	/* Guest can handle UFO in. */
#define VIRTIO_NET_F_HOST_TSO4	11	/* Host can handle TSOv4 in. */
#define VIRTIO_NET_F_HOST_TSO6	12	/* Host can handle TSOv6 in. */
#define VIRTIO_NET_F_HOST_ECN	13	/* Host can handle TSO[6] w/ ECN in. */
#define VIRTIO_NET_F_HOST_UFO	14	/* Host can handle UFO in. */
#define VIRTIO_NET_F_MRG_RXBUF	15	/* Host can merge receive buffers. */
#define VIRTIO_NET_F_STATUS	16	/* virtio_net_config.status available */
#define VIRTIO_NET_F_CTRL_VQ	17	/* Control channel available */
#define VIRTIO_NET_F_CTRL_RX	18	/* Control channel RX mode support */
#define VIRTIO_NET_F_CTRL_VLAN	19	/* Control channel VLAN filtering */
#define VIRTIO_NET_F_CTRL_RX_EXTRA 20	/* Extra RX mode control support */
#define VIRTIO_NET_F_GUEST_ANNOUNCE 21	/* Guest can announce device on the
					 * network */
#define VIRTIO_NET_F_MQ	22	/* Device supports Receive Flow
					 * Steering */
#define VIRTIO_NET_F_CTRL_MAC_ADDR 23	/* Set MAC address */
#define VIRTIO_NET_F_DEVICE_STATS 50	/* Device can provide device-level statistics. */
#define VIRTIO_NET_F_VQ_NOTF_COAL 52	/* Device supports virtqueue notification coalescing */
#define VIRTIO_NET_F_NOTF_COAL	53	/* Device supports notifications coalescing */
#define VIRTIO_NET_F_GUEST_USO4	54	/* Guest can handle USOv4 in. */
#define VIRTIO_NET_F_GUEST_USO6	55	/* Guest can handle USOv6 in. */
#define VIRTIO_NET_F_HOST_USO	56	/* Host can handle USO in. */
#define VIRTIO_NET_F_HASH_REPORT  57	/* Supports hash report */
#define VIRTIO_NET_F_GUEST_HDRLEN  59	/* Guest provides the exact hdr_len value. */
#define VIRTIO_NET_F_RSS	  60	/* Supports RSS RX steering */
#define VIRTIO_NET_F_RSC_EXT	  61	/* extended coalescing info */
#define VIRTIO_NET_F_STANDBY	  62	/* Act as standby for another device
					 * with the same MAC.
					 */
#define VIRTIO_NET_F_SPEED_DUPLEX 63	/* Device set linkspeed and duplex */

#ifndef VIRTIO_NET_NO_LEGACY
#define VIRTIO_NET_F_GSO	6	/* Host handles pkts w/ any GSO type */
#endif /* VIRTIO_NET_NO_LEGACY */

#define VIRTIO_NET_S_LINK_UP	1	/* Link is up */
#define VIRTIO_NET_S_ANNOUNCE	2	/* Announcement is needed */

/* supported/enabled hash types */
#define VIRTIO_NET_RSS_HASH_TYPE_IPv4          (1 << 0)
#define VIRTIO_NET_RSS_HASH_TYPE_TCPv4         (1 << 1)
#define VIRTIO_NET_RSS_HASH_TYPE_UDPv4         (1 << 2)
#define VIRTIO_NET_RSS_HASH_TYPE_IPv6          (1 << 3)
#define VIRTIO_NET_RSS_HASH_TYPE_TCPv6         (1 << 4)
#define VIRTIO_NET_RSS_HASH_TYPE_UDPv6         (1 << 5)
#define VIRTIO_NET_RSS_HASH_TYPE_IP_EX         (1 << 6)
#define VIRTIO_NET_RSS_HASH_TYPE_TCP_EX        (1 << 7)
#define VIRTIO_NET_RSS_HASH_TYPE_UDP_EX        (1 << 8)

struct virtio_net_config {
	/* The config defining mac address (if VIRTIO_NET_F_MAC) */
	uint8_t mac[ETH_ALEN];
	/* See VIRTIO_NET_F_STATUS and VIRTIO_NET_S_* above */
	__virtio16 status;
	/* Maximum number of each of transmit and receive queues;
	 * see VIRTIO_NET_F_MQ and VIRTIO_NET_CTRL_MQ.
	 * Legal values are between 1 and 0x8000
	 */
	__virtio16 max_virtqueue_pairs;
	/* Default maximum transmit unit advice */
	__virtio16 mtu;
	/*
	 * speed, in units of 1Mb. All values 0 to INT_MAX are legal.
	 * Any other value stands for unknown.
	 */
	uint32_t speed;
	/*
	 * 0x00 - half duplex
	 * 0x01 - full duplex
	 * Any other value stands for unknown.
	 */
	uint8_t duplex;
	/* maximum size of RSS key */
	uint8_t rss_max_key_size;
	/* maximum number of indirection table entries */
	uint16_t rss_max_indirection_table_length;
	/* bitmask of supported VIRTIO_NET_RSS_HASH_ types */
	uint32_t supported_hash_types;
} QEMU_PACKED;

/*
 * This header comes first in the scatter-gather list.  If you don't
 * specify GSO or CSUM features, you can simply ignore the header.
 *
 * This is bitwise-equivalent to the legacy struct virtio_net_hdr_mrg_rxbuf,
 * only flattened.
 */
struct virtio_net_hdr_v1 {
#define VIRTIO_NET_HDR_F_NEEDS_CSUM	1	/* Use csum_start, csum_offset */
#define VIRTIO_NET_HDR_F_DATA_VALID	2	/* Csum is valid */
#define VIRTIO_NET_HDR_F_RSC_INFO	4	/* rsc info in csum_ fields */
	uint8_t flags;
#define VIRTIO_NET_HDR_GSO_NONE		0	/* Not a GSO frame */
#define VIRTIO_NET_HDR_GSO_TCPV4	1	/* GSO frame, IPv4 TCP (TSO) */
#define VIRTIO_NET_HDR_GSO_UDP		3	/* GSO frame, IPv4 UDP (UFO) */
#define VIRTIO_NET_HDR_GSO_TCPV6	4	/* GSO frame, IPv6 TCP */
#define VIRTIO_NET_HDR_GSO_UDP_L4	5	/* GSO frame, IPv4& IPv6 UDP (USO) */
#define VIRTIO_NET_HDR_GSO_ECN		0x80	/* TCP has ECN set */
	uint8_t gso_type;
	__virtio16 hdr_len;	/* Ethernet + IP + tcp/udp hdrs */
	__virtio16 gso_size;	/* Bytes to append to hdr_len per frame */
	union {
		struct {
			__virtio16 csum_start;
			__virtio16 csum_offset;
		};
		/* Checksum calculation */
		struct {
			/* Position to start checksumming from */
			__virtio16 start;
			/* Offset after that to place checksum */
			__virtio16 offset;
		} csum;
		/* Receive Segment Coalescing */
		struct {
			/* Number of coalesced segments */
			uint16_t segments;
			/* Number of duplicated acks */
			uint16_t dup_acks;
		} rsc;
	};
	__virtio16 num_buffers;	/* Number of merged rx buffers */
};

struct virtio_net_hdr_v1_hash {
	struct virtio_net_hdr_v1 hdr;
	uint32_t hash_value;
#define VIRTIO_NET_HASH_REPORT_NONE            0
#define VIRTIO_NET_HASH_REPORT_IPv4            1
#define VIRTIO_NET_HASH_REPORT_TCPv4           2
#define VIRTIO_NET_HASH_REPORT_UDPv4           3
#define VIRTIO_NET_HASH_REPORT_IPv6            4
#define VIRTIO_NET_HASH_REPORT_TCPv6           5
#define VIRTIO_NET_HASH_REPORT_UDPv6           6
#define VIRTIO_NET_HASH_REPORT_IPv6_EX         7
#define VIRTIO_NET_HASH_REPORT_TCPv6_EX        8
#define VIRTIO_NET_HASH_REPORT_UDPv6_EX        9
	uint16_t hash_report;
	uint16_t padding;
};

#ifndef VIRTIO_NET_NO_LEGACY
/* This header comes first in the scatter-gather list.
 * For legacy virtio, if VIRTIO_F_ANY_LAYOUT is not negotiated, it must
 * be the first element of the scatter-gather list.  If you don't
 * specify GSO or CSUM features, you can simply ignore the header. */
struct virtio_net_hdr {
	/* See VIRTIO_NET_HDR_F_* */
	uint8_t flags;
	/* See VIRTIO_NET_HDR_GSO_* */
	uint8_t gso_type;
	__virtio16 hdr_len;		/* Ethernet + IP + tcp/udp hdrs */
	__virtio16 gso_size;		/* Bytes to append to hdr_len per frame */
	__virtio16 csum_start;	/* Position to start checksumming from */
	__virtio16 csum_offset;	/* Offset after that to place checksum */
};

/* This is the version of the header to use when the MRG_RXBUF
 * feature has been negotiated. */
struct virtio_net_hdr_mrg_rxbuf {
	struct virtio_net_hdr hdr;
	__virtio16 num_buffers;	/* Number of merged rx buffers */
};
#endif /* ...VIRTIO_NET_NO_LEGACY */

/*
 * Control virtqueue data structures
 *
 * The control virtqueue expects a header in the first sg entry
 * and an ack/status response in the last entry.  Data for the
 * command goes in between.
 */
struct virtio_net_ctrl_hdr {
	uint8_t class;
	uint8_t cmd;
} QEMU_PACKED;

typedef uint8_t virtio_net_ctrl_ack;

#define VIRTIO_NET_OK     0
#define VIRTIO_NET_ERR    1

/*
 * Control the RX mode, ie. promisucous, allmulti, etc...
 * All commands require an "out" sg entry containing a 1 byte
 * state value, zero = disable, non-zero = enable.  Commands
 * 0 and 1 are supported with the VIRTIO_NET_F_CTRL_RX feature.
 * Commands 2-5 are added with VIRTIO_NET_F_CTRL_RX_EXTRA.
 */
#define VIRTIO_NET_CTRL_RX    0
 #define VIRTIO_NET_CTRL_RX_PROMISC      0
 #define VIRTIO_NET_CTRL_RX_ALLMULTI     1
 #define VIRTIO_NET_CTRL_RX_ALLUNI       2
 #define VIRTIO_NET_CTRL_RX_NOMULTI      3
 #define VIRTIO_NET_CTRL_RX_NOUNI        4
 #define VIRTIO_NET_CTRL_RX_NOBCAST      5

/*
 * Control the MAC
 *
 * The MAC filter table is managed by the hypervisor, the guest should
 * assume the size is infinite.  Filtering should be considered
 * non-perfect, ie. based on hypervisor resources, the guest may
 * received packets from sources not specified in the filter list.
 *
 * In addition to the class/cmd header, the TABLE_SET command requires
 * two out scatterlists.  Each contains a 4 byte count of entries followed
 * by a concatenated byte stream of the ETH_ALEN MAC addresses.  The
 * first sg list contains unicast addresses, the second is for multicast.
 * This functionality is present if the VIRTIO_NET_F_CTRL_RX feature
 * is available.
 *
 * The ADDR_SET command requests one out scatterlist, it contains a
 * 6 bytes MAC address. This functionality is present if the
 * VIRTIO_NET_F_CTRL_MAC_ADDR feature is available.
 */
struct virtio_net_ctrl_mac {
	__virtio32 entries;
	uint8_t macs[][ETH_ALEN];
} QEMU_PACKED;

#define VIRTIO_NET_CTRL_MAC    1
 #define VIRTIO_NET_CTRL_MAC_TABLE_SET        0
 #define VIRTIO_NET_CTRL_MAC_ADDR_SET         1

/*
 * Control VLAN filtering
 *
 * The VLAN filter table is controlled via a simple ADD/DEL interface.
 * VLAN IDs not added may be filterd by the hypervisor.  Del is the
 * opposite of add.  Both commands expect an out entry containing a 2
 * byte VLAN ID.  VLAN filterting is available with the
 * VIRTIO_NET_F_CTRL_VLAN feature bit.
 */
#define VIRTIO_NET_CTRL_VLAN       2
 #define VIRTIO_NET_CTRL_VLAN_ADD             0
 #define VIRTIO_NET_CTRL_VLAN_DEL             1

/*
 * Control link announce acknowledgement
 *
 * The command VIRTIO_NET_CTRL_ANNOUNCE_ACK is used to indicate that
 * driver has recevied the notification; device would clear the
 * VIRTIO_NET_S_ANNOUNCE bit in the status field after it receives
 * this command.
 */
#define VIRTIO_NET_CTRL_ANNOUNCE       3
 #define VIRTIO_NET_CTRL_ANNOUNCE_ACK         0

/*
 * Control Receive Flow Steering
 */
#define VIRTIO_NET_CTRL_MQ   4
/*
 * The command VIRTIO_NET_CTRL_MQ_VQ_PAIRS_SET
 * enables Receive Flow Steering, specifying the number of the transmit and
 * receive queues that will be used. After the command is consumed and acked by
 * the device, the device will not steer new packets on receive virtqueues
 * other than specified nor read from transmit virtqueues other than specified.
 * Accordingly, driver should not transmit new packets  on virtqueues other than
 * specified.
 */
struct virtio_net_ctrl_mq {
	__virtio16 virtqueue_pairs;
};

 #define VIRTIO_NET_CTRL_MQ_VQ_PAIRS_SET        0
 #define VIRTIO_NET_CTRL_MQ_VQ_PAIRS_MIN        1
 #define VIRTIO_NET_CTRL_MQ_VQ_PAIRS_MAX        0x8000

/*
 * The command VIRTIO_NET_CTRL_MQ_RSS_CONFIG has the same effect as
 * VIRTIO_NET_CTRL_MQ_VQ_PAIRS_SET does and additionally configures
 * the receive steering to use a hash calculated for incoming packet
 * to decide on receive virtqueue to place the packet. The command
 * also provides parameters to calculate a hash and receive virtqueue.
 */
struct virtio_net_rss_config {
	uint32_t hash_types;
	uint16_t indirection_table_mask;
	uint16_t unclassified_queue;
	uint16_t indirection_table[1/* + indirection_table_mask */];
	uint16_t max_tx_vq;
	uint8_t hash_key_length;
	uint8_t hash_key_data[/* hash_key_length */];
};

struct virtio_net_rss_config_hdr {
	uint32_t hash_types;
	uint16_t indirection_table_mask;
	uint16_t unclassified_queue;
	uint16_t indirection_table[/* 1 + indirection_table_mask */];
};

struct virtio_net_rss_config_trailer {
	uint16_t max_tx_vq;
	uint8_t hash_key_length;
	uint8_t hash_key_data[/* hash_key_length */];
};

 #define VIRTIO_NET_CTRL_MQ_RSS_CONFIG          1

/*
 * The command VIRTIO_NET_CTRL_MQ_HASH_CONFIG requests the device
 * to include in the virtio header of the packet the value of the
 * calculated hash and the report type of hash. It also provides
 * parameters for hash calculation. The command requires feature
 * VIRTIO_NET_F_HASH_REPORT to be negotiated to extend the
 * layout of virtio header as defined in virtio_net_hdr_v1_hash.
 */
struct virtio_net_hash_config {
	uint32_t hash_types;
	/* for compatibility with virtio_net_rss_config */
	uint16_t reserved[4];
	uint8_t hash_key_length;
	uint8_t hash_key_data[/* hash_key_length */];
};

 #define VIRTIO_NET_CTRL_MQ_HASH_CONFIG         2

/*
 * Control network offloads
 *
 * Reconfigures the network offloads that Guest can handle.
 *
 * Available with the VIRTIO_NET_F_CTRL_GUEST_OFFLOADS feature bit.
 *
 * Command data format matches the feature bit mask exactly.
 *
 * See VIRTIO_NET_F_GUEST_* for the list of offloads
 * that can be enabled/disabled.
 */
#define VIRTIO_NET_CTRL_GUEST_OFFLOADS   5
#define VIRTIO_NET_CTRL_GUEST_OFFLOADS_SET        0

/*
 * Control notifications coalescing.
 *
 * Request the device to change the notifications coalescing parameters.
 *
 * Available with the VIRTIO_NET_F_NOTF_COAL feature bit.
 */
#define VIRTIO_NET_CTRL_NOTF_COAL		6
/*
 * Set the tx-usecs/tx-max-packets parameters.
 */
struct virtio_net_ctrl_coal_tx {
	/* Maximum number of packets to send before a TX notification */
	uint32_t tx_max_packets;
	/* Maximum number of usecs to delay a TX notification */
	uint32_t tx_usecs;
};

#define VIRTIO_NET_CTRL_NOTF_COAL_TX_SET		0

/*
 * Set the rx-usecs/rx-max-packets parameters.
 */
struct virtio_net_ctrl_coal_rx {
	/* Maximum number of packets to receive before a RX notification */
	uint32_t rx_max_packets;
	/* Maximum number of usecs to delay a RX notification */
	uint32_t rx_usecs;
};

#define VIRTIO_NET_CTRL_NOTF_COAL_RX_SET		1
#define VIRTIO_NET_CTRL_NOTF_COAL_VQ_SET		2
#define VIRTIO_NET_CTRL_NOTF_COAL_VQ_GET		3

struct virtio_net_ctrl_coal {
	uint32_t max_packets;
	uint32_t max_usecs;
};

struct  virtio_net_ctrl_coal_vq {
	uint16_t vqn;
	uint16_t reserved;
	struct virtio_net_ctrl_coal coal;
};

/*
 * Device Statistics
 */
#define VIRTIO_NET_CTRL_STATS         8
#define VIRTIO_NET_CTRL_STATS_QUERY   0
#define VIRTIO_NET_CTRL_STATS_GET     1

struct virtio_net_stats_capabilities {

#define VIRTIO_NET_STATS_TYPE_CVQ       (1ULL << 32)

#define VIRTIO_NET_STATS_TYPE_RX_BASIC  (1ULL << 0)
#define VIRTIO_NET_STATS_TYPE_RX_CSUM   (1ULL << 1)
#define VIRTIO_NET_STATS_TYPE_RX_GSO    (1ULL << 2)
#define VIRTIO_NET_STATS_TYPE_RX_SPEED  (1ULL << 3)

#define VIRTIO_NET_STATS_TYPE_TX_BASIC  (1ULL << 16)
#define VIRTIO_NET_STATS_TYPE_TX_CSUM   (1ULL << 17)
#define VIRTIO_NET_STATS_TYPE_TX_GSO    (1ULL << 18)
#define VIRTIO_NET_STATS_TYPE_TX_SPEED  (1ULL << 19)

	uint64_t supported_stats_types[1];
};

struct virtio_net_ctrl_queue_stats {
	struct {
		uint16_t vq_index;
		uint16_t reserved[3];
		uint64_t types_bitmap[1];
	} stats[1];
};

struct virtio_net_stats_reply_hdr {
#define VIRTIO_NET_STATS_TYPE_REPLY_CVQ       32

#define VIRTIO_NET_STATS_TYPE_REPLY_RX_BASIC  0
#define VIRTIO_NET_STATS_TYPE_REPLY_RX_CSUM   1
#define VIRTIO_NET_STATS_TYPE_REPLY_RX_GSO    2
#define VIRTIO_NET_STATS_TYPE_REPLY_RX_SPEED  3

#define VIRTIO_NET_STATS_TYPE_REPLY_TX_BASIC  16
#define VIRTIO_NET_STATS_TYPE_REPLY_TX_CSUM   17
#define VIRTIO_NET_STATS_TYPE_REPLY_TX_GSO    18
#define VIRTIO_NET_STATS_TYPE_REPLY_TX_SPEED  19
	uint8_t type;
	uint8_t reserved;
	uint16_t vq_index;
	uint16_t reserved1;
	uint16_t size;
};

struct virtio_net_stats_cvq {
	struct virtio_net_stats_reply_hdr hdr;

	uint64_t command_num;
	uint64_t ok_num;
};

struct virtio_net_stats_rx_basic {
	struct virtio_net_stats_reply_hdr hdr;

	uint64_t rx_notifications;

	uint64_t rx_packets;
	uint64_t rx_bytes;

	uint64_t rx_interrupts;

	uint64_t rx_drops;
	uint64_t rx_drop_overruns;
};

struct virtio_net_stats_tx_basic {
	struct virtio_net_stats_reply_hdr hdr;

	uint64_t tx_notifications;

	uint64_t tx_packets;
	uint64_t tx_bytes;

	uint64_t tx_interrupts;

	uint64_t tx_drops;
	uint64_t tx_drop_malformed;
};

struct virtio_net_stats_rx_csum {
	struct virtio_net_stats_reply_hdr hdr;

	uint64_t rx_csum_valid;
	uint64_t rx_needs_csum;
	uint64_t rx_csum_none;
	uint64_t rx_csum_bad;
};

struct virtio_net_stats_tx_csum {
	struct virtio_net_stats_reply_hdr hdr;

	uint64_t tx_csum_none;
	uint64_t tx_needs_csum;
};

struct virtio_net_stats_rx_gso {
	struct virtio_net_stats_reply_hdr hdr;

	uint64_t rx_gso_packets;
	uint64_t rx_gso_bytes;
	uint64_t rx_gso_packets_coalesced;
	uint64_t rx_gso_bytes_coalesced;
};

struct virtio_net_stats_tx_gso {
	struct virtio_net_stats_reply_hdr hdr;

	uint64_t tx_gso_packets;
	uint64_t tx_gso_bytes;
	uint64_t tx_gso_segments;
	uint64_t tx_gso_segments_bytes;
	uint64_t tx_gso_packets_noseg;
	uint64_t tx_gso_bytes_noseg;
};

struct virtio_net_stats_rx_speed {
	struct virtio_net_stats_reply_hdr hdr;

	/* rx_{packets,bytes}_allowance_exceeded are too long. So rename to
	 * short name.
	 */
	uint64_t rx_ratelimit_packets;
	uint64_t rx_ratelimit_bytes;
};

struct virtio_net_stats_tx_speed {
	struct virtio_net_stats_reply_hdr hdr;

	/* tx_{packets,bytes}_allowance_exceeded are too long. So rename to
	 * short name.
	 */
	uint64_t tx_ratelimit_packets;
	uint64_t tx_ratelimit_bytes;
};

#endif /* _LINUX_VIRTIO_NET_H */
