#!/bin/bash
command_exe="indent -br -l100 -i4 ";
echo $@;
echo "$# files";
echo "${command_exe} $@";
echo `${command_exe} $@`;
