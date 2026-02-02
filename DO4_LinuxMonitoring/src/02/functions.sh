#!/bin/bash

check_disk_space() {
    local required_space=1024
    local available_space=$(df -m / | awk 'NR==2 {print $4}')
    
    if [ "$available_space" -lt "$required_space" ]; then
        echo "Остановка: В файловой системе осталось менее 1 ГБ свободного места."
        return 1
    fi
    return 0
}

generate_name() {
    local letters=$1
    local min_length=5
    local date_suffix=$(date +"%d%m%y")
    
    local length=$(( RANDOM % 3 + min_length ))
    local name=""
    
    for (( i=0; i<${#letters}; i++ )); do
        name+=${letters:$i:1}
    done
    
    # Затем добавляем случайные буквы до нужной длины
    while [ ${#name} -lt $length ]; do
        local random_char=${letters:$(( RANDOM % ${#letters} )):1}
        name+=$random_char
    done
    
    echo "${name}_${date_suffix}"
}

find_suitable_directories() {
    find ~/ /tmp -type d 2>/dev/null | grep -v -E "(/bin|/sbin|/usr|/lib|/proc|/sys)"
}

create_clutter() {
    local folder_chars=$1
    local file_name_chars=$2
    local file_ext_chars=$3
    local file_size=$4
    local log_file=$5
    
    local counter=0
    echo "Начинаем создание файлов и папок..."
    
    while check_disk_space && [ $counter -lt 100 ]; do
        # Выбираем случайную директорию из подходящих
        target_dir=$(find_suitable_directories | shuf -n 1)
        
        [ -z "$target_dir" ] && echo "Не найдено подходящих директорий!" && break
        
        folder_name=$(generate_name "$folder_chars")
        full_folder_path="${target_dir}/${folder_name}"
        
        echo "Создаём папку: $full_folder_path"
        mkdir -p "$full_folder_path"
        echo "$(date +"%Y-%m-%d %H:%M:%S") - Created folder: $full_folder_path" >> "$log_file"
        
        # Случайное количество файлов в папке (от 1 до 5)
        file_count=$(( RANDOM % 5 + 1 ))
        
        # Создаем файлы в папке
        for (( i=0; i<file_count; i++ )); do
            if ! check_disk_space; then
                break 2
            fi
            file_name_part=$(generate_name "$file_name_chars")
            file_ext_part=$(generate_name "$file_ext_chars")
            file_name="${file_name_part}.${file_ext_part}"
            full_file_path="${full_folder_path}/${file_name}"
            
            echo "Создаём файл: $full_file_path (${file_size}MB)"

            dd if=/dev/zero of="$full_file_path" bs=1M count=$file_size 2>/dev/null
            
            echo "$(date +"%Y-%m-%d %H:%M:%S") - Created file: $full_file_path, size: ${file_size}MB" >> "$log_file"
        done
        
        ((counter++))
    done
    
    echo "Создано папок: $counter"
}