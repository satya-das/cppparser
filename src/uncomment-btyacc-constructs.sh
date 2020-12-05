#!/bin/bash

GRAMMER_START_LINE=`grep -n '%%' parser.y | head -1 | cut -d":" -f1`
GRAMMER_END_LINE=`grep -n '%%' parser.y | tail -1 | cut -d":" -f1`

sed -i                                                                   \
  -e "${GRAMMER_START_LINE},${GRAMMER_END_LINE}s/{\/\*ToYacc //g"        \
  -e "${GRAMMER_START_LINE},${GRAMMER_END_LINE}s/ ToYacc\*\/\}//g"       \
  parser.y

