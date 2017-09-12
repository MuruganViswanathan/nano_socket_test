#   Copyright 2016 Comcast Cable Communications Management, LLC
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

set(PROJ_SERVER server)
set(PROJ_CLIENT client)

set(SERVER test_server.c)
set(CLIENT  test_client.c)

add_executable(test_server ${SERVER})
add_executable(test_client ${CLIENT})

target_link_libraries (test_server
    ${CMAKE_THREAD_LIBS_INIT}
    -lm
    -lnanomsg
    -lrt
    )
#?? install (TARGETS seshat DESTINATION bin)

target_link_libraries (test_client
    ${CMAKE_THREAD_LIBS_INIT}
    -lm
    -lnanomsg
    -lrt
    )
