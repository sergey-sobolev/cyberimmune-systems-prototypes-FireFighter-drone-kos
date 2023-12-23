project (einit)

# Tools for working with KasperskyOS images.
include (platform/image)

find_package(kss REQUIRED)

find_package(vfs REQUIRED)
include_directories (${vfs_INCLUDE})

find_package (precompiled_vfs REQUIRED)
include_directories (${precompiled_vfs_INCLUDE})

# dhcp implementation
find_package (rump REQUIRED COMPONENTS DHCPCD_ENTITY)
include_directories (${rump_INCLUDE})

add_executable (KlogEntityHw "src/klog_entity.c")
target_link_libraries (KlogEntityHw ${klog_SYSTEM_AUDIT_LIB})
add_dependencies (KlogEntityHw klog_edl_files)

add_executable (KlogEntityQemu "src/klog_entity.c")
target_link_libraries (KlogEntityQemu ${klog_SYSTEM_AUDIT_LIB})
add_dependencies (KlogEntityQemu klog_edl_files)

# Set compiler flags.
project_header_default ("STANDARD_GNU_11:YES" "STRICT_WARNINGS:NO")

if ("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "aarch64")
     set (SECURITY_PSL_FILE "src/security.psl")
else ()
     message (FATAL_ERROR "${CMAKE_SYSTEM_PROCESSOR} architecture is not supported." )
endif ()

if (ROOTFS_SDCARD)
    set (ROOTFS_ENTITY "kl.VfsSdCardFs")
    set (FS_BACKEND ${precompiled_vfsVfsSdCardFs})
    set (FS_IMAGE sdcard0.img)
    set (FS_IMG_FORMAT fat32)
    set (FS_IMG_SIZE 64)
    set (QEMU_FLAGS "-drive file=${FS_IMAGE},if=sd,format=raw")
else()
    set (ROOTFS_ENTITY "kl.VfsRamFs")
    set (FS_BACKEND ${precompiled_vfsVfsRamFs})
    set (FS_IMAGE ramdisk0.img)
    set (FS_IMG_FORMAT ext4)
    set (FS_IMG_SIZE 2)
    list (APPEND FILES ${CMAKE_BINARY_DIR}/einit/${FS_IMAGE})
endif()

# Define an ENTITIES variable with a list of programs.
    set (ENTITIES Aggregation
                  CCU
                  Communication
                  EAIC
                  Extinguishing
                  FMAC
                  Movement
                  Navigation
                  Situation
                  KlogStorageEntity
                  ${precompiled_vfsVfsNet}
                  ${rump_DHCPCD_ENTITY})
    set (CONNECTIONS_CFG_FILE "src/init.yaml.in")
list (APPEND ENTITIES ${FS_BACKEND})

set_target_properties(${FS_BACKEND} PROPERTIES
    EXTRA_ARGS "\
    - -l
    - devfs /dev devfs 0")

set (EXTRA_CONNECTIONS "\
  - target: kl.VfsNet
    id: kl.VfsNet
  - target: ${ROOTFS_ENTITY}
    id: ${ROOTFS_ENTITY}")
    
set_target_properties (${rump_DHCPCD_ENTITY} PROPERTIES
    DEPENDS_ON_ENTITY ""
    EXTRA_CONNECTIONS ${EXTRA_CONNECTIONS}
    EXTRA_ENV "\
    VFS_FILESYSTEM_BACKEND: client{fs->net}:${ROOTFS_ENTITY}
    VFS_NETWORK_BACKEND: client:kl.VfsNet"
    EXTRA_ARGS "\
    - '-4'
    - -f
    - /etc/dhcpcd.conf")

# Add a target to create disk image.
add_custom_target (${FS_IMAGE}
    COMMAND  ${KL_SDK_ROOT_PATH}/common/prepare_hdd_img.sh
        -d   ${CMAKE_SOURCE_DIR}/resources/hdd
        -s   ${FS_IMG_SIZE}
        -f   ${FS_IMG_FORMAT}
        -img ${FS_IMAGE})

set (INIT_KlogEntity_PATH "KlogEntityHw")
# KasperskyOS image for the target hardware platform.
build_kos_hw_image (kos-image
                    EINIT_ENTITY EinitHw
                    CONNECTIONS_CFG ${CONNECTIONS_CFG_FILE}
                    SECURITY_PSL ${SECURITY_PSL_FILE}
                    KLOG_ENTITY KlogEntityHw
                    IMAGE_FILES ${ENTITIES}
                                ${FILES})

if (NOT ROOTFS_SDCARD)
    add_dependencies (kos-image ${FS_IMAGE})
endif ()
target_link_libraries (KlogEntityHw kssaudit)

set (INIT_KlogEntity_PATH "KlogEntityQemu")
# KasperskyOS image for QEMU with simulation targets (sim, gdbsim, gdb).
build_kos_qemu_image (kos-qemu-image
                      EINIT_ENTITY EinitQemu
                      CONNECTIONS_CFG ${CONNECTIONS_CFG_FILE}
                      SECURITY_PSL ${SECURITY_PSL_FILE}
                      KLOG_ENTITY KlogEntityQemu
                      QEMU_FLAGS "${QEMU_FLAGS}"
                      QEMU_USER_NETWORK_FLAGS "hostfwd=tcp::1106-:1106"
                      IMAGE_FILES ${ENTITIES}
                                  ${FILES})

add_dependencies (kos-qemu-image ${FS_IMAGE})
target_link_libraries (KlogEntityQemu kssaudit)
set_target_properties (EinitHw PROPERTIES LINK_FLAGS ${VULN_LDFLAGS})
set_target_properties (EinitQemu PROPERTIES LINK_FLAGS ${VULN_LDFLAGS})
