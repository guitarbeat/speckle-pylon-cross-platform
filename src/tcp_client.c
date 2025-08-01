//modified by Tommy on 09/13/2012
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
* @file    tcp_client.c
*
* @brief	TCP implementation using <system supported function > APIs.
**/
/**************************************************************************************************************************************************/
#include "common.h"

/*Include header files related to TCP/IP communication */
#include "tcp_client.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512

/************************************************************************************
 *                           TCP_Connect
 * INPUT: 
 *	- host : address of the host (e.g. "192.168.1.100")
 *	- port : port number to connect (e.g. "21845" or 0x5555)
 * OUTPUT:
 *  - ConnectSocket
 ************************************************************************************/
SOCKET TCP_Connect(char *host, unsigned long int port)
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
	int iResult;
	char portNum[10];

    //1. Declare and Initialize TCP/IP module
	// Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_INET;       //IPv4 only originally AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM; //TCP only, no UDP
    hints.ai_protocol = IPPROTO_TCP;

    //2. Create a socket for connecting to server

	//convert port to String since getaddrinfo expect char* for 2nd param
	sprintf(portNum, "%d", port);
	
	// Resolve the server address and port
	iResult = getaddrinfo(host, portNum, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

	// Attempt to connect to an address until one succeeds
    ptr = result;
    // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

    //3. Connect to server.
	iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            //continue;
        }
	
	freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    return ConnectSocket;
}

/************************************************************************************
 *                           TCP_Send
 * INPUT: 
 *	- ConnectSocket : the TCP socket to operate on 
 *                    (e.g. output of TCP_Connect)
 *	- buffer : the packets to send
 *	- length : the number of bytes the packet contains
 * OUTPUT:
 *  - 0 : succeed			1 : fail
 ************************************************************************************/
int TCP_Send(SOCKET ConnectSocket, uint8 *buffer, int length){
    
	int iResult;

	// Send 'length' number of bytes from buffer via provided
	iResult = send( ConnectSocket, buffer, length, MSG_DONTROUTE );
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // for debugging:
	// printf("Bytes Sent: %ld\n", iResult);
	
    return 0;
}

/************************************************************************************
 *                           TCP_Receive
 * INPUT: 
 *	- ConnectSocket : the TCP socket to operate on 
 *                    (e.g. output of TCP_Connect)
 *	- buffer : where to store the retrieved packets
 *	- length : the number of bytes to retrieve
 * OUTPUT:
 *  - 0 : succeed			1 : fail
 ************************************************************************************/
int TCP_Receive(SOCKET ConnectSocket, uint8 *buffer, int length){

	int iResult;

    //Retrieve 'length' number of bytes into 'buffer' from the socket <sock> address
	iResult = recv(ConnectSocket, buffer, length, 0);
        if (iResult > 0) {
            // printf("Bytes received: %d\n", iResult);
		} else  {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            WSACleanup();
            return 1;
        }

    return 0;
}

/************************************************************************************
 *                           TCP_Disconnect
 * INPUT: 
  *	- ConnectSocket : the TCP socket to operate on 
 *                    (e.g. output of TCP_Connect)
 * OUTPUT:
 *  - 0 : succeed			1 : fail
 ************************************************************************************/
int TCP_Disconnect(SOCKET ConnectSocket){
	
	int iResult;

	//free and cleanup socket occupied memory
	iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    } 

    //cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}
