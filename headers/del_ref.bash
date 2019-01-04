#!/bin/bash

loc=$(pwd)/*.h
for file in $loc; do 


sed -ie 's/&//g' $file




done
