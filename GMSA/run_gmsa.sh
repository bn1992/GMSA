#!/bin/bash
i=0
while [ $i -lt 5 ]; do
	./rungmsa ./data/300/x70/97/ &
	let i=i+1
done
wait
exit 0
