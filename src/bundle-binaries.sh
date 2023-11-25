#!/bin/sh

. ./get-sysroot.sh

case "$host_os" in
  linux)
    shared_lib_name='libcronet.so'
    static_lib_name='libcronet_static.a'
  ;;
  win)
    shared_lib_name='cronet.dll.lib'
    dll_name='cronet.dll'
    static_lib_name='cronet_static.lib'
  ;;
  mac)
    shared_lib_name='libcronet.dylib'
    static_lib_name='libcronet_static.a'
  ;;
esac

set -ex

mkdir -p out/Release/cronet

if [ "$target_os" = 'android' ]; then
  WITH_SYSROOT='third_party/android_toolchain/ndk/toolchains/llvm/prebuilt/linux-x86_64/sysroot'
fi

cp -a out/Release/$shared_lib_name out/Release/cronet/
if [ "$host_os" = 'win' ]; then
  cp -a out/Release/$dll_name out/Release/cronet/
fi
cp -a out/Release/obj/components/cronet/$static_lib_name out/Release/cronet/
cp -a components/cronet/native/generated/cronet.idl_c.h out/Release/cronet/
cp -a components/cronet/native/include/cronet_c.h out/Release/cronet/
cp -a components/cronet/native/include/cronet_export.h out/Release/cronet/
cp -a components/grpc_support/include/bidirectional_stream_c.h out/Release/cronet/
if [ "$WITH_SYSROOT" ]; then
  cp -a "$PWD/$WITH_SYSROOT" out/Release/cronet/sysroot
fi
if [ "$target_os" = 'android' ]; then
  # Included by base/BUILD.gn
  cp -a base/android/library_loader/anchor_functions.lds out/Release/cronet
fi
