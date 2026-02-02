#!/bin/bash

source ./functions.sh

if [ "$#" -ne 3 ]; then
    echo "Ошибка: Необходимо передать 3 параметра."
    echo "Пример использования: $0 az az.az 3Mb"
    exit 1
fi

folder_chars=$1
file_chars_full=$2
file_size_str=$3

if [[ ${#folder_chars} -gt 7 ]]; then
    echo "Ошибка: Для имен папок указано более 7 символов."
    exit 1
fi

file_name_chars=${file_chars_full%.*}
file_ext_chars=${file_chars_full#*.}

if [[ ${#file_name_chars} -gt 7 || ${#file_ext_chars} -gt 3 ]]; then
    echo "Ошибка: Для имен файлов указано более 7 символов или для расширений более 3 символов."
    exit 1
fi

file_size=${file_size_str%Mb}
if ! [[ "$file_size" =~ ^[0-9]+$ ]] || [ "$file_size" -gt 100 ]; then
    echo "Ошибка: Размер файла должен быть числом (в Мегабайтах, не более 100)."
    exit 1
fi

log_file="file_system_clutter_$(date +"%d%m%y_%H%M%S").log"
echo "Script started at $(date +"%Y-%m-%d %H:%M:%S")" > "$log_file"
start_time=$(date +%s)

create_clutter "$folder_chars" "$file_name_chars" "$file_ext_chars" "$file_size" "$log_file"

end_time=$(date +%s)
total_time=$((end_time - start_time))

echo "Script finished at $(date +"%Y-%m-%d %H:%M:%S")" | tee -a "$log_file"
echo "Total execution time: ${total_time} seconds" | tee -a "$log_file"

echo "Скрипт завершен. Лог сохранён в $log_file"