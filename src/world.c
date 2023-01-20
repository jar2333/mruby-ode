#include <world.h>

#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/array.h>

#include <ode/ode.h>

void World_free(mrb_state *mrb, void *id) {
    dWorldDestroy((dWorldID)id);
}

static const mrb_data_type World_type = {
  "World", World_free
};

/**
 * Initialize
*/

mrb_value World_initialize(mrb_state *mrb, mrb_value self) {

    dWorldID id = (dWorldID)DATA_PTR(self);
    if (id) { 
        dWorldDestroy(id); 
    }

    mrb_data_init(self, NULL, &World_type);

    id = dWorldCreate();

    mrb_data_init(self, id, &World_type);

    return self;
}

/**
 * Gravity
*/

mrb_value World_set_gravity(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float x, y, z;
    mrb_get_args(mrb, "fff", &x, &y, &z);

    dWorldSetGravity(id, (dReal)x, (dReal)y, (dReal)z);

    return mrb_nil_value();
}

mrb_value World_get_gravity(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    dVector3 gravity;

    dWorldGetGravity(id, gravity);

    mrb_value x = mrb_float_value(mrb, gravity[0]);
    mrb_value y = mrb_float_value(mrb, gravity[1]);
    mrb_value z = mrb_float_value(mrb, gravity[2]);

    mrb_value values[3] = {x, y, z};
    return mrb_ary_new_from_values(mrb, 3, values);
}

/**
 * ERB
*/

mrb_value World_set_erp(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float erp;
    mrb_get_args(mrb, "f", &erp);

    dWorldSetERP(id, (dReal)erp);

    return mrb_nil_value();
}

mrb_value World_get_erp(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    dReal erp = dWorldGetERP(id);

    return mrb_float_value(mrb, (mrb_float)erp);
}

/**
 * CFM
*/

mrb_value World_set_cfm(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float cfm;
    mrb_get_args(mrb, "f", &cfm);

    dWorldSetERP(id, (dReal)cfm);

    return mrb_nil_value();
}

mrb_value World_get_cfm(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    dReal cfm = dWorldGetCFM(id);

    return mrb_float_value(mrb, (mrb_float)cfm);
}

/**
 * Auto-disable parameters
*/

// Flag 

mrb_value World_set_auto_disable_flag(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_bool auto_disable;
    mrb_get_args(mrb, "b", &auto_disable);

    dWorldSetAutoDisableFlag(id, (int)auto_disable);

    return mrb_nil_value();
}

mrb_value World_get_auto_disable_flag(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    int auto_disable = dWorldGetAutoDisableFlag(id);

    return mrb_bool_value((mrb_bool)auto_disable);
}

// Linear Threshold

mrb_value World_set_auto_disable_linear_threshold(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float threshold;
    mrb_get_args(mrb, "f", &threshold);

    dWorldSetAutoDisableLinearThreshold(id, (dReal)threshold);

    return mrb_nil_value();
}

mrb_value World_get_auto_disable_linear_threshold(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    dReal threshold = dWorldGetAutoDisableLinearThreshold(id);

    return mrb_float_value(mrb, (mrb_float)threshold);
}

// Angular Threshold

mrb_value World_set_auto_disable_angular_threshold(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float threshold;
    mrb_get_args(mrb, "f", &threshold);

    dWorldSetAutoDisableAngularThreshold(id, (dReal)threshold);

    return mrb_nil_value();
}

mrb_value World_get_auto_disable_angular_threshold(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    dReal threshold = dWorldGetAutoDisableAngularThreshold(id);

    return mrb_float_value(mrb, (mrb_float)threshold);
}

// Steps

mrb_value World_set_auto_disable_steps(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_int steps;
    mrb_get_args(mrb, "i", &steps);

    dWorldSetAutoDisableSteps(id, (int)steps);

    return mrb_nil_value();
}

mrb_value World_get_auto_disable_steps(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    int steps = dWorldGetAutoDisableSteps(id);

    return mrb_int_value(mrb, (mrb_int)steps);
}

// Time

mrb_value World_set_auto_disable_time(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float time;
    mrb_get_args(mrb, "f", &time);

    dWorldSetAutoDisableTime(id, (dReal)time);

    return mrb_nil_value();
}

mrb_value World_get_auto_disable_time(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    dReal time = dWorldGetAutoDisableTime(id);

    return mrb_float_value(mrb, (mrb_float)time);
}

/**
 * Add World class to mrb state
*/

void append_World(mrb_state *mrb) {
    World_class = mrb_define_class(mrb, "World", mrb->object_class);
    MRB_SET_INSTANCE_TT(World_class, MRB_TT_DATA);

    mrb_define_method(mrb, World_class, "initialize", World_initialize, MRB_ARGS_NONE());

    mrb_define_method(mrb, World_class, "gravity=", World_set_gravity, MRB_ARGS_REQ(3));
    mrb_define_method(mrb, World_class, "gravity", World_get_gravity, MRB_ARGS_NONE());

    mrb_define_method(mrb, World_class, "erp=", World_set_erp, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "erp", World_get_erp, MRB_ARGS_NONE());

    mrb_define_method(mrb, World_class, "cfm=", World_set_cfm, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "cfm", World_get_cfm, MRB_ARGS_NONE());

    //remove prefix? add alias? make module? revisit this code
    mrb_define_method(mrb, World_class, "auto_disable=", World_set_auto_disable_flag, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "auto_disable", World_get_auto_disable_flag, MRB_ARGS_NONE()); //add alias method with ?
    mrb_define_method(mrb, World_class, "auto_disable_linear_threshold=", World_set_auto_disable_linear_threshold, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "auto_disable_linear_threshold", World_get_auto_disable_linear_threshold, MRB_ARGS_NONE());
    mrb_define_method(mrb, World_class, "auto_disable_angular_threshold=", World_set_auto_disable_angular_threshold, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "auto_disable_angular_threshold", World_get_auto_disable_angular_threshold, MRB_ARGS_NONE());
    mrb_define_method(mrb, World_class, "auto_disable_steps=", World_set_auto_disable_steps, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "auto_disable_steps", World_get_auto_disable_steps, MRB_ARGS_NONE());
    mrb_define_method(mrb, World_class, "auto_disable_time=", World_set_auto_disable_time, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "auto_disable_time", World_get_auto_disable_time, MRB_ARGS_NONE());

}