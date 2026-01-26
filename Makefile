# ---- Project settings ----
CXX      := g++
TARGET   := gameboi++

# One tree: src/ contains both .cpp and .hpp (nested ok)
SRC_DIR  := src
RES_DIR  := resources

BUILD_DIR:= build
OBJ_DIR  := $(BUILD_DIR)/objs
DEP_DIR  := $(BUILD_DIR)/deps
BIN      := $(BUILD_DIR)/$(TARGET)

# macOS .app bundle
APP_NAME := $(TARGET).app
APP_DIR  := $(BUILD_DIR)/$(APP_NAME)
MACOS_DIR:= $(APP_DIR)/Contents/MacOS
RSRC_DIR := $(APP_DIR)/Contents/Resources
PLIST    := $(APP_DIR)/Contents/Info.plist

# ---- Flags ----
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O2
CXXFLAGS += -I$(SRC_DIR)
# Generate deps into build/deps, while compiling objs into build/objs
CXXFLAGS += -MMD -MP -MF $(DEP_DIR)/$*.d
LDFLAGS  :=
LDLIBS   :=

# ---- Find nested sources ----
SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(patsubst $(SRC_DIR)/%.cpp,$(DEP_DIR)/%.d,$(SRCS))

# ---- Default ----
# Usage:
#    make		          -> builds the raw executable
#    make run             -> builds and runs the raw executable
#    make clean           -> removes build/
.PHONY: all
all: $(BIN)

.PHONY: run clean
run: $(BIN)
	./$(BIN) $(ARGS)

clean:
	rm -rf $(BUILD_DIR)

# Link (binary lives in build/)
$(BIN): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# Compile (mirror src/ subdirs into build/objs and build/deps)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@) $(DEP_DIR)/$(dir $*)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Include auto-generated dependency files
-include $(DEPS)
