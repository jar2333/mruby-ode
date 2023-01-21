#include <world.h>
#include <init.h>

#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/array.h>

#include <ode/ode.h>

struct RClass *World_class;

/*
 * Called when the garbage collector tries to dispose of the object
*/
void World_free(mrb_state *mrb, void *id) {
    if (is_ode_initialized_for_thread()) {
        dWorldDestroy((dWorldID)id);
    }
}

static const mrb_data_type World_type = {
  "World", World_free
};


/**
 * ==============================
 * General functions
 * ==============================
*/

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
 * Impulse to Force
*/

mrb_value World_impulse_to_force(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float step_size, ix, iy, iz;
    mrb_get_args(mrb, "ffff", &step_size, &ix, &iy, &iz);

    dVector3 force;
    dWorldImpulseToForce(id, (dReal)step_size, (dReal)ix, (dReal)iy, (dReal)iz, force);

    mrb_value x = mrb_float_value(mrb, force[0]);
    mrb_value y = mrb_float_value(mrb, force[1]);
    mrb_value z = mrb_float_value(mrb, force[2]);

    mrb_value values[3] = {x, y, z};
    return mrb_ary_new_from_values(mrb, 3, values);
}

/**
 * ==============================
 * Stepping functions
 * ==============================
*/

mrb_value World_step(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float step_size;
    mrb_get_args(mrb, "f", &step_size);

    dWorldStep(id, (dReal)step_size);

    return mrb_nil_value();
}

mrb_value World_quick_step(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float step_size;
    mrb_get_args(mrb, "f", &step_size);

    dWorldQuickStep(id, (dReal)step_size);

    return mrb_nil_value();
}

mrb_value World_set_quick_step_iterations(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_int iterations;
    mrb_get_args(mrb, "i", &iterations);

    dWorldSetQuickStepNumIterations(id, (int)iterations);

    return mrb_nil_value();
}

mrb_value World_get_quick_step_iterations(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    int iterations = dWorldGetQuickStepNumIterations(id);

    return mrb_int_value(mrb, (mrb_int)iterations);
}

mrb_value World_set_quick_step_w(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float w;
    mrb_get_args(mrb, "f", &w);

    dWorldSetQuickStepW(id, (dReal)w);

    return mrb_nil_value();
}

mrb_value World_get_quick_step_w(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    dReal w = dWorldGetQuickStepW(id);

    return mrb_float_value(mrb, (mrb_float)w);
}

/**
 * ==============================
 * Damping
 * ==============================
*/

// Linear Damping

mrb_value World_set_linear_damping(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float scale;
    mrb_get_args(mrb, "f", &scale);

    dWorldSetLinearDamping(id, (dReal)scale);

    return mrb_nil_value();
}

mrb_value World_get_linear_damping(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    dReal scale = dWorldGetLinearDamping(id);

    return mrb_float_value(mrb, (mrb_float)scale);
}

// Angular Threshold

mrb_value World_set_angular_damping(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float scale;
    mrb_get_args(mrb, "f", &scale);

    dWorldSetAngularDamping(id, (dReal)scale);

    return mrb_nil_value();
}

mrb_value World_get_angular_damping(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    dReal scale = dWorldGetAngularDamping(id);

    return mrb_float_value(mrb, (mrb_float)scale);
}

// Combined

mrb_value World_set_damping(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float linear_scale, angular_scale;
    mrb_get_args(mrb, "ff", &linear_scale, &angular_scale);

    dWorldSetDamping(id, (dReal)linear_scale, (dReal)angular_scale);

    return mrb_nil_value();
}

// Linear Threshold

mrb_value World_set_linear_damping_threshold(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float threshold;
    mrb_get_args(mrb, "f", &threshold);

    dWorldSetLinearDampingThreshold(id, (dReal)threshold);

    return mrb_nil_value();
}

mrb_value World_get_linear_damping_threshold(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    dReal threshold = dWorldGetLinearDampingThreshold(id);

    return mrb_float_value(mrb, (mrb_float)threshold);
}

// Angular Threshold

mrb_value World_set_angular_damping_threshold(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float threshold;
    mrb_get_args(mrb, "f", &threshold);

    dWorldSetAngularDampingThreshold(id, (dReal)threshold);

    return mrb_nil_value();
}

mrb_value World_get_angular_damping_threshold(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    dReal threshold = dWorldGetAngularDampingThreshold(id);

    return mrb_float_value(mrb, (mrb_float)threshold);
}

// Max angular speed

mrb_value World_set_max_angular_speed(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float max_speed;
    mrb_get_args(mrb, "f", &max_speed);

    dWorldSetMaxAngularSpeed(id, (dReal)max_speed);

    return mrb_nil_value();
}

mrb_value World_get_max_angular_speed(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    dReal max_speed = dWorldGetMaxAngularSpeed(id);

    return mrb_float_value(mrb, (mrb_float)max_speed);
}

/**
 * ===============================
 * Contact Parameters
 * ===============================
*/

// Max correcting velocity

mrb_value World_set_contact_max_correcting_velocity(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float velocity;
    mrb_get_args(mrb, "f", &velocity);

    dWorldSetContactMaxCorrectingVel(id, (dReal)velocity);

    return mrb_nil_value();
}

mrb_value World_get_contact_max_correcting_velocity(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    dReal velocity = dWorldGetContactMaxCorrectingVel(id);

    return mrb_float_value(mrb, (mrb_float)velocity);
}

// Contact surface layer

mrb_value World_set_contact_surface_layer(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    mrb_float depth;
    mrb_get_args(mrb, "f", &depth);

    dWorldSetContactSurfaceLayer(id, (dReal)depth);

    return mrb_nil_value();
}

mrb_value World_get_contact_surface_layer(mrb_state *mrb, mrb_value self) {
    dWorldID id = (dWorldID)DATA_PTR(self);

    dReal depth = dWorldGetContactSurfaceLayer(id);

    return mrb_float_value(mrb, (mrb_float)depth);
}

/**
 * ===============================
 * Add World class to mrb state
 * ===============================
*/

void append_World(mrb_state *mrb, struct RClass *ode_module) {
    World_class = mrb_define_class_under(mrb, ode_module, "World", mrb->object_class);
    MRB_SET_INSTANCE_TT(World_class, MRB_TT_DATA);

    /*
    * General methods
    */

    mrb_define_method(mrb, World_class, "initialize", World_initialize, MRB_ARGS_NONE());

    mrb_define_method(mrb, World_class, "gravity=", World_set_gravity, MRB_ARGS_REQ(3));
    mrb_define_method(mrb, World_class, "gravity", World_get_gravity, MRB_ARGS_NONE());

    mrb_define_method(mrb, World_class, "erp=", World_set_erp, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "erp", World_get_erp, MRB_ARGS_NONE());

    mrb_define_method(mrb, World_class, "cfm=", World_set_cfm, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "cfm", World_get_cfm, MRB_ARGS_NONE());

    //remove prefix? make module? revisit this code
    mrb_define_method(mrb, World_class, "auto_disable=", World_set_auto_disable_flag, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "auto_disable", World_get_auto_disable_flag, MRB_ARGS_NONE()); 
    mrb_define_alias(mrb, World_class, "auto_disable?", "auto_disable"); // Ruby convention

    mrb_define_method(mrb, World_class, "auto_disable_linear_threshold=", World_set_auto_disable_linear_threshold, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "auto_disable_linear_threshold", World_get_auto_disable_linear_threshold, MRB_ARGS_NONE());

    mrb_define_method(mrb, World_class, "auto_disable_angular_threshold=", World_set_auto_disable_angular_threshold, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "auto_disable_angular_threshold", World_get_auto_disable_angular_threshold, MRB_ARGS_NONE());

    mrb_define_method(mrb, World_class, "auto_disable_steps=", World_set_auto_disable_steps, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "auto_disable_steps", World_get_auto_disable_steps, MRB_ARGS_NONE());

    mrb_define_method(mrb, World_class, "auto_disable_time=", World_set_auto_disable_time, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "auto_disable_time", World_get_auto_disable_time, MRB_ARGS_NONE());

    mrb_define_method(mrb, World_class, "impulse_to_force", World_impulse_to_force, MRB_ARGS_REQ(4));

    /*
    * Stepping methods
    */

    mrb_define_method(mrb, World_class, "step!", World_step, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "quick_step!", World_quick_step, MRB_ARGS_REQ(1));

    mrb_define_method(mrb, World_class, "quick_step_iterations=", World_set_quick_step_iterations, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "quick_step_iterations", World_get_quick_step_iterations, MRB_ARGS_NONE());

    mrb_define_method(mrb, World_class, "quick_step_w=", World_set_quick_step_w, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "quick_step_w", World_get_quick_step_w, MRB_ARGS_NONE());

    /*
    * Damping
    */

    mrb_define_method(mrb, World_class, "linear_damping=", World_set_linear_damping, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "linear_damping", World_get_linear_damping, MRB_ARGS_NONE());
 
    mrb_define_method(mrb, World_class, "angular_damping=", World_set_angular_damping, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "angular_damping", World_get_angular_damping, MRB_ARGS_NONE());

    mrb_define_method(mrb, World_class, "damping=", World_set_damping, MRB_ARGS_REQ(2));

    mrb_define_method(mrb, World_class, "linear_damping_threshold=", World_set_linear_damping_threshold, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "linear_damping_threshold", World_get_linear_damping_threshold, MRB_ARGS_NONE());

    mrb_define_method(mrb, World_class, "angular_damping_threshold=", World_set_angular_damping_threshold, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "angular_damping_threshold", World_get_angular_damping_threshold, MRB_ARGS_NONE());

    mrb_define_method(mrb, World_class, "max_angular_speed=", World_set_max_angular_speed, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "max_angular_speed", World_get_max_angular_speed, MRB_ARGS_NONE());

    /*
    * Contact parameters
    */

    mrb_define_method(mrb, World_class, "contact_max_correcting_velocity=", World_set_contact_max_correcting_velocity, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "contact_max_correcting_velocity", World_get_contact_max_correcting_velocity, MRB_ARGS_NONE());

    mrb_define_method(mrb, World_class, "contact_surface_layer=", World_set_contact_surface_layer, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, World_class, "contact_surface_layer", World_get_contact_surface_layer, MRB_ARGS_NONE());


}
