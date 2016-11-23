/*
** mrb_ss.c - SS class
**
** Copyright (c) dojineko 2016
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mrb_ss.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

void mrb_init_ss(mrb_state* mrb);
void mrb_init_tcp(mrb_state* mrb);

void mrb_mruby_ss_gem_init(mrb_state* mrb) {
  mrb_init_ss(mrb); DONE;
  mrb_init_tcp(mrb); DONE;
}

void mrb_mruby_ss_gem_final(mrb_state* mrb) {
}
