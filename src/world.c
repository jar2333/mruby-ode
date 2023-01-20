#include <world.h>

#include <mruby/class.h>
#include <mruby/compile.h>
#include <mruby/data.h>
#include <mruby/variable.h>
#include <mruby/array.h>

#include <ode/ode.h>

void World_free(mrb_state *mrb, void *id) {
    dWorldDestroy((dWorldID)id);
}

static const mrb_data_type World_type = {
  "World", World_free
};

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


void append_World(mrb_state *mrb) {
    World_class = mrb_define_class(mrb, "World", mrb->object_class);
    MRB_SET_INSTANCE_TT(World_class, MRB_TT_DATA);

    mrb_define_method(mrb, World_class, "initialize", World_initialize, MRB_ARGS_REQ(0));
}