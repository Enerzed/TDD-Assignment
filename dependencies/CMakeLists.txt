# OpenSSL
FetchContent_Declare(
	openssl-cmake
	GIT_REPOSITORY https://github.com/flagarde/openssl-cmake
	GIT_TAG 4f4ef7ab029c3e6696c4d749ca3d0f8a137a2f82 # 2.4
)
add_subdirectory(openssl-cmake)
