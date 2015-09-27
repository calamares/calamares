#!/bin/bash

cd "$WORKSPACE"
cppcheck --enable=all --inconclusive --xml --xml-version=2 src 2> cppcheck.xml