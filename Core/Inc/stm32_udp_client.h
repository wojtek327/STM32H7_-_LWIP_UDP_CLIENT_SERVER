#ifndef INC_STM32_UDP_CLIENT_H_
#define INC_STM32_UDP_CLIENT_H_

#define UDP_SERVER_PORT    ((uint16_t)7U)
#define UDP_CLIENT_PORT    ((uint16_t)7U)

/*Static DEST IP ADDRESS: DEST_IP_ADDR0.DEST_IP_ADDR1.DEST_IP_ADDR2.DEST_IP_ADDR3 */
#define DEST_IP_ADDR0   ((uint8_t)169U)
#define DEST_IP_ADDR1   ((uint8_t)254U)
#define DEST_IP_ADDR2   ((uint8_t)24U)
#define DEST_IP_ADDR3   ((uint8_t)21U)

/*Static IP ADDRESS: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3 */
#define IP_CLIENT_ADDR0   ((uint8_t)169U)
#define IP_CLIENT_ADDR1   ((uint8_t)254U)
#define IP_CLIENT_ADDR2   ((uint8_t)24U)
#define IP_CLIENT_ADDR3   ((uint8_t)157U)

void udp_client_connect(void);
void udp_client_send(void);
void udp_client_send_string(char *dataToSend);

#endif /* INC_STM32_UDP_CLIENT_H_ */
