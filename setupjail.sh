path="$1"
mkdir -p $path/sandbox

cp -r -L /usr $path/sandbox

mkdir -p $path/sandbox/dev
sudo mknod $path/sandbox/dev/null c 1 3
sudo mknod $path/sandbox/dev/tty c 5 0
mkdir -p $path/sandbox/proc
