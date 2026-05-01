# Script to register the component and force the include path
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
import os

# Registry for the component
CODEOWNERS = ["@gevako-nl"]

# Define the C++ namespace and the component class
thread_prov_ns = cg.esphome_ns.namespace('thread_prov')
ThreadProvisioning = thread_prov_ns.class_('ThreadProvisioning', cg.Component)

# Schema to make the component valid and loadable in YAML
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ThreadProvisioning),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    # Get the absolute path to the directory where this file is located
    current_dir = os.path.dirname(__file__)
    
    # Force the compiler to add this directory to its include search paths
    cg.add_build_flag("-I" + current_dir)
    
    # Inject the global include statement into the generated C++ code
    cg.add_global(cg.RawExpression('#include "thread_provisioning.h"'))
    
    # Create the C++ component instance and register it
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
