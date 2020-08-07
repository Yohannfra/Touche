PROJECT_NAME := wsff-server

SERVER_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

# Fixme for LTS but ok for now
CPPFLAGS += -iquote $(SERVER_DIR)/../shared/ \
			-iquote $(SERVER_DIR)/include

include $(IDF_PATH)/make/project.mk
