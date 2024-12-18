# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/dmitrysorokin/VS Code/Casino-Project"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/dmitrysorokin/VS Code/Casino-Project"

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/opt/local/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/opt/local/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start "/Users/dmitrysorokin/VS Code/Casino-Project/CMakeFiles" "/Users/dmitrysorokin/VS Code/Casino-Project//CMakeFiles/progress.marks"
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start "/Users/dmitrysorokin/VS Code/Casino-Project/CMakeFiles" 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named MoneyPit

# Build rule for target.
MoneyPit: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 MoneyPit
.PHONY : MoneyPit

# fast build rule for target.
MoneyPit/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/build
.PHONY : MoneyPit/fast

src/bar.o: src/bar.cpp.o
.PHONY : src/bar.o

# target to build an object file
src/bar.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/bar.cpp.o
.PHONY : src/bar.cpp.o

src/bar.i: src/bar.cpp.i
.PHONY : src/bar.i

# target to preprocess a source file
src/bar.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/bar.cpp.i
.PHONY : src/bar.cpp.i

src/bar.s: src/bar.cpp.s
.PHONY : src/bar.s

# target to generate assembly for a file
src/bar.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/bar.cpp.s
.PHONY : src/bar.cpp.s

src/blackjack.o: src/blackjack.cpp.o
.PHONY : src/blackjack.o

# target to build an object file
src/blackjack.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/blackjack.cpp.o
.PHONY : src/blackjack.cpp.o

src/blackjack.i: src/blackjack.cpp.i
.PHONY : src/blackjack.i

# target to preprocess a source file
src/blackjack.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/blackjack.cpp.i
.PHONY : src/blackjack.cpp.i

src/blackjack.s: src/blackjack.cpp.s
.PHONY : src/blackjack.s

# target to generate assembly for a file
src/blackjack.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/blackjack.cpp.s
.PHONY : src/blackjack.cpp.s

src/card.o: src/card.cpp.o
.PHONY : src/card.o

# target to build an object file
src/card.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/card.cpp.o
.PHONY : src/card.cpp.o

src/card.i: src/card.cpp.i
.PHONY : src/card.i

# target to preprocess a source file
src/card.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/card.cpp.i
.PHONY : src/card.cpp.i

src/card.s: src/card.cpp.s
.PHONY : src/card.s

# target to generate assembly for a file
src/card.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/card.cpp.s
.PHONY : src/card.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/menumanager.o: src/menumanager.cpp.o
.PHONY : src/menumanager.o

# target to build an object file
src/menumanager.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/menumanager.cpp.o
.PHONY : src/menumanager.cpp.o

src/menumanager.i: src/menumanager.cpp.i
.PHONY : src/menumanager.i

# target to preprocess a source file
src/menumanager.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/menumanager.cpp.i
.PHONY : src/menumanager.cpp.i

src/menumanager.s: src/menumanager.cpp.s
.PHONY : src/menumanager.s

# target to generate assembly for a file
src/menumanager.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/menumanager.cpp.s
.PHONY : src/menumanager.cpp.s

src/player.o: src/player.cpp.o
.PHONY : src/player.o

# target to build an object file
src/player.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/player.cpp.o
.PHONY : src/player.cpp.o

src/player.i: src/player.cpp.i
.PHONY : src/player.i

# target to preprocess a source file
src/player.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/player.cpp.i
.PHONY : src/player.cpp.i

src/player.s: src/player.cpp.s
.PHONY : src/player.s

# target to generate assembly for a file
src/player.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/player.cpp.s
.PHONY : src/player.cpp.s

src/roulette.o: src/roulette.cpp.o
.PHONY : src/roulette.o

# target to build an object file
src/roulette.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/roulette.cpp.o
.PHONY : src/roulette.cpp.o

src/roulette.i: src/roulette.cpp.i
.PHONY : src/roulette.i

# target to preprocess a source file
src/roulette.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/roulette.cpp.i
.PHONY : src/roulette.cpp.i

src/roulette.s: src/roulette.cpp.s
.PHONY : src/roulette.s

# target to generate assembly for a file
src/roulette.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/roulette.cpp.s
.PHONY : src/roulette.cpp.s

src/runner.o: src/runner.cpp.o
.PHONY : src/runner.o

# target to build an object file
src/runner.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/runner.cpp.o
.PHONY : src/runner.cpp.o

src/runner.i: src/runner.cpp.i
.PHONY : src/runner.i

# target to preprocess a source file
src/runner.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/runner.cpp.i
.PHONY : src/runner.cpp.i

src/runner.s: src/runner.cpp.s
.PHONY : src/runner.s

# target to generate assembly for a file
src/runner.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/runner.cpp.s
.PHONY : src/runner.cpp.s

src/slots.o: src/slots.cpp.o
.PHONY : src/slots.o

# target to build an object file
src/slots.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/slots.cpp.o
.PHONY : src/slots.cpp.o

src/slots.i: src/slots.cpp.i
.PHONY : src/slots.i

# target to preprocess a source file
src/slots.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/slots.cpp.i
.PHONY : src/slots.cpp.i

src/slots.s: src/slots.cpp.s
.PHONY : src/slots.s

# target to generate assembly for a file
src/slots.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/slots.cpp.s
.PHONY : src/slots.cpp.s

src/visuals.o: src/visuals.cpp.o
.PHONY : src/visuals.o

# target to build an object file
src/visuals.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/visuals.cpp.o
.PHONY : src/visuals.cpp.o

src/visuals.i: src/visuals.cpp.i
.PHONY : src/visuals.i

# target to preprocess a source file
src/visuals.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/visuals.cpp.i
.PHONY : src/visuals.cpp.i

src/visuals.s: src/visuals.cpp.s
.PHONY : src/visuals.s

# target to generate assembly for a file
src/visuals.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MoneyPit.dir/build.make CMakeFiles/MoneyPit.dir/src/visuals.cpp.s
.PHONY : src/visuals.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... MoneyPit"
	@echo "... src/bar.o"
	@echo "... src/bar.i"
	@echo "... src/bar.s"
	@echo "... src/blackjack.o"
	@echo "... src/blackjack.i"
	@echo "... src/blackjack.s"
	@echo "... src/card.o"
	@echo "... src/card.i"
	@echo "... src/card.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/menumanager.o"
	@echo "... src/menumanager.i"
	@echo "... src/menumanager.s"
	@echo "... src/player.o"
	@echo "... src/player.i"
	@echo "... src/player.s"
	@echo "... src/roulette.o"
	@echo "... src/roulette.i"
	@echo "... src/roulette.s"
	@echo "... src/runner.o"
	@echo "... src/runner.i"
	@echo "... src/runner.s"
	@echo "... src/slots.o"
	@echo "... src/slots.i"
	@echo "... src/slots.s"
	@echo "... src/visuals.o"
	@echo "... src/visuals.i"
	@echo "... src/visuals.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
