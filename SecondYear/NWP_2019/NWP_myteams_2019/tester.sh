#/bin/sh

for i in {1..10}
do
    nc 0 $1 &
done

#'killall nc' to kill every instances of nc