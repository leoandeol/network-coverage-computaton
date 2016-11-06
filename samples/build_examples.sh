#!/bin/bash
for file in `ls *.dot`; do
dot -Tpng $file -o "$file.png";
done;
