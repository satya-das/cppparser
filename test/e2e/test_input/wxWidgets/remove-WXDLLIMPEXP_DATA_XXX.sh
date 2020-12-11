#!/bin/bash

for i in `grep -lRIP 'extern WXDLLIMPEXP_DATA_'`
do
    sed -e 's/extern WXDLLIMPEXP_DATA_\([A-Z]*\)(\([^)]*\))/extern WXDLLIMPEXP_\1 \2/g' -i $i
done

