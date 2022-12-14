#include "stm32_udp_client.h"

#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"

#include "stdio.h"
#include "string.h"

void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

u8_t   data[100];
volatile uint32_t message_count = 0;
struct udp_pcb *upcb;

void udp_client_connect(void)
{
  ip_addr_t DestIPaddr;
  err_t err;

  upcb = udp_new();

  if (upcb!=NULL)
  {
    ip_addr_t myIPaddr;
	IP_ADDR4(&myIPaddr, IP_CLIENT_ADDR0, IP_CLIENT_ADDR1, IP_CLIENT_ADDR2, IP_CLIENT_ADDR3);
	udp_bind(upcb, &myIPaddr, UDP_CLIENT_PORT);

    IP4_ADDR( &DestIPaddr, DEST_IP_ADDR0, DEST_IP_ADDR1, DEST_IP_ADDR2, DEST_IP_ADDR3 );
    err= udp_connect(upcb, &DestIPaddr, UDP_SERVER_PORT);

    if (err == ERR_OK)
    {
      udp_recv(upcb, udp_receive_callback, NULL);
    }
  }
}

void udp_client_send(void)
{
  struct pbuf *p;

  sprintf((char*)data, "client message count %d\r\n", (int)message_count);

  p = pbuf_alloc(PBUF_TRANSPORT,strlen((char*)data), PBUF_RAM);

  if (NULL != p)
  {
    pbuf_take(p, (char*)data, strlen((char*)data));
    udp_send(upcb, p);
    pbuf_free(p);
  }
}

void udp_client_send_string(char *dataToSend)
{
	  struct pbuf *p;

	  sprintf((char*)data, dataToSend);

	  p = pbuf_alloc(PBUF_TRANSPORT,strlen((char*)data), PBUF_RAM);

	  if (p != NULL)
	  {
	    pbuf_take(p, (char*)data, strlen((char*)data));
	    udp_send(upcb, p);
	    pbuf_free(p);
	  }
}

void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
  message_count++;
  udp_client_send_string(p->payload);
  pbuf_free(p);
}

