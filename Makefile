# ---- Project settings ----
CXX      := g++
TARGET   := gameboi++

# One tree: src/ contains both .cpp and .hpp (nested ok)
SRC_DIR  := src

BUILD_DIR:= build
OBJ_DIR  := $(BUILD_DIR)/objs
DEP_DIR  := $(BUILD_DIR)/deps
BIN      := $(BUILD_DIR)/$(TARGET)

# ---- SDL3 (as git submodule at external/SDL) ----
SDL_DIR       := external/SDL
SDL_BUILD_DIR := $(BUILD_DIR)/sdl3
SDL_CONFIG    := $(SDL_BUILD_DIR)/CMakeCache.txt
SDL_LIB       := $(SDL_BUILD_DIR)/libSDL3.0.dylib

# Override if desired:
#   make SDL_BUILD_TYPE=Debug
#   make SDL_ARCHS="arm64;x86_64"
SDL_BUILD_TYPE ?= Release
SDL_ARCHS      ?=
MACOSX_DEPLOYMENT_TARGET ?= 10.13

SDL_CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=$(SDL_BUILD_TYPE) \
                   -DSDL_SHARED=ON -DSDL_STATIC=OFF \
                   -DSDL_TEST_LIBRARY=OFF -DSDL_TESTS=OFF -DSDL_EXAMPLES=OFF \
                   -DCMAKE_OSX_DEPLOYMENT_TARGET=$(MACOSX_DEPLOYMENT_TARGET)

ifneq ($(strip $(SDL_ARCHS)),)
SDL_CMAKE_FLAGS += -DCMAKE_OSX_ARCHITECTURES=$(SDL_ARCHS)
endif

# ---- Flags ----
CXXFLAGS := -std=c++20 -Wall -Wextra -O2
CXXFLAGS += -I$(SRC_DIR)
CXXFLAGS += -I$(SDL_DIR)/include -I$(SDL_BUILD_DIR)/include

# Generate deps into build/deps, while compiling objs into build/objs
CXXFLAGS += -MMD -MP -MF $(DEP_DIR)/$*.d

# Ensure runtime can find libSDL3.dylib:
# We copy libSDL3.dylib next to build/<TARGET>, and use @executable_path
LDFLAGS  := -Wl,-rpath,@executable_path
LDLIBS   := $(SDL_LIB)

# ---- Find nested sources ----
SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(patsubst $(SRC_DIR)/%.cpp,$(DEP_DIR)/%.d,$(SRCS))

# ---- Default ----
# Usage:
#    make                    -> builds the executable
#    make run ARGS="..."     -> builds and runs it with args
#    make clean              -> removes everything non-SDL in build/ 
#    make clean-full	     -> removes build/
.PHONY: all
all: $(BIN)

.PHONY: run clean
run: $(BIN)
	./$(BIN) $(ARGS)

clean:
	rm -rf $(DEP_DIR)
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN)
	@echo
	@echo "(!) Keeping SDL files to avoid long recompilation. To remove everything, run make clean-full"
	@echo

clean-full:
	rm -rf $(BUILD_DIR)

# ---- Build SDL3 ----
$(SDL_CONFIG): | $(SDL_BUILD_DIR)
	cmake -S "$(SDL_DIR)" -B "$(SDL_BUILD_DIR)" $(SDL_CMAKE_FLAGS)

$(SDL_LIB): $(SDL_CONFIG)
	cmake --build "$(SDL_BUILD_DIR)" --config "$(SDL_BUILD_TYPE)"

$(SDL_BUILD_DIR):
	mkdir -p "$(SDL_BUILD_DIR)"

# ---- Link (binary lives in build/) ----
$(BIN): $(OBJS) $(SDL_LIB) | $(BUILD_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)
	@cp -f "$(SDL_LIB)" "$(BUILD_DIR)/"

# ---- Compile (mirror src/ subdirs into build/objs and build/deps) ----
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@) $(DEP_DIR)/$(dir $*)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Include auto-generated dependency files
-include $(DEPS)