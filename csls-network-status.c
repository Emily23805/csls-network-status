#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>

char t1[30];

/* ltime(); 함수*/
void ltime()
{
struct tm *date;
const time_t t = time(NULL);
date = localtime(&t);
           printf("%c[1;32m", 27);
           printf( "%d-%d-%d %d:%d:%d\n" , date->tm_year + 1900 , date->tm_mon + 1 , date->tm_mday , date->tm_hour , date->tm_min , date->tm_sec );
           printf("%c[0m", 27);
}
void ltimes()
{
	struct tm *date;
	const time_t t = time(NULL);
	date = localtime(&t);

           sprintf( t1, "%d/%d/%d %d:%d:%d\n" , date->tm_year + 1900 , date->tm_mon + 1 , date->tm_mday , date->tm_hour , date->tm_min , date->tm_sec );
}

/* nic-core */
void nic()
{
    struct ifaddrs *addrs,*tmp;
 
    getifaddrs(&addrs);
    tmp = addrs;
 
    while (tmp)
    {   
            if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_PACKET)
                        printf("%s\n", tmp->ifa_name);
 
                tmp = tmp->ifa_next;
    }   
 
    freeifaddrs(addrs);
}
/* end nic-core*/

/* ip-addr*/
void ipaddr()
{
	    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char *addr;

    getifaddrs (&ifap);
    for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr && ifa->ifa_addr->sa_family==AF_INET) {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);
            printf("%s\n", addr);
        }
    }

    freeifaddrs(ifap);
}
/*end ip-addr*/
/*boot script codes*/
void boot()
{
	    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char *addr;

    getifaddrs (&ifap);
    for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr && ifa->ifa_addr->sa_family==AF_INET) {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);
            printf("Interface: %s\tAddress: %s\n", ifa->ifa_name, addr);
        }
    }

    freeifaddrs(ifap);
	ltimes();
	printf("boot time:%s\n",t1);
}
/*end boot script codes*/
/* help() */
void help()
{
	printf("enet is clear sky linux series network test program\n========================================================\nuseing enet -tni\nuseing enet -t \n========================================================\n -t [print time]\n -n [print NIC(Network Interface controller , LAN card)]\n -i [print ip address]\n -l [print non lo NIC(Network Interface controller , LAN card)]\n -h [print enet help]\n -r [reboot system]\n========================================================\nReference list\n nic-core() [https://m.blog.naver.com/cksdn788/220379995787]\n ltime(),ltimes() [https://araikuma.tistory.com/597]\n ip-addr(),boot() [https://stackoverflow.com/questions/4139405/how-can-i-get-to-know-the-ip-address-for-interfaces-in-c]\n nicnonlo() [https://pencil1031.tistory.com/66]\n========================================================\nlicences\n Copyright kudansul\n Development by kudansul\nsource code/github\n https://github.com/fuyubi-network/csls-network-status.git\n========================================================\n");
}
/* end help() */
/* nic-core non-lo ver */
void nicnonlo()
{
    struct ifaddrs *addrs,*tmp;
 
    getifaddrs(&addrs);
    tmp = addrs;
 
    while (tmp)
    {   
            if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_PACKET)
            {
		        if(strcmp(tmp->ifa_name, "lo") != 0) 
    		    {
			        printf("%s\n",tmp->ifa_name);
			        break;
    		    }
            }
                tmp = tmp->ifa_next;
    }   
    freeifaddrs(addrs);
}
/* end nic-core non-lo ver*/
/* reboot this server/workstation/machen*/
void reboot()
{
    system("shutdown -r now");
}
/* end reboot */

int main( int argc, char **argv)
{
   int   param_opt;

   opterr   = 0;
   while( -1 !=( param_opt = getopt( argc, argv, "f:nithrlb")))
   {
      switch( param_opt)
      {
      case  'f'   :  printf( "%s \n", optarg);
                     break;
      case  'n'   :  nic();
			  	 	 break;
	  case	'i'	  :  ipaddr();
			  		 break;
      case  't'   :  ltime();
                     break;
	  case  'h'   :  help();
			  		 break;
	  case  'b'   :  boot();
			  		 break;
	  case  'l'   :  nicnonlo();
			  		 break;
	  case  'r'   :  reboot();
			  		 break;
      case  '?'   :  printf( "Try 'enet -h' for more information.\n", optopt);
                     break;
      }
   }
   return 0;
}
/*
void time()
{
    while (1)
    {
        ltime();
        sleep(1);
    }
}
*/
