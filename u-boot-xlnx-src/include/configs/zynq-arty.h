#include <configs/zynq-common.h>


#define CONFIG_SERVERIP 	192.168.0.21
#define CONFIG_GATEWAYIP	192.168.0.1
#define CONFIG_NETMASK		255.255.255.0


#define CONFIG_SYS_PROMPT "zynq-arty-boot> "


#define CONFIG_EXTRA_ENV_SETTINGS 	\
	"ipaddr=192.168.0.123\0" 	\
	"sdboot=echo Copying Linux from QSPI to RAM...;" 	\
		"sf probe 0 && sf read 0x4000000 0x800000 0x800000 && bootm 0x4000000\0" 			\
	"tftpboot=tftpb 0x4000000 image-arty.itb && bootm 4000000\0"	\
""

#define CONFIG_BOOTCOMMAND	"run sdboot"
