cmake_minimum_required(VERSION 3.3)
project(VulkanIntroducingPVRVk)
if(IOS)
	message ("Skipping VulkanIntroducingPVRVk : Vulkan is not supported on iOS.")
	return()
endif()

add_subdirectory(../../.. ${CMAKE_CURRENT_BINARY_DIR}/sdk)

if(PVR_PREBUILT_DEPENDENCIES)
	find_package(PVRShell REQUIRED MODULE)
	find_package(PVRVk REQUIRED MODULE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT VulkanIntroducingPVRVk)

set(SRC_FILES VulkanIntroducingPVRVk.cpp)

set(ASSET_FOLDER ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets_VulkanIntroducingPVRVk)

# Adds an executable (or ndk library for Android) and necessary files like plists for Mac/iOS etc.
add_platform_specific_executable(VulkanIntroducingPVRVk ${SRC_FILES})

#################################### ASSET FILES ##########################################
# For platforms supporting it, will be packaged with the executable for runtime use.
# Will be accessible from the app with their "relative path". One call per base path

### Shaders that need to be compiled to SpirV (Vulkan) ###
# During build time, glslangvalidator will be called to create a "<shadername.extension>.spv" file
add_spirv_shaders_to_target(VulkanIntroducingPVRVk 
	SOURCE_GROUP "shaders_source" 
	SPIRV_SOURCE_GROUP "shaders_generated"
	ASSET_FOLDER ${ASSET_FOLDER} 
	BASE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/
	FILE_LIST
		VertShader.vsh
		FragShader.fsh)

# Create and adds a Windows resource file (Resources.rc) with all the assets that have been added to the target with the previous functions
add_assets_resource_file(VulkanIntroducingPVRVk)
###########################################################################################

# Apply SDK example specific compile and linker options
apply_example_compile_options_to_target(VulkanIntroducingPVRVk)

target_link_libraries(VulkanIntroducingPVRVk PUBLIC
	PVRShell
	PVRVk
)
if(APPLE AND NOT IOS)
	find_package(MoltenVK REQUIRED)
	if (${MOLTENVK_FOUND})
		list(APPEND PVRUtilsVk_PRIVATE_LINK_LIBS ${MVK_LIBRARIES})
		list(APPEND PVRUtilsVk_INCLUDE_DIRECTORIES ${MVK_INCLUDE_DIR})
	endif()
endif()