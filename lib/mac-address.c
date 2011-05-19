#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>

char *getMACAddress()
{
  #define MAC_STRING_LENGTH 13
  char *ret = malloc(MAC_STRING_LENGTH);
  struct ifreq s;
  int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
  
  // You may need to use "eth0" or another interface here instead of eth1
  strcpy(s.ifr_name, "eth1");
  if (fd >= 0 && ret && 0 == ioctl(fd, SIOCGIFHWADDR, &s))
  {
    int i;
    for (i = 0; i < 6; ++i)
      snprintf(ret+i*2,MAC_STRING_LENGTH-i*2,"%02x",(unsigned char) s.ifr_addr.sa_data[i]);
  }
  else
  {
    perror("malloc/socket/ioctl failed");
    return(ret);
  }
  return(ret);
}