#!/bin/bash

GRAMMER_START_LINE=371
GRAMMER_END_LINE=1764

sed -i                                                                                  \
  -e "${GRAMMER_START_LINE},${GRAMMER_END_LINE}s/\(\/\*.*\*\/\)//g"                     \
  -e "${GRAMMER_START_LINE},${GRAMMER_END_LINE}s/\(\/\/.*\)$//g"                        \
  -e "${GRAMMER_START_LINE},${GRAMMER_END_LINE}s/\(\[.*;[ \t]*]\)/\{\/*&*\/\}/g"        \
  -e "${GRAMMER_START_LINE},${GRAMMER_END_LINE}s/\(\[\)$/\{\/*&/g"                      \
  -e "${GRAMMER_START_LINE},${GRAMMER_END_LINE}s/\(^[ \t]*\]\)/&*\/\}/g"                \
  parser.y

