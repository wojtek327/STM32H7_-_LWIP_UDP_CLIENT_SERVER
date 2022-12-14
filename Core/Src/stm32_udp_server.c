#include "stm32_udp_server.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"

#include "stdio.h"
#include "string.h"

void udp_server_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);

u8_t   data[100];
__IO uint32_t message_count_server = 0;
struct udp_pcb *upcb;

void udp_server_init(void)
{
   err_t err;
   upcb = udp_new();

   if (NULL != upcb)
   {
      err = udp_bind(upcb, IP_ADDR_ANY, SERVER_UDP_SERVER_PORT);

      if(ERR_OK == err)
      {
        udp_recv(upcb, udp_server_receive_callback, NULL);
      }
      else
      {
        udp_remove(upcb);
      }
   }
}

void udp_server_send_message(void)
{
	struct pbuf *p;

	sprintf((char*)data, "test");

	/* allocate pbuf from pool*/
	p = pbuf_alloc(PBUF_TRANSPORT,strlen((char*)data), PBUF_RAM);

	if (p != NULL)
	{
      ip_addr_t myIPADDR;
	  IP_ADDR4(&myIPADDR, UDP_CLIENT_ADDR0, UDP_CLIENT_ADDR1, UDP_CLIENT_ADDR2, UDP_CLIENT_ADDR3);
	  pbuf_take(p, (char*)data, strlen((char*)data));
	  udp_sendto(upcb, p, &myIPADDR, SERVER_UDP_CLIENT_PORT);
	  pbuf_free(p);
	}
}

void udp_server_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
  struct pbuf *p_tx;

  /* allocate pbuf from RAM*/
  p_tx = pbuf_alloc(PBUF_TRANSPORT,p->len, PBUF_RAM);

  if(p_tx != NULL)
  {
    pbuf_take(p_tx, (char*)p->payload, p->len);
    udp_connect(upcb, addr, SERVER_UDP_CLIENT_PORT);
    udp_send(upcb, p_tx);
    udp_disconnect(upcb);
    pbuf_free(p_tx);
    pbuf_free(p);
  }
}


