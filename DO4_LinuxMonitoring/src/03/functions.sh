#!/bin/bash

check_sudo() {
    if [ "$(id -u)" -ne 0 ]; then
        echo "Ошибка: Требуются права root/sudo для удаления системных файлов!"
        exit 1
    fi
}

clean_by_log() {
    local log_file="$1"
    
    if [ ! -f "$log_file" ]; then
        echo "Ошибка: Файл журнала '$log_file' не найден!"
        exit 1
    fi
    
    echo "=== Очистка по журналу ($log_file) ==="
    
    grep "Created file:" "$log_file" | awk -F': ' '{print $2}' | cut -d',' -f1 | while read -r file; do
        file=$(echo "$file" | xargs)
        if [ -f "$file" ]; then
            rm -fv "$file" || echo "Не удалось удалить файл: $file"
        else
            echo "Файл не найден: $file"
        fi
    done
    
    grep "Created folder:" "$log_file" | awk -F': ' '{print $2}' | while read -r dir; do
        dir=$(echo "$dir" | xargs)  # Удаляем возможные пробелы
        if [ -d "$dir" ]; then
            find "$dir" -type f -delete 2>/dev/null
            rm -rfv "$dir" || echo "Не удалось удалить папку: $dir"
        else
            echo "Папка не найдена: $dir"
        fi
    done
    
    echo "Очистка завершена."
}

clean_by_date() {
    local start_time="$1"
    local end_time="$2"
    local log_file="$3"
    
    if [ ! -f "$log_file" ]; then
        echo "Ошибка: Файл журнала '$log_file' не найден!"
        exit 1
    fi
    
    echo "=== Очистка за период с $start_time по $end_time ==="
    
    local temp_file=$(mktemp)
    
    awk -v start="$start_time" -v end="$end_time" '
        $1" "$2 >= start && $1" "$2 <= end && /Created (file|folder):/ {print $4}
    ' "$log_file" > "$temp_file"
    
    grep -v "/$" "$temp_file" | while read -r file; do
        if [ -f "$file" ]; then
            rm -fv "$file" || echo "Не удалось удалить файл: $file"
        fi
    done
    
    grep "/$" "$temp_file" | sort -r | while read -r dir; do
        if [ -d "$dir" ]; then
            rm -rfv "$dir" || echo "Не удалось удалить папку: $dir"
        fi
    done
    
    rm -f "$temp_file"
    echo "Очистка завершена."
}

clean_by_mask() {
    local mask="$1"
    
    echo "=== Очистка по маске '*${mask}*' ==="
    
    find / -type f -name "*${mask}*" 2>/dev/null | while read -r file; do
        rm -fv "$file" || echo "Не удалось удалить файл: $file"
    done
    
    find / -type d -name "*${mask}*" 2>/dev/null | sort -r | while read -r dir; do
        rm -rfv "$dir" || echo "Не удалось удалить папку: $dir"
    done
    
    echo "Очистка завершена."
}