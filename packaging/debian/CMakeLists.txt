# Copyright (c) 2016, 2018, Oracle and/or its affiliates. All rights reserved. 
# 
# This program is free software; you can redistribute it and/or modify 
# it under the terms of the GNU General Public License, version 2.0, as 
# published by the Free Software Foundation. 
#
# This program is also distributed with certain software (including 
# but not limited to OpenSSL) that is licensed under separate terms, 
# as designated in a particular file or component or in included license 
# documentation. The authors of MySQL hereby grant you an 
# additional permission to link the program and your derivative works 
# with the separately licensed software that they have included with 
# MySQL. 
# 
# Without limiting anything contained in the foregoing, this file, 
# which is part of MySQL Connector/ODBC, is also subject to the 
# Universal FOSS Exception, version 1.0, a copy of which can be found at 
# http://oss.oracle.com/licenses/universal-foss-exception. 
# 
# This program is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
# See the GNU General Public License, version 2.0, for more details. 
# 
# You should have received a copy of the GNU General Public License 
# along with this program; if not, write to the Free Software Foundation, Inc., 
# 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA 

# This is a small CMake project to copy this directory to the top of
# the source, and at the same time do some modifications to these
# files

cmake_minimum_required(VERSION 2.8.12)
project(MySQL_Connector_ODBC_Deb_Init NONE)

# ----------------------------------------------------------------------
# Set some variables to replace
# Use the version variables from "version.cmake"
# ----------------------------------------------------------------------

include(../../version.cmake)

string(TIMESTAMP YEAR "%Y")
if(NOT YEAR)
  message(FATAL_ERROR "Could not determine what year it is")
endif()

set(PRODUCT   "MySQL Connector/ODBC ${CONNECTOR_BASE_VERSION}")

if(NOT DEBIAN_REVISION)
  set(DEBIAN_REVISION 1)
endif()

# Distinguish between community and non-community builds, with the
# default being a community build. This does not impact the feature
# set that will be compiled in; it's merely provided as a hint to
# custom packaging steps.
option(COMMUNITY_BUILD "Set to true if this is a community build" ON) 

if(NOT COMMUNITY_BUILD)
  set(PRODUCT_SUFFIX "-commercial")
  set(NOT_PRODUCT_SUFFIX "")
  set(VERSION "${CONNECTOR_VERSION}+commercial-${DEBIAN_REVISION}")
else()
  set(PRODUCT_SUFFIX "")
  set(NOT_PRODUCT_SUFFIX "-commercial")
  set(VERSION "${CONNECTOR_VERSION}-${DEBIAN_REVISION}")
endif()

# ----------------------------------------------------------------------
# Find out if Debian/Ubuntu, the codename, distribution and version
# ----------------------------------------------------------------------

execute_process(
  COMMAND lsb_release --short --id
  OUTPUT_VARIABLE lsb_id
  RESULT_VARIABLE lsb_result
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT lsb_result EQUAL 0)
  message(FATAL_ERROR "Can't run lsb_release")
endif()

string(TOLOWER "${lsb_id}" lsb_id)

if(NOT lsb_id STREQUAL "debian" AND NOT lsb_id STREQUAL "ubuntu")
  message(FATAL_ERROR "We can only handle Debian or Ubuntu Deb packaging")
endif()

execute_process(
  COMMAND lsb_release --short --release
  OUTPUT_VARIABLE lsb_release
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
  COMMAND lsb_release --short --codename
  OUTPUT_VARIABLE CODENAME
  OUTPUT_STRIP_TRAILING_WHITESPACE
)


if(lsb_id STREQUAL "debian")
  # For Debian we want just the major release number
  string(REGEX REPLACE "\\..*" "" lsb_release "${lsb_release}")
endif()

set(ID_RELEASE "${lsb_id}${lsb_release}")

message(STATUS "OS distribution : ${ID_RELEASE}")
message(STATUS "OS code name    : ${CODENAME}")

# ----------------------------------------------------------------------
# Copy this directory and 
# ----------------------------------------------------------------------

set(DEST_DIR ${CMAKE_SOURCE_DIR}/../../debian)

file(
  COPY ${CMAKE_SOURCE_DIR}/
  DESTINATION ${DEST_DIR}
  PATTERN "*.in"   EXCLUDE
  PATTERN "CMake*" EXCLUDE
)

set(in_files
  changelog
  control
  copyright
  rules
  mysql-connector-odbc-setup.install
  mysql-connector-odbc-test.install
  mysql-connector-odbc.install
)

foreach(_in_file ${in_files})
  string(REPLACE "odbc" "odbc${PRODUCT_SUFFIX}" _out_file "${_in_file}")
  configure_file(
    ${CMAKE_SOURCE_DIR}/${_in_file}.in
    ${DEST_DIR}/${_out_file}
    @ONLY
  )
endforeach()
