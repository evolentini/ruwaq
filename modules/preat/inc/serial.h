/************************************************************************************************
Copyright (c) 2022-2023, Laboratorio de Microprocesadores
Facultad de Ciencias Exactas y Tecnología, Universidad Nacional de Tucumán
https://www.microprocesadores.unt.edu.ar/

Copyright (c) 2022-2023, Esteban Volentini <evolentini@herrera.unt.edu.ar>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

#ifndef SERIAL_H
#define SERIAL_H

/** \brief Serial server for preat protocol declarations
 **
 ** \addtogroup preat PREAT
 ** \brief Protocol for Remote Excecution of Automated Tests
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include "protocol.h"

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

#include "saio.h"

/* === Public data type declarations =========================================================== */

/**
 * @brief Data type to handle a server instance
 */
typedef struct preat_server_s * preat_server_t;

/**
 * @brief Callback function to notify when a completed frame is received
 */
typedef void (*preat_event_handler_t)(preat_server_t server, void * object);

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Function to create a prear server instance over a serial interface
 *
 * @param   sci             Serial port descriptor
 * @param   handler         Callback Function to notify when a full frame is received
 * @param   object          User pointer to send when callback function is called
 * @return  preat_server_t  Preat server instance descriptor
 */
preat_server_t SerialStartServer(hal_sci_t sci, preat_event_handler_t handler, void * object);

/**
 * @brief Function to get a command frame from reception buffer
 *
 * @param   server      Preat server instance descriptor obtained when starting the server
 * @param   command     Pointer to a variable with 64 bytes to copy the received frame
 * @return  true        There was a pending frame and it could be copied to the user variable
 * @return  false       There was no pending frame to receive
 */
bool SerialReceiveCommand(preat_server_t server, uint8_t * command);

/**
 * @brief Function to put a response in transmition buffer and send it
 *
 * @param server        Preat server instance descriptor obtained when starting the server
 * @param response      Pointer to a variable the response frame to transmit
 * @return true         The frame could be queued for transmission successfully
 * @return false        There is a transmission pending and the new frame can be queued
 */
bool SerialTransmitResponse(preat_server_t server, uint8_t * response);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* SERIAL_H */
