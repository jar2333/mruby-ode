#pragma once

#include <mruby.h>

int is_ode_initialized_for_thread();

void append_World(mrb_state *mrb, struct RClass *ode_module);