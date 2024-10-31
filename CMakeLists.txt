cmake_minimum_required(VERSION 3.14.0)

option(SMTG_ENABLE_VST3_PLUGIN_EXAMPLES "Enable VST 3 Plug-in Examples" OFF)
option(SMTG_ENABLE_VST3_HOSTING_EXAMPLES "Enable VST 3 Hosting Examples" OFF)

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

set(vst3sdk_SOURCE_DIR "C:/Users/jared/Downloads/vst-sdk_3.7.11_build-10_2024-04-22/VST_SDK/vst3sdk")
if(NOT vst3sdk_SOURCE_DIR)
    message(FATAL_ERROR "Path to VST3 SDK is empty!")
endif()

project(Strainer
    # This is your plug-in version number. Change it here only.
    # Version number symbols usable in C++ can be found in
    # source/version.h and ${PROJECT_BINARY_DIR}/projectversion.h.
    VERSION 1.0.0.0 
    DESCRIPTION "Strainer VST 3 Plug-in"
)

set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(Strainer
    source/version.h
    source/strainercids.h
    source/strainerprocessor.h
    source/strainerprocessor.cpp
    source/strainercontroller.h
    source/strainercontroller.cpp
    source/strainerentry.cpp
)

#- VSTGUI Wanted ----
if(SMTG_ENABLE_VSTGUI_SUPPORT)
    target_sources(Strainer
        PRIVATE
            resource/strainereditor.uidesc
    )
    target_link_libraries(Strainer
        PRIVATE
            vstgui_support
    )
    smtg_target_add_plugin_resources(Strainer
        RESOURCES
            "resource/strainereditor.uidesc"
    )
endif(SMTG_ENABLE_VSTGUI_SUPPORT)
# -------------------

smtg_target_add_plugin_snapshots (Strainer
    RESOURCES
        resource/47C5243B2155562C895FECB5FB791EB7_snapshot.png
        resource/47C5243B2155562C895FECB5FB791EB7_snapshot_2.0x.png
)

target_link_libraries(Strainer
    PRIVATE
        sdk
)

smtg_target_configure_version_file(Strainer)

if(SMTG_MAC)
    smtg_target_set_bundle(Strainer
        BUNDLE_IDENTIFIER com.vargason.strainer
        COMPANY_NAME "Vargason"
    )
    smtg_target_set_debug_executable(Strainer
        "/Applications/VST3PluginTestHost.app"
        "--pluginfolder;$(BUILT_PRODUCTS_DIR)"
    )
elseif(SMTG_WIN)
    target_sources(Strainer PRIVATE 
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Strainer)

        smtg_target_set_debug_executable(Strainer
            "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
            "--pluginfolder \"$(OutDir)/\""
        )
    endif()
endif(SMTG_MAC)
