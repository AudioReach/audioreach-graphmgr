#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause-Clear
#
# Copyright (c) 2025 Qualcomm Innovation Center, Inc. All rights reserved.

# Move outside the github workspace to avoid conflicts
cd ..

# copy the build artifacts to a temporary directory
sudo cp -R build/usr/* /tmp/rootfs/usr/
sudo cp -R build/etc/* /tmp/rootfs/etc/
sudo touch Sample_files.txt
#echo testing... > Sample_files.txt
sudo cp -R Sample_files.txt /tmp/rootfs/etc/
