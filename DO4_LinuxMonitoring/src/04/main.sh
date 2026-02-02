#!/bin/bash

source ./log_functions.sh

if [ ! -f "./log_functions.sh" ]; then
    echo "Ошибка: файл log_functions.sh не найден!"
    exit 1
fi

for day in {1..5}; do
    current_date=$(date -d "-$((5-day)) days" +"%Y-%m-%d")
    log_file="nginx_access_$(date -d "$current_date" +"%Y%m%d").log"
    generate_log_file "$current_date" "$log_file"
done

echo "Генерация логов завершена. Создано 5 файлов:"
