aux_source_directory(${KIWI_SOURCE_PATH}/kmodule/kmemory KIWI_MODULE_SOURCE)
aux_source_directory(${KIWI_SOURCE_PATH}/kmodule/kthread KIWI_MODULE_SOURCE)
aux_source_directory(${KIWI_SOURCE_PATH}/kmodule/kcompon KIWI_MODULE_SOURCE)
aux_source_directory(${KIWI_SOURCE_PATH}/kmodule/klog KIWI_MODULE_SOURCE)

include_directories(${KIWI_SOURCE_PATH}/kmodule/kmemory)
include_directories(${KIWI_SOURCE_PATH}/kmodule/kthread)
include_directories(${KIWI_SOURCE_PATH}/kmodule/klog)
include_directories(${KIWI_SOURCE_PATH}/kbase)

add_library(kmodule ${KIWI_MODULE_SOURCE})