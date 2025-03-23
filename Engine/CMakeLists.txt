message(STATUS "Configuring MLEngine")

MLCreateAndSelectEngineTarget()
MLConfigureTarget(${MLEngine_BuiltTarget})

MLAddModule(CoreInterfaces)
MLAddModule(Core)
MLAddModule(Logger)
MLAddModule(Inputs)
MLAddModule(Resource)
MLAddModule(Platform)

if(MLEngine_Options_Rendering)
    MLAddModule(Rendering)
endif()

message(STATUS "MLEngine have been configured")
