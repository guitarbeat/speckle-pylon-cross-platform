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
* @file    lcr_packetizer.h
*
* @brief	This file is responsible for packetizing the data. The functions defined in this file are called by lcr_cmd file
**/
/**************************************************************************************************************************************************/

#ifndef LCR_PACKETIZER_H_
#define LCR_PACKETIZER_H_

#include "common.h"
#include "error.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HEADER_SIZE			6
#define MAX_PACKET_SIZE		0xFFFF
#define CHECKSUM_SIZE		1

#define LCR_CMD_IP			"192.168.1.100"
#define LCR_CMD_PORT		0x5555

    enum LCR_PacketType {
        PKT_TYPE_BUSY,
        PKT_TYPE_ERROR,
        PKT_TYPE_WRITE,
        PKT_TYPE_WRITE_RESP,
        PKT_TYPE_READ,
        PKT_TYPE_READ_RESP
    };

    typedef enum
    {
        LCR_CMD_PKT_TYPE_READ,
        LCR_CMD_PKT_TYPE_WRITE,
    } LCR_CommandType_t;

    ErrorCode_t LCR_CMD_PKT_ConnectToLCR(void);
    ErrorCode_t LCR_CMD_PKT_DisconnectLCR(void);

    int LCR_CMD_PKT_CommandInit(LCR_CommandType_t cmdType, uint16 cmd);
    int LCR_CMD_PKT_PutData(uint8 *data, unsigned long int size);
    int LCR_CMD_PKT_PutInt(uint32 value, unsigned int size);
    int LCR_CMD_PKT_GetData(uint8 *data, unsigned long int size);
    uint32 LCR_CMD_PKT_GetInt(unsigned int size);
    int LCR_CMD_PKT_PutFile(char const *fileName);
    int LCR_CMD_PKT_GetFile(char const *fileName,uint32 size);
    int LCR_CMD_PKT_SendCommand(void);

    int LCR_CMD_PKT_ReceivePacket(BOOL firstPkt);
    int LCR_CMD_PKT_SendPacket(BOOL more);

#ifdef __cplusplus
}
#endif

#endif /* LCR_PACKETIZER_H_ */

