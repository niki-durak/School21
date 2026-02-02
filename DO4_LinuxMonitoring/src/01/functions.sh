#!/bin/bash

check_disk_space() {
    local required_space=$((1 * 1024 * 1024))
    local available_space=$(df / | awk 'NR==2 {print $4}')
    
    if [ "$available_space" -lt "$required_space" ]; then
        echo "Ошибка: В файловой системе осталось менее 1 ГБ свободного места."
        exit 1
    fi
}

generate_name() {
    local letters=$1
    local min_length=$2
    local date_suffix=$(date +"%d%m%y")
    
    local length=$(( RANDOM % (7 - min_length + 1) + min_length ))
    local name=""
    
    # Сначала добавляем каждую букву хотя бы один раз
    for (( i=0; i<${#letters}; i++ )); do
        name+=${letters:$i:1}
    done
    
    # Затем добавляем случайные буквы до нужной длины
    while [ ${#name} -lt $length ]; do
        local random_char=${letters:$(( RANDOM % ${#letters} )):1}
        name+=$random_char
    done
    
    # Перемешиваем буквы (кроме первого символа каждой уникальной буквы)
    if [ ${#name} -gt ${#letters} ]; then
        local fixed_part=${name:0:${#letters}}
        local random_part=${name:${#letters}}
        random_part=$(echo $random_part | fold -w1 | shuf | tr -d '\n')
        name=$fixed_part$random_part
    fi
    
    echo "${name}_${date_suffix}"
}

create_files_and_folders() {
    local base_path=$1
    local folder_count=$2
    local folder_letters=$3
    local file_count=$4
    local file_letters=$5
    local file_size_kb=$6
    local log_file=$7
    
    if [ ${#folder_letters} -gt 7 ]; then
        echo "Ошибка в 3 параметре: Для имен папок указано более 7 символов."
        exit 1
    fi
    
    local file_name_letters=${file_letters%.*}
    local file_ext_letters=${file_letters#*.}
    
    if [ ${#file_name_letters} -gt 7 ] || [ ${#file_ext_letters} -gt 3 ]; then
        echo "Ошибка в 5 параметре: Для имен файлов указано более 7 символов или для расширений более 3 символов."
        exit 1
    fi
    
    if [ $file_size_kb -gt 100 ]; then
        echo "Ошибка: Размер файла превышает 100 КБ."
        exit 1
    fi
    
    # Создаем папки
    for (( i=0; i<folder_count; i++ )); do
        check_disk_space
        
        local folder_name=$(generate_name "$folder_letters" 4)
        local full_folder_path="${base_path}/${folder_name}"
        
        mkdir -p "$full_folder_path"
        echo "$(date +"%Y-%m-%d %H:%M:%S") - Created folder: $full_folder_path" >> "$log_file"
        
        # Создаем файлы в каждой папке
        for (( j=0; j<file_count; j++ )); do
            check_disk_space
            
            local file_name_part=$(generate_name "$file_name_letters" 4)
            local file_ext_part=$(generate_name "$file_ext_letters" 1)
            local file_name="${file_name_part}.${file_ext_part}"
            local full_file_path="${full_folder_path}/${file_name}"
            
            dd if=/dev/zero of="$full_file_path" bs=1024 count=$file_size_kb 2>/dev/null
            echo "$(date +"%Y-%m-%d %H:%M:%S") - Created file: $full_file_path, size: ${file_size_kb}KB" >> "$log_file"
        done
    done
}