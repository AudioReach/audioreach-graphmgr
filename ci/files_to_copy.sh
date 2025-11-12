#!/bin/bash
# SPDX-License-Identifier: BSD-3-Clause-Clear
#
# Copyright (c) 2025 Qualcomm Innovation Center, Inc. All rights reserved.

# Move outside the github workspace to avoid conflicts
cd ..


# Create sample file in workspace (outside container)
touch SAMPLE_AUDIO_CLIP.txt
echo "it consists of sample audio clip" > SAMPLE_AUDIO_CLIP.txt
    
# copy the build artifacts to a temporary directory
cp -R build/usr/* /tmp/rootfs/usr/
cp -R build/etc/* /tmp/rootfs/etc/

# Now copy the file to the mounted rootfs
cp /workspace/SAMPLE_AUDIO_CLIP.txt /tmp/rootfs/
cat /tmp/rootfs/SAMPLE_AUDIO_CLIP.txt
