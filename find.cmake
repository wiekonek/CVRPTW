# Copyright 2014 <copyright holder> <email>
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 

# - Try to find 
# Once done this will define
#  _FOUND - System has 
#  _INCLUDE_DIRS - The  include directories
#  _LIBRARIES - The libraries needed to use 
#  _DEFINITIONS - Compiler switches required for using 

find_package(PkgConfig)
pkg_check_modules(PC_ QUIET )
set(_DEFINITIONS ${PC__CFLAGS_OTHER})

find_path(_INCLUDE_DIR 
          HINTS ${PC__INCLUDEDIR} ${PC__INCLUDE_DIRS}
          PATH_SUFFIXES  )

find_library(_LIBRARY NAMES 
             HINTS ${PC__LIBDIR} ${PC__LIBRARY_DIRS} )

set(_LIBRARIES ${_LIBRARY} )
set(_INCLUDE_DIRS ${_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set _FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(  DEFAULT_MSG
                                  _LIBRARY _INCLUDE_DIR)
mark_as_advanced(_INCLUDE_DIR _LIBRARY )
