#!/bin/bash

if [ -z "$1" ]; then
  echo "Usage: $0 JAIL_FOLDER"
  echo "Mounts every directory in ./sandbox to JAIL_FOLDER with bind and readonly"
  exit 1
fi

jail_folder="$1"

# Create the jail folder if it doesn't exist
if [ ! -d "$jail_folder" ]; then
  mkdir -p "$jail_folder"
fi

mkdir -p "$jail_folder/home/user"

# Loop through each directory in ./sandbox and mount it to the jail
for dir in $(find ./sandbox -maxdepth 1 -type d ); do
  # Get the relative path to the directory
  if [ "$dir" != "./sandbox" ]; then
    rel_path=${dir#./sandbox}
    mkdir -p "$jail_folder$rel_path"
    # Mount the directory to the jail with bind and readonly
    mount --bind -o ro "$dir" "$jail_folder$rel_path"
  fi
done

# Add symlinks to /bin /lib /lib64
ln -s /usr/bin "$jail_folder/bin"
ln -s /usr/lib "$jail_folder/lib"
ln -s /usr/lib64 "$jail_folder/lib64"

