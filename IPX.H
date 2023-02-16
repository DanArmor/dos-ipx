#ifndef _INC_IPX_H
#define _INC_IPX_H
/*Коды функций*/
#define _IPXOpenSocket 0x00
#define _IPXCloseSocket 0x01
#define _IPXListenForPacket 0x04
#define _IPXSendPacket 0x03
#define _IPXRelinquishControl 0x0A
#define _IPXCancelEvent 0x06
/*Инициализация сокета*/
#define _IPX_CHECK_DRIVER 0x7A00
#define _IPX_DRV_OK 0xFF
#define _IPX_MULTIPLEX_INT 0x2F
/*Открытие сокета*/
#define _IPX_SHORT_LIVED 0x0
#define _IPX_LONG_LIVED 0xFF
#define _IPXOpenSocket_OPEN 0x0
#define _IPXOpenSocket_BUSY 0xFF
#define _IPXOpenSocket_OVERFLOW 0xFE
/*Флаг InUse*/
#define _ECB_SND 0xFF
#define _ECB_REC 0xFE
#define _ECB_AES 0xFD
#define _ECB_QUE 0xFB
/*Прием*/
#define _ECB_CCODE_OK 0x0
#define _ECB_CCODE_NOSOCKET 0xFF
#define _ECB_CCODE_POVERFLOW 0xFD
/*Передача*/
#define _ECB_CCODE_CNC 0xFC
#define _ECB_CCODE_PHYS 0xFF
#define _ECB_CCODE_NOSTATION 0xFE
#define _ECB_CCODE_BADPACKET 0xFD
/*Отмена события*/
#define _IPXCancelEvent_OK 0x0
#define _IPXCancelEvent_FAILED 0xF9
#define _IPXCancelEvent_NOTBUSY 0xFF
/*Другие константы и макросы*/
#define _IPX_SAME_NETWORK 0x0
#define _IPX_BROADCAST 0xFF
#define _IPX_PCT_TYPE 0x4
#define _REVERSE_BYTES(x) (((x) & 0x00FF) << 8 | ((x) & 0xFF00) >> 8)

/*Точка входа*/
extern void (far *IPXDrvInvoke) (void);

typedef struct IPXHeader {
	unsigned int checksum;
	unsigned int length;
	unsigned char transportControl;
	unsigned char packetType;
	unsigned char destNetwork[4];
	unsigned char destNode[6];
	unsigned int destSocket;
	unsigned char sourceNetwork[4];
	unsigned char sourceNode[6];
	unsigned int sourceSocket;
} IPXHeader;

int IPXInit(void);

int IPXOpenSocket(int socketType, int *socketNum);
void IPXCloseSocket(int socketNum);
void IPXListenForPacket(void far *ECB);
void IPXSendPacket(void far *ECB);
void IPXRelinquishControl(void);
int IPXCancelEvent(void far *ECB);

typedef struct ECBfrag{
	void far *addr;
	unsigned int size;
} ECBfrag;

typedef struct ECB {
	void far *link;
	void (far *ESRAddress) (void);
	unsigned char inUse;
	unsigned char ccode;
	unsigned int socket;
	void far *IPXWorkspace;
	unsigned char driverWorkspace[12];
	unsigned char immAddress[6];
	unsigned int fragmentCnt;
	ECBfrag descs[4];
} ECB;

#endif
