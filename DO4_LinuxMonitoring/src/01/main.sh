#!/bin/bash

if [ "$#" -ne 6 ]; then
    echo "Ошибка: Необходимо передать 6 параметров."
    exit 1
fi

base_path=$1
folder_count=$2
folder_letters=$3
file_count=$4
file_letters=$5
file_size=${6%kb}

if ! [[ "$file_size" =~ ^[0-9]+$ ]]; then
    echo "Ошибка: Размер файла должен быть числом (в килобайтах)."
    exit 1
fi

log_file="creation_log_$(date +"%d%m%y_%H%M%S").txt"
echo "Script started at $(date +"%Y-%m-%d %H:%M:%S")" > "$log_file"

source ./functions.sh

create_files_and_folders "$base_path" "$folder_count" "$folder_letters" "$file_count" "$file_letters" "$file_size" "$log_file"

echo "Скрипт успешно завершен. Лог сохранен в $log_file"