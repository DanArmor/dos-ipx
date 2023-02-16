#include "ipx.h"
#include <dos.h>
#include <stdio.h>


void (far *IPXDrvInvoke) (void);

int IPXInit(void){
	int status = 0;

	_AX = _IPX_CHECK_DRIVER;
	geninterrupt(_IPX_MULTIPLEX_INT);
	status = _AL;

	IPXDrvInvoke = MK_FP(_ES, _DI);
	return status;
}

int IPXOpenSocket(int socketType, int *socketNum){
	int status = 0;
	_DX = _REVERSE_BYTES(*socketNum);
	_AL = socketType;
	_BX = _IPXOpenSocket;
	IPXDrvInvoke();
	status = _AL;
	*socketNum = _DX;
	*socketNum = _REVERSE_BYTES(*socketNum);
	return status;
}

void IPXCloseSocket(int socketNum){
	_BX = _IPXCloseSocket;
	_DX = _REVERSE_BYTES(socketNum);
	IPXDrvInvoke();
}

void IPXListenForPacket(void far *ECB){
	_BX = _IPXListenForPacket;
	_ES = FP_SEG(ECB);
	_SI = FP_OFF(ECB);
	IPXDrvInvoke();
}

void IPXSendPacket(void far *ECB){
	_BX = _IPXSendPacket;
	_ES = FP_SEG(ECB);
	_SI = FP_OFF(ECB);
	IPXDrvInvoke();
}

void IPXRelinquishControl(void){
	_BX = _IPXRelinquishControl;
	IPXDrvInvoke();
}

int IPXCancelEvent(void far *ECB){
	_BX = _IPXSendPacket;
	_ES = FP_SEG(ECB);
	_SI = FP_OFF(ECB);
	IPXDrvInvoke();
	return _AL;
}
