#!/bin/bash
prefix=""
gcc -o enet csls-network-status.c
cp -r enet ${prefix}/bin
