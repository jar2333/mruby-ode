#include <init.h>

#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/array.h>

#include <ode/ode.h>

//To-do: make thread specific mechanism instead of global
int is_initialized = 0;

int ode_initialize_for_thread() {
    is_initialized = dAllocateODEDataForThread(dAllocateMaskAll);
    return is_initialized;
}

void ode_cleanup_for_thread() {
    is_initialized = 0;
    dCleanupODEAllDataForThread();
}

int is_ode_initialized_for_thread() {
    return is_initialized;
}

mrb_value is_ode_initialized(mrb_state *mrb, mrb_value self) {
    return mrb_bool_value((mrb_bool)is_initialized);
}

void append_Init(mrb_state *mrb, struct RClass *ode_module) {
    mrb_define_class_method(mrb, ode_module, "initialized?", is_ode_initialized, MRB_ARGS_NONE());
}