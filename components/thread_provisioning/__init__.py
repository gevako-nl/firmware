import esphome.codegen as cg

async def to_code(config):
    cg.add_global(cg.RawStatement('#include "thread_provisioning.h"'))
