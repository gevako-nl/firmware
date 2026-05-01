import esphome.codegen as cg
import esphome.config_validation as cv
import os

CODEOWNERS = ["@gevako-nl"]

# Schema to activate the component
CONFIG_SCHEMA = cv.Schema({})

async def to_code(config):
    current_dir = os.path.dirname(__file__)
    # Add the current directory to include path
    cg.add_build_flag("-I" + current_dir)
    # Global include for the header file
    cg.add_global(cg.RawExpression('#include "thread_provisioning.h"'))
