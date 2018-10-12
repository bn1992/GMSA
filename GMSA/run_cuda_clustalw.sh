#!/bin/bash
i=0
while [ $i -lt 5 ]; do
    ./runcuda_clustalw ./data/300/x90/97/ wait &
    let i=i+1
done
wait #// 等待执行完成 即可
exit 0
