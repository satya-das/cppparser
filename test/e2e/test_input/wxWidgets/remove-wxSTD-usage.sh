#!/bin/bash

for i in `grep -wlRIP wxSTD | grep -v 'platform\.h'`
do
    sed -e 's/wxSTD /std::/g' -i $i
done

