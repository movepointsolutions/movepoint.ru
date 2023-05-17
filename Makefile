# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anek/www

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anek/www

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/anek/www/CMakeFiles /home/anek/www//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/anek/www/CMakeFiles 0
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
# Target rules for targets named movepoint

# Build rule for target.
movepoint: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 movepoint
.PHONY : movepoint

# fast build rule for target.
movepoint/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/build
.PHONY : movepoint/fast

comment.o: comment.cpp.o

.PHONY : comment.o

# target to build an object file
comment.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/comment.cpp.o
.PHONY : comment.cpp.o

comment.i: comment.cpp.i

.PHONY : comment.i

# target to preprocess a source file
comment.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/comment.cpp.i
.PHONY : comment.cpp.i

comment.s: comment.cpp.s

.PHONY : comment.s

# target to generate assembly for a file
comment.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/comment.cpp.s
.PHONY : comment.cpp.s

comment_form.o: comment_form.cpp.o

.PHONY : comment_form.o

# target to build an object file
comment_form.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/comment_form.cpp.o
.PHONY : comment_form.cpp.o

comment_form.i: comment_form.cpp.i

.PHONY : comment_form.i

# target to preprocess a source file
comment_form.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/comment_form.cpp.i
.PHONY : comment_form.cpp.i

comment_form.s: comment_form.cpp.s

.PHONY : comment_form.s

# target to generate assembly for a file
comment_form.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/comment_form.cpp.s
.PHONY : comment_form.cpp.s

comments.o: comments.cpp.o

.PHONY : comments.o

# target to build an object file
comments.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/comments.cpp.o
.PHONY : comments.cpp.o

comments.i: comments.cpp.i

.PHONY : comments.i

# target to preprocess a source file
comments.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/comments.cpp.i
.PHONY : comments.cpp.i

comments.s: comments.cpp.s

.PHONY : comments.s

# target to generate assembly for a file
comments.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/comments.cpp.s
.PHONY : comments.cpp.s

engine.o: engine.cpp.o

.PHONY : engine.o

# target to build an object file
engine.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/engine.cpp.o
.PHONY : engine.cpp.o

engine.i: engine.cpp.i

.PHONY : engine.i

# target to preprocess a source file
engine.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/engine.cpp.i
.PHONY : engine.cpp.i

engine.s: engine.cpp.s

.PHONY : engine.s

# target to generate assembly for a file
engine.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/engine.cpp.s
.PHONY : engine.cpp.s

form_part.o: form_part.cpp.o

.PHONY : form_part.o

# target to build an object file
form_part.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/form_part.cpp.o
.PHONY : form_part.cpp.o

form_part.i: form_part.cpp.i

.PHONY : form_part.i

# target to preprocess a source file
form_part.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/form_part.cpp.i
.PHONY : form_part.cpp.i

form_part.s: form_part.cpp.s

.PHONY : form_part.s

# target to generate assembly for a file
form_part.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/form_part.cpp.s
.PHONY : form_part.cpp.s

handler.o: handler.cpp.o

.PHONY : handler.o

# target to build an object file
handler.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/handler.cpp.o
.PHONY : handler.cpp.o

handler.i: handler.cpp.i

.PHONY : handler.i

# target to preprocess a source file
handler.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/handler.cpp.i
.PHONY : handler.cpp.i

handler.s: handler.cpp.s

.PHONY : handler.s

# target to generate assembly for a file
handler.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/handler.cpp.s
.PHONY : handler.cpp.s

index.o: index.cpp.o

.PHONY : index.o

# target to build an object file
index.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/index.cpp.o
.PHONY : index.cpp.o

index.i: index.cpp.i

.PHONY : index.i

# target to preprocess a source file
index.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/index.cpp.i
.PHONY : index.cpp.i

index.s: index.cpp.s

.PHONY : index.s

# target to generate assembly for a file
index.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/index.cpp.s
.PHONY : index.cpp.s

login.o: login.cpp.o

.PHONY : login.o

# target to build an object file
login.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/login.cpp.o
.PHONY : login.cpp.o

login.i: login.cpp.i

.PHONY : login.i

# target to preprocess a source file
login.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/login.cpp.i
.PHONY : login.cpp.i

login.s: login.cpp.s

.PHONY : login.s

# target to generate assembly for a file
login.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/login.cpp.s
.PHONY : login.cpp.s

movepoint.o: movepoint.cpp.o

.PHONY : movepoint.o

# target to build an object file
movepoint.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/movepoint.cpp.o
.PHONY : movepoint.cpp.o

movepoint.i: movepoint.cpp.i

.PHONY : movepoint.i

# target to preprocess a source file
movepoint.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/movepoint.cpp.i
.PHONY : movepoint.cpp.i

movepoint.s: movepoint.cpp.s

.PHONY : movepoint.s

# target to generate assembly for a file
movepoint.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/movepoint.cpp.s
.PHONY : movepoint.cpp.s

redis.o: redis.cpp.o

.PHONY : redis.o

# target to build an object file
redis.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/redis.cpp.o
.PHONY : redis.cpp.o

redis.i: redis.cpp.i

.PHONY : redis.i

# target to preprocess a source file
redis.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/redis.cpp.i
.PHONY : redis.cpp.i

redis.s: redis.cpp.s

.PHONY : redis.s

# target to generate assembly for a file
redis.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/redis.cpp.s
.PHONY : redis.cpp.s

season.o: season.cpp.o

.PHONY : season.o

# target to build an object file
season.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/season.cpp.o
.PHONY : season.cpp.o

season.i: season.cpp.i

.PHONY : season.i

# target to preprocess a source file
season.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/season.cpp.i
.PHONY : season.cpp.i

season.s: season.cpp.s

.PHONY : season.s

# target to generate assembly for a file
season.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/season.cpp.s
.PHONY : season.cpp.s

session_manager.o: session_manager.cpp.o

.PHONY : session_manager.o

# target to build an object file
session_manager.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/session_manager.cpp.o
.PHONY : session_manager.cpp.o

session_manager.i: session_manager.cpp.i

.PHONY : session_manager.i

# target to preprocess a source file
session_manager.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/session_manager.cpp.i
.PHONY : session_manager.cpp.i

session_manager.s: session_manager.cpp.s

.PHONY : session_manager.s

# target to generate assembly for a file
session_manager.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/session_manager.cpp.s
.PHONY : session_manager.cpp.s

sha1/sha1.o: sha1/sha1.c.o

.PHONY : sha1/sha1.o

# target to build an object file
sha1/sha1.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/sha1/sha1.c.o
.PHONY : sha1/sha1.c.o

sha1/sha1.i: sha1/sha1.c.i

.PHONY : sha1/sha1.i

# target to preprocess a source file
sha1/sha1.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/sha1/sha1.c.i
.PHONY : sha1/sha1.c.i

sha1/sha1.s: sha1/sha1.c.s

.PHONY : sha1/sha1.s

# target to generate assembly for a file
sha1/sha1.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/sha1/sha1.c.s
.PHONY : sha1/sha1.c.s

snippet.o: snippet.cpp.o

.PHONY : snippet.o

# target to build an object file
snippet.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/snippet.cpp.o
.PHONY : snippet.cpp.o

snippet.i: snippet.cpp.i

.PHONY : snippet.i

# target to preprocess a source file
snippet.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/snippet.cpp.i
.PHONY : snippet.cpp.i

snippet.s: snippet.cpp.s

.PHONY : snippet.s

# target to generate assembly for a file
snippet.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/movepoint.dir/build.make CMakeFiles/movepoint.dir/snippet.cpp.s
.PHONY : snippet.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... movepoint"
	@echo "... comment.o"
	@echo "... comment.i"
	@echo "... comment.s"
	@echo "... comment_form.o"
	@echo "... comment_form.i"
	@echo "... comment_form.s"
	@echo "... comments.o"
	@echo "... comments.i"
	@echo "... comments.s"
	@echo "... engine.o"
	@echo "... engine.i"
	@echo "... engine.s"
	@echo "... form_part.o"
	@echo "... form_part.i"
	@echo "... form_part.s"
	@echo "... handler.o"
	@echo "... handler.i"
	@echo "... handler.s"
	@echo "... index.o"
	@echo "... index.i"
	@echo "... index.s"
	@echo "... login.o"
	@echo "... login.i"
	@echo "... login.s"
	@echo "... movepoint.o"
	@echo "... movepoint.i"
	@echo "... movepoint.s"
	@echo "... redis.o"
	@echo "... redis.i"
	@echo "... redis.s"
	@echo "... season.o"
	@echo "... season.i"
	@echo "... season.s"
	@echo "... session_manager.o"
	@echo "... session_manager.i"
	@echo "... session_manager.s"
	@echo "... sha1/sha1.o"
	@echo "... sha1/sha1.i"
	@echo "... sha1/sha1.s"
	@echo "... snippet.o"
	@echo "... snippet.i"
	@echo "... snippet.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

