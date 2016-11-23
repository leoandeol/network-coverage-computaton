#!/bin/bash
for i in `ls | grep -e .dot$`
do
	rm "$i.png" 2> /dev/null
	dot -Tpng $i > "$i.png"
done;
