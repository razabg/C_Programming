#!/bin/bash

for i in 1 2 3
do
    echo "Hello from client $i" | nc -q 1 localhost 8080 &
done

wait
