#!/bin/bash
i=0
while [ $i -lt 5 ]; do
        ./rungmsa_cpu ./data/300/x100/97/ &
        let i=i+1
done
wait
exit 0
