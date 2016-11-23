/*
** tcp.c - SS::TCP class
**
** Copyright (c) dojineko 2016
**
** See Copyright Notice in LICENSE
*/

#include <string.h>
#include <arpa/inet.h>

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/class.h"

typedef struct {
  char* ip;
  int ip_len;
  int port;
} mrb_tcp_data;

static const struct mrb_data_type mrb_tcp_data_type = {
  "mrb_tcp_data", mrb_free,
};

static mrb_value mrb_ss_init(mrb_state* mrb, mrb_value self) {
  mrb_tcp_data* data;
  char* ip;
  int ip_len;
  int port;

  data = (mrb_tcp_data*)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_tcp_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "si", &ip, &ip_len, &port);
  data = (mrb_tcp_data*)mrb_malloc(mrb, sizeof(mrb_tcp_data));
  data->ip = ip;
  data->ip_len = ip_len;
  data->port = port;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_tcp_is_listen(mrb_state* mrb, mrb_value self) {
  mrb_tcp_data* data = (mrb_tcp_data*)DATA_PTR(self);
  int check_port = data->port;

  FILE* procinfo;
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

  procinfo = fopen("/proc/net/tcp", "r");

  do {
    if (fgets(buffer, sizeof(buffer), procinfo)) {
      sscanf(buffer, "%d: %64[0-9A-Fa-f]:%X %64[0-9A-Fa-f]:%X %X %lX:%lX %X:%lX "
                     "%lX %d %d %ld %512s\n",
             &d, local_addr, &local_port, rem_addr, &rem_port, &state, &txq, &rxq,
             &timer_run, &time_len, &retr, &uid, &timeout, &inode, more);

      if (check_port == local_port) {
        struct sockaddr_in localaddr;
        sscanf(local_addr, "%X", &((struct sockaddr_in *)&localaddr)->sin_addr.s_addr);
        ((struct sockaddr *)&localaddr)->sa_family = AF_INET;

        if ( strcmp( data->ip, inet_ntoa(localaddr.sin_addr) ) == 0 ) {
            return mrb_bool_value(TRUE);
        }
      }
    }
  } while (!feof(procinfo));

  return mrb_bool_value(FALSE);
}

void mrb_init_tcp(mrb_state* mrb) {
  struct RClass* ss;
  struct RClass* tcp;
  ss = mrb_module_get(mrb, "SS");
  tcp = mrb_define_class_under(mrb, ss, "TCP", mrb->object_class);
  MRB_SET_INSTANCE_TT(tcp, MRB_TT_DATA);

  mrb_define_method(mrb, tcp, "initialize", mrb_ss_init, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, tcp, "listen?", mrb_tcp_is_listen, MRB_ARGS_NONE());
}
