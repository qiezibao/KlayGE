#!/usr/bin/env python
#-*- coding: ascii -*-

from __future__ import print_function
import os
import sys
import shutil
import glob

def copy_to_dst(src_name, dst_dir):
	print("Copy %s to %s" % (src_name, dst_dir))
	shutil.copy(src_name, dst_dir)

env = os.environ

if len(sys.argv) > 1:
	cfg = sys.argv[1]
else:
	if "VS100COMNTOOLS" in env:
		cfg = "vc10"
	elif "VS90COMNTOOLS" in env:
		cfg = "vc9"
	elif "VS80COMNTOOLS" in env:
		cfg = "vc8"
	elif os.path.exists("C:\MinGW\bin\gcc.exe"):
		cfg = "mingw"

if "vc10" == cfg:
	compiler_name = "vc"
	compiler_version = 10
	ide_name = "VS"
	ide_version = 2010
elif "vc9" == cfg:
	compiler_name = "vc"
	compiler_version = 9
	ide_name = "VS"
	ide_version = 2008
elif "vc8" == cfg:
	compiler_name = "vc"
	compiler_version = 8
	ide_name = "VS"
	ide_version = 2005
elif "mingw" == cfg:
	compiler_name = "gcc"
	compiler_version = 0
	ide_name = "mingw"
	ide_version = 0
else:
	print("Wrong configuration\n")
	sys.exit(1)

dst_dir_x86 = "KlayGE/bin/win_x86/"
dst_dir_x64 = "KlayGE/bin/win_x64/"


print("\nBuilding boost...\n")

if not os.path.exists("External/boost/bjam.exe"):
	os.system("External/boost/bootstrap.bat")

boost_define_str = "define=_CRT_SECURE_NO_DEPRECATE define=_SCL_SECURE_NO_DEPRECATE"
if ("vc" == compiler_name) and ((8 == compiler_version) or (9 == compiler_version)):
	boost_define_str += " define=_SECURE_SCL=0"
os.chdir("External/boost")
if "vc" == compiler_name:
	boost_toolset = "%s%d" % (compiler_name, compiler_version)
else:
	boost_toolset = "gcc"
os.system("build_%s.bat" % boost_toolset)
os.chdir("../../")

for fname in glob.iglob("External/boost/lib_%s_x86/lib/*.dll" % boost_toolset):
	copy_to_dst(fname, dst_dir_x86)
for fname in glob.iglob("External/boost/lib_%s_x64/lib/*.dll" % boost_toolset):
	copy_to_dst(fname, dst_dir_x64)


print("\nBuilding Python...\n")

os.chdir("External/Python/PCbuild")
os.system("build_%s%d_all.bat" % (compiler_name, compiler_version))
os.chdir("../../../")

copy_to_dst("External/Python/DLLs/python32.dll", dst_dir_x86)
copy_to_dst("External/Python/DLLs/python32_d.dll", dst_dir_x86)
copy_to_dst("External/Python/DLLs/amd64/python32.dll", dst_dir_x64)
copy_to_dst("External/Python/DLLs/amd64/python32_d.dll", dst_dir_x64)


print("\nBuilding libogg...\n")

os.chdir("External/libogg/win32/%s%d" % (ide_name, ide_version))
os.system("build_all.bat")
os.chdir("../../../../")


print("\nBuilding libvorbis...\n")

os.chdir("External/libvorbis/win32/%s%d" % (ide_name, ide_version))
os.system("build_all.bat")
os.chdir("../../../../")


print("\nBuilding freetype...\n")

os.chdir("External/freetype/builds/win32/vc%s" % ide_version)
os.system("build_all.bat")
os.chdir("../../../../../")


print("\nSeting up DXSDK...\n")

os.chdir("External/DXSDK/Redist")
os.system("dxwebsetup.exe")
os.chdir("../../../")


print("\nSeting up OpenAL SDK...\n")

os.chdir("External/OpenALSDK/redist")
os.system("oalinst.exe")
os.chdir("../../../")


print("\nSeting up Cg...\n")

copy_to_dst("External/Cg/bin/cg.dll", dst_dir_x86)
copy_to_dst("External/Cg/bin.x64/cg.dll", dst_dir_x64)
