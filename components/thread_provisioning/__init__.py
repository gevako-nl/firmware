# Python script to register the custom component and include the header file
import esphome.codegen as cg
import esphome.config_validation as cv

# The namespace in your C++ code
# Replace this if your namespace is different
thread_prov_ns = cg.esphome_ns.namespace('thread_prov')

# Required schema for component registration
CONFIG_SCHEMA = cv.Schema({})

async def to_code(config):
    # This line forces the compiler to include the specific header file
    cg.add_global(cg.RawExpression('#include "thread_provisioning.h"'))
