#!/bin/bash
gcc csls-network-status.c
./a.out -n | sed '/lo/d'
rm -rf a.out
