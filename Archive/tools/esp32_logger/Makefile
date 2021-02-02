#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

CURRENT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

PROJECT_NAME := es32_logger

CPPFLAGS += -iquote $(CURRENT_DIR)/../../shared/

include $(IDF_PATH)/make/project.mk

