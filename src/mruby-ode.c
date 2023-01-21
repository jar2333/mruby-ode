#include <ode/ode.h>
#include <ode/odeinit.h>

#include <mruby-ode.h>

#include <init.h>
#include <world.h>

struct RClass *ode_module;

void mrb_mruby_ode_gem_init(mrb_state* mrb) {
    dInitODE2(dInitFlagManualThreadCleanup);
    ode_initialize_for_thread();

    ode_module = mrb_define_module(mrb, "ODE");
    append_Init(mrb, ode_module);
    append_World(mrb, ode_module);
}

void mrb_mruby_ode_gem_final(mrb_state* mrb) {
    is_initialized = 0;

    dCloseODE();
}