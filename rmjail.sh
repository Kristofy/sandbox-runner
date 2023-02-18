#!/bin/bash

if [ -z "$1" ]; then
  echo "Usage: $0 JAIL_FOLDER"
  echo "Unmounts every mounted directory in JAIL_FOLDER and deletes the folder"
  exit 1
fi

jail_folder="$1"

# Unmount all the directories that were mounted in the jail folder
for dir in $(find "$jail_folder" -maxdepth 1 -type d); do
  # Skip the home directory and the jail folder itself
  if [ "$dir" != "$jail_folder" ] && [ "${dir##*/}" != "home" ]; then
    mount -o remount,rw "$dir"
    umount "$dir"
  fi
done

# Delete the jail folder
rm -r "$jail_folder"
