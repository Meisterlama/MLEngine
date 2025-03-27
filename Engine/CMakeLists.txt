message(STATUS "Configuring MLEngine")

MLCreateAndSelectEngineTarget() # Select between SHARED and STATIC library and create MLEngine_Engine target
MLConfigureTarget(${MLEngine_BuiltTarget})

MLAddModule(CoreInterfaces)
MLAddModule(Core)
MLAddModule(Debug)
MLAddModule(Inputs)
MLAddModule(Resource)
MLAddModule(Platform)

if(MLEngine_Options_Rendering)
    MLAddModule(Rendering)
endif()

message(STATUS "MLEngine have been configured")
