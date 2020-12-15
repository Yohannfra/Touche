PROJECT_NAME := wsff-client

CLIENT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

# Fixme for LTS but ok for now
CPPFLAGS += -iquote $(CLIENT_DIR)/../shared/  \
			-iquote $(CLIENT_DIR)/include

include $(IDF_PATH)/make/project.mk
