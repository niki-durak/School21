#!/bin/bash

# Коды HTTP ответов и их значения:
# 200 - OK - Успешный запрос
# 201 - Created - Ресурс создан
# 400 - Bad Request - Неверный запрос
# 401 - Unauthorized - Требуется аутентификация
# 403 - Forbidden - Доступ запрещен
# 404 - Not Found - Ресурс не найден
# 500 - Internal Server Error - Ошибка сервера
# 501 - Not Implemented - Не реализовано
# 502 - Bad Gateway - Ошибка шлюза
# 503 - Service Unavailable - Сервис недоступен

generate_ip() {
    echo "$((RANDOM%256)).$((RANDOM%256)).$((RANDOM%256)).$((RANDOM%256))"
}

generate_datetime() {
    local day="$1"
    local hour=$(printf "%02d" $((RANDOM%24)))
    local minute=$(printf "%02d" $((RANDOM%60)))
    local second=$(printf "%02d" $((RANDOM%60)))
    echo "${day}T${hour}:${minute}:${second}+00:00"
}

generate_url() {
    local paths=("/" "/index.html" "/api/user" "/api/data" "/images/photo.jpg" 
                 "/documents/file.pdf" "/search" "/admin" "/login" "/logout")
    local queries=("" "?id=123" "?page=1" "?filter=all" "?sort=desc")
    echo "${paths[$RANDOM%${#paths[@]}]}${queries[$RANDOM%${#queries[@]}]}"
}

generate_user_agent() {
    local agents=(
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64)"
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7)"
        "Google Chrome/91.0.4472.124"
        "Opera/9.80 (Windows NT 6.1; U; en) Presto/2.7.62 Version/11.01"
        "Safari/537.36"
        "Internet Explorer/11.0"
        "Microsoft Edge/91.0.864.59"
        "Mozilla/5.0 (compatible; Googlebot/2.1; +http://www.google.com/bot.html)"
        "curl/7.68.0"
    )
    echo "${agents[$RANDOM%${#agents[@]}]}"
}

generate_log_file() {
    local day="$1"
    local file="$2"
    local entries=$((RANDOM%901 + 100))
    
    echo "Генерация файла $file с $entries записями за $day"
    
    local timestamps=()
    for ((i=0; i<entries; i++)); do
        timestamps[$i]=$(date -d "$day +$((i*86400/entries)) seconds" +"%s")
    done
    
    for ((i=0; i<entries; i++)); do
        j=$((RANDOM%entries))
        temp=${timestamps[$i]}
        timestamps[$i]=${timestamps[$j]}
        timestamps[$j]=$temp
    done
    timestamps=($(printf '%s\n' "${timestamps[@]}" | sort -n))
    
    for ((i=0; i<entries; i++)); do
        ip=$(generate_ip)
        timestamp=$(date -d "@${timestamps[$i]}" +"[%d/%b/%Y:%H:%M:%S %z]")
        method=("GET" "POST" "PUT" "PATCH" "DELETE")
        method=${method[$RANDOM%5]}
        url=$(generate_url)
        code=(200 201 400 401 403 404 500 501 502 503)
        code=${code[$RANDOM%10]}
        bytes=$((RANDOM%10000 + 500))
        referer="-"
        agent=$(generate_user_agent)
        
        echo "$ip - - $timestamp \"$method $url HTTP/1.1\" $code $bytes \"$referer\" \"$agent\"" >> "$file"
    done
}