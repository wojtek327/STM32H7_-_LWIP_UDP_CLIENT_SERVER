#ifndef __STM32F7_UDP_SERVER_H
#define __STM32F7_UDP_SERVER_H

/* UDP local connection port */
#define SERVER_UDP_SERVER_PORT    7
/* UDP remote connection port */
#define SERVER_UDP_CLIENT_PORT    8

#define UDP_CLIENT_ADDR0   (uint8_t) 169
#define UDP_CLIENT_ADDR1   (uint8_t) 254
#define UDP_CLIENT_ADDR2   (uint8_t) 24
#define UDP_CLIENT_ADDR3   (uint8_t) 21

void udp_server_init(void);
void udp_server_send_message(void);

#endif // __STM32F7_UDP_SERVER_H
