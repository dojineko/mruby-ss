/*
** tcp.c - SS::TCP class
**
** Copyright (c) dojineko 2016
**
** See Copyright Notice in LICENSE
*/

#include <stdlib.h>
#include "mruby.h"
#include "mruby/data.h"
#include "mruby/class.h"
#include "ipv4.h"
#include "namespace.h"

typedef struct {
  char* ip;
  int ip_len;
  int port;
  char* ns;
  int ns_len;
} mrb_tcp_data;

static const struct mrb_data_type mrb_tcp_data_type = {
  "mrb_tcp_data", mrb_free,
};

static mrb_value mrb_ss_init(mrb_state* mrb, mrb_value self) {
  mrb_tcp_data* data;
  char* ip;
  int ip_len;
  int port;
  char* ns;
  int ns_len;

  data = (mrb_tcp_data*)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_tcp_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "si|s", &ip, &ip_len, &port, &ns, &ns_len);
  data = (mrb_tcp_data*)mrb_malloc(mrb, sizeof(mrb_tcp_data));
  data->ip = ip;
  data->ip_len = ip_len;
  data->port = port;
  data->ns = ns;
  data->ns_len = ns_len;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_tcp_is_listen( mrb_state* mrb, mrb_value self ) {
  mrb_tcp_data* data = ( mrb_tcp_data* )DATA_PTR( self );
  if(data->ns_len > 0) {
    if (netns_switch(data->ns)) {
        exit(1);
    }
  }
  return mrb_bool_value( search_listen( "/proc/net/tcp", data->ip, data->port ) );
}

void mrb_init_tcp(mrb_state* mrb) {
  struct RClass* ss;
  struct RClass* tcp;
  ss = mrb_module_get(mrb, "SS");
  tcp = mrb_define_class_under(mrb, ss, "TCP", mrb->object_class);
  MRB_SET_INSTANCE_TT(tcp, MRB_TT_DATA);

  mrb_define_method(mrb, tcp, "initialize", mrb_ss_init, MRB_ARGS_ARG(2, 1));
  mrb_define_method(mrb, tcp, "listen?", mrb_tcp_is_listen, MRB_ARGS_NONE());
}
