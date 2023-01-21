#include <ode/ode.h>

#include <mruby-ode.h>

#include <world.h>

void mrb_mruby_ode_gem_init(mrb_state* mrb) {
    dInitODE();
    append_World(mrb);
}

void mrb_mruby_ode_gem_final(mrb_state* mrb) {
    dCloseODE();
}