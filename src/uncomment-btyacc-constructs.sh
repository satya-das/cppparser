#!/bin/bash

GRAMMER_START_LINE=371
GRAMMER_END_LINE=1764

sed -i                                                                   \
  -e "${GRAMMER_START_LINE},${GRAMMER_END_LINE}s/{\/\*ToYacc //g"        \
  -e "${GRAMMER_START_LINE},${GRAMMER_END_LINE}s/ ToYacc\*\/\}//g"       \
  parser.y

