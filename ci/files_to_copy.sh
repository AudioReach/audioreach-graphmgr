#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause-Clear
#
# Copyright (c) 2025 Qualcomm Innovation Center, Inc. All rights reserved.

# Move outside the github workspace to avoid conflicts
cd ..

sudo touch graphmger.txt
sudo cp -R touch graphmger.txt /tmp/rootfs/etc/
# copy the build artifacts to a temporary directory
sudo cp -R build/usr/* /tmp/rootfs/usr/
sudo cp -R build/etc/* /tmp/rootfs/etc/
