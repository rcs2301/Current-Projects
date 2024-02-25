#!/usr/bin/bash


cd /workspaces/93345806

echo "Ignore the 'no such file or directory' messages!"

for dir in *;
do
    chmod u+rwx $dir
    if [ $dir != "z_compsci" ]; then
        cd /workspaces/93345806/$dir
        for f in *;
        do
            if [ $f != "finished.sh" ]; then
                chmod ugo-rwx $f
            fi

            if [ $f == ".data" ]; then
                rm .data
            fi

            touch .data
            chmod ugo-rwx .data
            chmod u+w .data
        done
    fi
    chmod u+rwx $dir

done
