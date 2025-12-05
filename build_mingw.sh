#!/bin/bash

# Copyright (c) 2025 Alex313031.

export HERE=${PWD}

make clean && make all -j 4 $@
