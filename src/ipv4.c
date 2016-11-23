/*
** ipv4.c
**
** Copyright (c) dojineko 2016
**
** See Copyright Notice in LICENSE
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <arpa/inet.h>

bool search_listen( const char* filename, const char* ip, const int port ) {
  FILE* file;
  char buffer[8162];
  unsigned long txq;
  unsigned long rxq;
  unsigned long time_len;
  unsigned long retr;
  unsigned long inode;
  int d;
  int local_port;
  int rem_port;
  int state;
  int timer_run;
  int uid;
  int timeout;
  char local_addr[128];
  char rem_addr[128];
  char more[512];

  file = fopen( filename, "r" );

  do {
    if (fgets( buffer, sizeof( buffer ), file ) ) {
      sscanf( buffer, "%d: %64[0-9A-Fa-f]:%X %64[0-9A-Fa-f]:%X %X %lX:%lX %X:%lX "
                     "%lX %d %d %ld %512s\n",
             &d, local_addr, &local_port, rem_addr, &rem_port, &state, &txq, &rxq,
             &timer_run, &time_len, &retr, &uid, &timeout, &inode, more );

      if ( local_port == port ) {
        struct sockaddr_in localaddr;
        sscanf( local_addr, "%X", &( ( struct sockaddr_in * )&localaddr )->sin_addr.s_addr );
        ( ( struct sockaddr * )&localaddr )->sa_family = AF_INET;

        if ( strcmp( ip, inet_ntoa( localaddr.sin_addr ) ) == 0 ) {
            return true;
        }
      }
    }
  } while ( !feof( file ) );

  return false;
}
