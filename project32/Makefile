#----------for all----------------
WORK_DIR = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build
LIB_BUILD_DIR = $(BUILD_DIR)/lib
LIB_LOCAL_INSTALL_DIR = $(WORK_DIR)/lib

#configure.sh > will chenge this line LIB_GOLBAL_INSTALL_DIR
LIB_GOLBAL_INSTALL_DIR = /usr/local/lib
#confiure.sh  explain: set lib install dir,such as /usr/local/lib <
#-----------for lib---------------
C_LIB_INCLUDES = ${WORK_DIR}/include
#configure.sh > will chenge this line C_LIB_NAMES
C_LIB_NAMES = vtuzki
#configure.sh explain: set lib name, such as vtuzki->libvtuzki.a <
C_LIB_INSTALL_DIR = ${WORK_DIR}/lib
TEST_FILE_DIR = $(WORK_DIR)/test
TEST_BUILD_DIR = $(BUILD_DIR)/_test


#-----------for app---------------
APP_FILE_DIR = $(WORK_DIR)/app
APP_BUILD_DIR = $(BUILD_DIR)/_app
C_APP_INCLUDES = ${WORK_DIR}/include ${WORK_DIR}/app
C_APP_LIB = ${WORK_DIR}/lib

#configure.sh will chenge this line IS_C_APP_USE_LIB
#configure.sh explain: set app use lib or not, such as yes <
#configure.sh explain: set app use lib or not, such as yes <
IS_C_APP_USE_LIB = no
#configure.sh explain: set app use lib or not, such as yes or no <


#complier
include ./scripts/build.mk


#test
include ./scripts/test.mk