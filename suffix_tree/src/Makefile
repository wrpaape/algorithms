.PHONY: all clean

ROOT_DIR  = ..
SRC_DIR   = $(addprefix $(ROOT_DIR)/, src)
OBJ_DIR   = $(addprefix $(ROOT_DIR)/, obj)
BIN_DIR   = $(addprefix $(ROOT_DIR)/, bin)
TESTS_DIR = $(addprefix $(ROOT_DIR)/, tests)

LIB_NAMES = utils
LIB_FLAGS = $(addprefix -l, $(LIB_NAMES))

CC	= gcc
CFLAGS	= -g -I$(SRC_DIR) -std=c99 -Wall -D__USE_FIXED_PROTOTYPES__


STREE_NAME = suffix_tree
STREE_SRC  = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(STREE_NAME)))
STREE_HDR  = $(addprefix $(SRC_DIR)/, $(addsuffix .h, $(STREE_NAME)))
STREE_OBJ  = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(STREE_NAME)))
STREE_BIN  = $(addprefix $(BIN_DIR)/, $(STREE_NAME))
STREE_ODEP = $(STREE_SRC) $(STREE_HDR)
STREE_BDEP = $(STREE_OBJ)


ALL_BINS  = $(STREE_BIN)
ALL_OBJS  = $(STREE_OBJ)
ALL_TRGTS = $(ALL_BINS) $(ALL_OBJS)

SRC_TMPS  = $(addprefix $(SRC_DIR)/,   *~)
TEST_TMPS = $(addprefix $(TESTS_DIR)/, *~)
ROOT_TMPS = $(addprefix $(ROOT_DIR)/,  *~)
ALL_TMPS  = $(SRC_TMPS) $(TEST_TMPS) $(ROOT_TMPS)


all: $(ALL_TRGTS)

$(STREE_BIN): $(STREE_BDEP)
	$(CC) $(CFLAGS) $(LIB_FLAGS) -o $@ $^

$(STREE_OBJ): $(STREE_ODEP)
	$(CC) $(CFLAGS) $(LIB_FLAGS) -c -o $@ $<

clean:
	$(RM) $(ALL_TRGTS) $(ALL_TMPS)
