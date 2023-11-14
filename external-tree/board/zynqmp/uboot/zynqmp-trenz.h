#include <configs/xilinx_zynqmp.h>

/* ethernet - psu_ethernet_3 */
#define CONFIG_SYS_FAULT_ECHO_LINK_DOWN
#define PHY_ANEG_TIMEOUT 20000
#define CONFIG_MII
#define CONFIG_NET_MULTI
#define CONFIG_NETCONSOLE	1


#define CONFIG_GATEWAYIP	192.168.0.1
#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_SERVERIP 	192.168.0.21 

#define CONFIG_SYS_PROMPT "trenz-boot> "

#define CONFIG_EXTRA_ENV_SETTINGS 	\
	"ipaddr=192.168.0.123\0" 	\
	"qspiboot=echo Copying Linux from QSPI to RAM...;" 	\
		"sf probe 0 && sf read 0x60000000 0x800000 0x800000 && bootm 0x60000000\0" 			\
	"sdboot=echo Copying Linux from miroSD to RAM...;" 	\
		"fatload mmc 1 0x60000000 image.itb && bootm 0x60000000\0" 			\
	"tftpboot=echo Copying Linux via TFTP to RAM...;"	\
		"tftpb 0x60000000 image.itb && bootm 0x60000000\0"	\
""

#define CONFIG_BOOTCOMMAND	"run sdboot"
