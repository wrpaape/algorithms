.PHONY: all clean

ROOT_DIR = ..
SRC_DIR  = $(addprefix $(ROOT_DIR)/, src)
OBJ_DIR  = $(addprefix $(ROOT_DIR)/, obj)
BIN_DIR  = $(addprefix $(ROOT_DIR)/, bin)
TEST_DIR = $(addprefix $(ROOT_DIR)/, tests)

LIB_NAMES = utils
LIB_FLAGS = $(addprefix -l, $(LIB_NAMES))

CC	= gcc
CFLAGS	= -g -I$(SRC_DIR) -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__

# Google Test config
# for 'GTEST_DIR' environment variable
SHELL := /bin/zsh
# Flags passed to the preprocessor.
CPPFLAGS += -isystem $(GTEST_DIR)/include
# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread
# All Google Test headers.
GTEST_HDRS = $(GTEST_DIR)/include/gtest/*.h \
	     $(GTEST_DIR)/include/gtest/internal/*.h
# All Google Test source files.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HDRS)
# Flags for building Google Test object files.
GTEST_OBJ_FLAGS = -I$(GTEST_DIR)
# Flags for building user test object files.
TEST_OBJ_FLAGS  = -I$(SRC_DIR)
# Flags for building user test binary files.
TEST_BIN_FLAGS  = $(TEST_OBJ_FLAGS) -lpthread


# root/bin/demo
DEMO_NAME = demo
DEMO_SRC  = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(DEMO_NAME)))
DEMO_OBJ  = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(DEMO_NAME)))
DEMO_BIN  = $(addprefix $(BIN_DIR)/, $(DEMO_NAME))
DEMO_ODEP = $(DEMO_SRC) $(SFTR_HDR)
DEMO_BDEP = $(DEMO_OBJ) $(SFTR_OBJ)

# root/obj/suffix_tree.o
SFTR_NAME = suffix_tree
SFTR_SRC  = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SFTR_NAME)))
SFTR_HDR  = $(addprefix $(SRC_DIR)/, $(addsuffix .h, $(SFTR_NAME)))
SFTR_OBJ  = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SFTR_NAME)))
SFTR_ODEP = $(SFTR_SRC) $(SFTR_HDR)

# root/tests/suffix_tree_test
SFTR_TEST_NAME = $(addsuffix _test, $(SFTR_NAME))
SFTR_TEST_SRC  = $(addprefix $(TEST_DIR)/, $(addsuffix .cc, $(SFTR_TEST_NAME)))
SFTR_TEST_OBJ  = $(addprefix $(OBJ_DIR)/,  $(addsuffix .o,  $(SFTR_TEST_NAME)))
SFTR_TEST_BIN  = $(addprefix $(TEST_DIR)/, $(SFTR_TEST_NAME))
SFTR_TEST_ODEP = $(SFTR_TEST_SRC) $(SFTR_ODEP) $(GTEST_HDRS)
SFTR_TEST_BDEP = $(SFTR_TEST_OBJ) $(GTEST_MAIN_LIB)

# root/obj/gtest-all.a
GTEST_ALL_NAME = gtest-all
# GTEST_ALL_SRC  = $(addprefix $(GTEST_DIR)/src/, $(addsuffix .cc, $(GTEST_ALL_NAME)))
GTEST_ALL_OBJ  = $(addprefix $(OBJ_DIR)/,       $(addsuffix .o,  $(GTEST_ALL_NAME)))
GTEST_ALL_LIB  = $(addprefix $(OBJ_DIR)/,       $(addsuffix .a,  $(GTEST_ALL_NAME)))
# GTEST_ALL_ODEP = $(GTEST_ALL_SRC) $(GTEST_SRCS_)
GTEST_ALL_ODEP = $(GTEST_SRCS_)
GTEST_ALL_LDEP = $(GTEST_ALL_OBJ)

# root/obj/gtest_main.a
GTEST_MAIN_NAME = gtest_main
# GTEST_MAIN_SRC  = $(addprefix $(GTEST_DIR)/src/, $(addsuffix .cc, $(GTEST_MAIN_NAME)))
GTEST_MAIN_OBJ  = $(addprefix $(OBJ_DIR)/,       $(addsuffix .o,  $(GTEST_MAIN_NAME)))
GTEST_MAIN_LIB  = $(addprefix $(OBJ_DIR)/,       $(addsuffix .a,  $(GTEST_MAIN_NAME)))
# GTEST_MAIN_ODEP = $(GTEST_MAIN_SRC) $(GTEST_SRCS_)
GTEST_MAIN_ODEP = $(GTEST_SRCS_)
GTEST_MAIN_LDEP = $(GTEST_MAIN_OBJ)

# convenience groupings
ALL_BINS  = $(DEMO_BIN) $(SFTR_TEST_BIN)
ALL_LIBS  = $(GTEST_ALL_LIB) $(GTEST_MAIN_LIB)
ALL_OBJS  = $(SFTR_OBJ) $(SFTR_TEST_OBJ) $(GTEST_ALL_OBJ) $(GTEST_MAIN_OBJ)
ALL_TRGTS = $(ALL_BINS) $(ALL_LIBS) $(ALL_OBJS)

# make targets
all: $(ALL_TRGTS)

$(DEMO_BIN): $(DEMO_BDEP)
	$(CC) $(CFLAGS) $(LIB_FLAGS) -o $@ $^

$(DEMO_OBJ): $(DEMO_ODEP)
	$(CC) $(CFLAGS) -c -o $@ $<

$(SFTR_OBJ): $(SFTR_ODEP)
	$(CC) $(CFLAGS) -c -o $@ $<

$(SFTR_TEST_BIN): $(SFTR_TEST_BDEP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(TEST_BIN_FLAGS) -o $@ $^

$(SFTR_TEST_OBJ): $(SFTR_TEST_ODEP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(TEST_OBJ_FLAGS) -c -o $@ $<

$(GTEST_ALL_LIB): $(GTEST_ALL_LDEP)
	$(AR) $(ARFLAGS) $@ $^

$(GTEST_ALL_OBJ): $(GTEST_ALL_ODEP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(GTEST_OBJ_FLAGS) -c -o $@ $<

$(GTEST_MAIN_LIB): $(GTEST_MAIN_LDEP)
	$(AR) $(ARFLAGS) $@ $^

$(GTEST_MAIN_OBJ): $(GTEST_MAIN_ODEP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(GTEST_OBJ_FLAGS) -c -o $@ $<

clean:
	$(RM) $(ALL_TRGTS)
