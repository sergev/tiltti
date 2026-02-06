# Build MOO parser (C++17, zlib for gzip)
CXX      ?= c++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic
LDFLAGS  ?= -lz
RELEASE_FLAGS = -O2 -DNDEBUG
DEBUG_FLAGS   = -O0 -g3

BUILD_DIR = build
SRCS      = main.cpp moo_parser.cpp test_case.cpp print.cpp emit_gtest.cpp
OBJS      = $(addprefix $(BUILD_DIR)/, main.o moo_parser.o test_case.o print.o emit_gtest.o)
DEP       = $(OBJS:.o=.d)
TARGET    = moo-booth
TARGET_DBG = moo-booth-dbg

# Default: release build
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(RELEASE_FLAGS) -MMD -MP -c -o $@ $<

-include $(DEP)

.PHONY: all debug clean run

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET_DBG)

$(TARGET_DBG): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TARGET_DBG) $(TARGET_DBG).dSYM

run: $(TARGET)
	./$(TARGET) $(ARGS)
