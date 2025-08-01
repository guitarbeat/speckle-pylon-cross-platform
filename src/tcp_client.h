/**************************************************************************************************************************************************
*                                 Copyright © 2012 Texas Instruments Incorporated - http://www.ti.com/                                            *
***************************************************************************************************************************************************
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: *
*                                                                                                                                                 *
*    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.                 *
*                                                                                                                                                 *
*    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the        *
*    documentation and/or other materials provided with the distribution.                                                                         *
*                                                                                                                                                 *
*    Neither the name of Texas Instruments Incorporated nor the names of its contributors may be used to endorse or promote products derived      *
*    from this software without specific prior written permission.                                                                                *
*                                                                                                                                                 *
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          *
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT     *
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT         *
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    *
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE      *
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                                                           *
***************************************************************************************************************************************************/
/**
*
* @file    tcp_client.h
*
* @brief	This file contains functions related to TCP communication. 
*			Based on the platform and development environment, functions can be implemented.
**/
/**************************************************************************************************************************************************/

/*Include header files related to TCP/IP communication */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "common.h"

#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TRUE                    1
#define FALSE                   0


    SOCKET TCP_Connect(char *host, unsigned long int  port);
    int TCP_Send(SOCKET ConnectSocket, uint8 *buffer, int length);
    int TCP_Receive(SOCKET ConnectSocket, uint8 *buffer, int length);
    int TCP_Disconnect(SOCKET ConnectSocket);

#ifdef __cplusplus
}
#endif


#endif /* TCP_CLIENT_H_ */

