#!/bin/bash

########################################################################################
## Comments out btyacc cnstructs so that bison/yacc can be used to generate grammer
## It is only meant for diagnostic purpose to improve the grammer
## and performance by reducing reduce/reduce conflicts
########################################################################################

GRAMMER_START_LINE=`grep -n '%%' parser.y | head -1 | cut -d":" -f1`
GRAMMER_END_LINE=`grep -n '%%' parser.y | tail -1 | cut -d":" -f1`

sed -i                                                                                                    \
  -e "${GRAMMER_START_LINE},${GRAMMER_END_LINE}s/\(\[[^'].*;[ \t]*]\)/\{\/*ToYacc & ToYacc*\/\}/g"        \
  -e "${GRAMMER_START_LINE},${GRAMMER_END_LINE}s/\(\[\)$/\{\/*ToYacc &/g"                                 \
  -e "${GRAMMER_START_LINE},${GRAMMER_END_LINE}s/\(^[ \t]*\]\)/& ToYacc\*\/\}/g"                          \
  parser.y

