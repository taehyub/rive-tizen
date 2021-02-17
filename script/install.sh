#!/bin/sh

cd "submodule"

patch -p1 < ../script/tizen_build.diff

