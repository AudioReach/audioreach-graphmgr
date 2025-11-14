#!/bin/bash
# set -x
# SPDX-License-Identifier: BSD-3-Clause-Clear
#
# Copyright (c) 2025 Qualcomm Innovation Center, Inc. All rights reserved.

# Move outside the github workspace to avoid conflicts
cd ..

# copy the build artifacts to a temporary directory
cp -R build/usr/* /tmp/rootfs/usr/
cp -R build/etc/* /tmp/rootfs/etc/
touch yample.txt
echo "Sample sound clip" > Sample.txt
sudo cp Yample.txt /tmp/rootfs/etc/
cat Yample.txt
