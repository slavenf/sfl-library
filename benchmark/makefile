#
# This is GNU makefile for Linux OS and GCC/Clang compiler
#

# C++ compiler
CXX = g++ -std=c++20

# C++ compiler flags
CXXFLAGS = -Wall -Wextra -Wfatal-errors -I ../include -I include -DNDEBUG -O3

# Function: Resursive wildcard
# Usage: $(call rwildcard,dir,pattern)
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# Source directory
SRC_DIR := ./src

# List of all source files that must be compiled and tested
SRCS := $(call rwildcard,$(SRC_DIR),*.cpp)

# Build directory
BUILD_DIR := ./build

# First rule
.PHONY: all
all:

# This function generates build rule for given source file.
# Usage: $(call generate_rules,source_file)
define generate_rules

.PHONY: $(basename $(notdir $(1)))
all:  $(basename $(notdir $(1)))
$(basename $(notdir $(1))):
	mkdir -p $(dir $(BUILD_DIR)/$(basename $(1)).out)
	$(CXX) $(CXXFLAGS) $(1) -o $(BUILD_DIR)/$(basename $(1)).out

endef

# Generate rules for all source files
$(foreach file,$(SRCS),$(eval $(call generate_rules,$(file))))

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
