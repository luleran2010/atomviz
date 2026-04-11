vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO mosra/magnum-integration
    REF 26a3af2d376b58ba82a0ab8314006d40d630ee73
    SHA512 faa14a8c318eba9d91d15bd37545a0447be0817df2676847bdf8f13823fed56ba0968b3875d14e894bd198ae903a8ce675e166135aac298ea88dd9769c50d1e7
    HEAD_REF master
)

string(COMPARE EQUAL "${VCPKG_LIBRARY_LINKAGE}" "static" BUILD_STATIC)

vcpkg_check_features(
    OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    FEATURES
        bullet WITH_BULLET
        eigen  WITH_EIGEN
        glm    WITH_GLM
        imgui  WITH_IMGUI
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        ${FEATURE_OPTIONS}
        -DBUILD_STATIC=${BUILD_STATIC}
        -DMAGNUM_PLUGINS_DEBUG_DIR=${CURRENT_INSTALLED_DIR}/debug/bin/magnum-d
        -DMAGNUM_PLUGINS_RELEASE_DIR=${CURRENT_INSTALLED_DIR}/bin/magnum
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(PACKAGE_NAME MagnumIntegration CONFIG_PATH share/cmake/MagnumIntegration)

# Debug includes and share are the same as release
file(REMOVE_RECURSE
    "${CURRENT_PACKAGES_DIR}/debug/include"
    "${CURRENT_PACKAGES_DIR}/debug/share"
)

# Clean up empty directories
if("${FEATURES}" STREQUAL "core")
    file(REMOVE_RECURSE
        "${CURRENT_PACKAGES_DIR}/bin"
        "${CURRENT_PACKAGES_DIR}/lib"
        "${CURRENT_PACKAGES_DIR}/debug"
    )
    set(VCPKG_POLICY_EMPTY_INCLUDE_FOLDER enabled)
else()
    file(GLOB FILES "${CURRENT_PACKAGES_DIR}/debug/*")
    list(LENGTH FILES COUNT)
    if(COUNT EQUAL 0)
        file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug")
    endif()
endif()

if(VCPKG_LIBRARY_LINKAGE STREQUAL static)
   file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/bin")
   file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/bin")
endif()

# Handle copyright
file(INSTALL "${SOURCE_PATH}/COPYING"
    DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
    RENAME copyright)

vcpkg_copy_pdbs()
