/*
** ss.c - SS Module
**
** Copyright (c) dojineko 2016
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"

void mrb_init_ss(mrb_state* mrb) {
  struct RClass* ss;
  ss = mrb_define_module(mrb, "SS");
}
