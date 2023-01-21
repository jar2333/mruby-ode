#pragma once

#include <mruby.h>

//To-do: make thread specific mechanism instead of global
extern int is_initialized;
int ode_initialize_for_thread();
void ode_cleanup_for_thread();
int is_ode_initialized_for_thread();

void append_Init(mrb_state *mrb, struct RClass *ode_module);