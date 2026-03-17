cmake_minimum_required(VERSION 3.20)
project(BIG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# --- 1. MANUAL PATHS (M3 Mac) ---
set(HOMEBREW_PREFIX "/opt/homebrew")

include_directories(
    "${HOMEBREW_PREFIX}/include"
    src/Headers
)

link_directories(
    "${HOMEBREW_PREFIX}/lib"
)

# --- 2. FIND PACKAGES ---
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

# --- 3. SOURCE FILES ---
add_executable(BIG 
    src/Cpp/main.cpp 
    src/Cpp/Link.cpp
)

# --- 4. LINK LIBRARIES ---
target_link_libraries(BIG
    PRIVATE
    OpenSSL::SSL 
    OpenSSL::Crypto
    Threads::Threads
    # REMOVED: boost_system (It is header-only, no linking needed)
)