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

# ---- SDL3_ttf (as git submodule at external/SDL_ttf) ----
TTF_DIR       := external/SDL_ttf
TTF_BUILD_DIR := $(BUILD_DIR)/sdl3_ttf
TTF_CONFIG    := $(TTF_BUILD_DIR)/CMakeCache.txt

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

# SDL_ttf CMake:
# - SDLTTF_VENDORED=ON uses the vendored deps mechanism
# - Point SDL3_DIR at the SDL build dir so SDL_ttf can find SDL3Config.cmake (no system install needed).
TTF_CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=$(SDL_BUILD_TYPE) \
                   -DSDLTTF_VENDORED=ON \
                   -DSDL3_DIR="$(shell pwd)/$(SDL_BUILD_DIR)" \
                   -DCMAKE_OSX_DEPLOYMENT_TARGET=$(MACOSX_DEPLOYMENT_TARGET)

ifneq ($(strip $(SDL_ARCHS)),)
TTF_CMAKE_FLAGS += -DCMAKE_OSX_ARCHITECTURES=$(SDL_ARCHS)
endif

# ---- Flags ----
CXXFLAGS := -std=c++20 -Wall -Wextra -O2
CXXFLAGS += -I$(SRC_DIR)
CXXFLAGS += -I$(SDL_DIR)/include -I$(SDL_BUILD_DIR)/include
CXXFLAGS += -I$(TTF_DIR)/include -I$(TTF_BUILD_DIR)/include

DEPFLAGS = -MMD -MP -MF $(DEP_DIR)/$*.d -MT $@

# Generate deps into build/deps, while compiling objs into build/objs
CXXFLAGS += -MMD -MP -MF $(DEP_DIR)/$*.d

# ---- Link against SDL dylibs in their build dirs (no filename probing) ----
SDL_LIBDIR := $(SDL_BUILD_DIR)
TTF_LIBDIR := $(TTF_BUILD_DIR)

# Runtime search paths so dyld can load them (relative to build/ executable location).
LDFLAGS += -Wl,-rpath,@executable_path/sdl3
LDFLAGS += -Wl,-rpath,@executable_path/sdl3_ttf

# Linker search paths + libs
LDFLAGS += -L$(SDL_LIBDIR) -L$(TTF_LIBDIR)
LDLIBS  := -lSDL3 -lSDL3_ttf


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

# ---- SDL3 and SDL3_ttf stamp files ----
SDL_BUILT := $(SDL_BUILD_DIR)/.built
TTF_BUILT := $(TTF_BUILD_DIR)/.built

# ---- Build SDL3 ----
$(SDL_CONFIG): | $(SDL_BUILD_DIR)
	cmake -S "$(SDL_DIR)" -B "$(SDL_BUILD_DIR)" $(SDL_CMAKE_FLAGS)

$(SDL_BUILT): $(SDL_CONFIG)
	cmake --build "$(SDL_BUILD_DIR)" --config "$(SDL_BUILD_TYPE)"
	@touch $@

$(SDL_BUILD_DIR):
	mkdir -p "$(SDL_BUILD_DIR)"

# ---- Build SDL3_ttf ----
$(TTF_CONFIG): $(SDL_LIB) | $(TTF_BUILD_DIR)
	cmake -S "$(TTF_DIR)" -B "$(TTF_BUILD_DIR)" $(TTF_CMAKE_FLAGS)

$(TTF_BUILT): $(TTF_CONFIG)
	cmake --build "$(TTF_BUILD_DIR)" --config "$(SDL_BUILD_TYPE)"
	@touch $@

$(TTF_BUILD_DIR):
	mkdir -p "$(TTF_BUILD_DIR)"

# ---- Link (binary lives in build/) ----
$(BIN): $(OBJS) $(SDL_BUILT) $(TTF_BUILT) | $(BUILD_DIR)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

# ---- Compile (mirror src/ subdirs into build/objs and build/deps) ----
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@) $(DEP_DIR)/$(dir $*)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Include auto-generated dependency files
-include $(DEPS)