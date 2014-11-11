
cmake_minimum_required (VERSION 2.8.1)

PROJECT(imx6_ipu_csc)
SET(LICENSE "MIT")

include_directories(
	$ENV{SDKTARGETSYSROOT}/usr/src/kernel/include/uapi
	$ENV{SDKTARGETSYSROOT}/usr/src/kernel/include
	$ENV{SDKTARGETSYSROOT}/usr/include
)

link_directories(
	${LINK_DIRECTORIES}
)

add_executable(
	imx6_ipu_csc

	test.c
	ipu_csc.c
)

