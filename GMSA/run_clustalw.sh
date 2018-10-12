 #!/bin/bash
i=0
while [ $i -lt 5 ]; do
    ./runclustalw ./data/300/x100/97/ &
    let i=i+1
done
wait #// 等待执行完
exit 0
