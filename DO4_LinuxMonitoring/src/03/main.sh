#!/bin/bash

source ./functions.sh

check_sudo

if [ "$#" -lt 1 ]; then
    echo "Использование:"
    echo "  $0 1 /../../logfile.log          # По журналу"
    echo "  $0 2 '2023-11-20 10:00' '2023-11-20 11:00' /../../logfile.log # По дате"
    echo "  $0 3 'abc'                        # По маске"
    exit 1
fi

method="$1"

case "$method" in
    1)
        [ -z "$2" ] && { echo "Укажите путь к лог-файлу"; exit 1; }
        clean_by_log "$2"
        ;;
    2)
        if [ -z "$4" ]; then
            read -p "Введите начальную дату (ГГГГ-ММ-ДД ЧЧ:ММ): " start_time
            read -p "Введите конечную дату (ГГГГ-ММ-ДД ЧЧ:ММ): " end_time
            read -p "Введите путь к лог-файлу: " log_file
        else
            start_time="$2"
            end_time="$3"
            log_file="$4"
        fi
        clean_by_date "$start_time" "$end_time" "$log_file"
        ;;
    3)
        [ -z "$2" ] && { read -p "Введите маску имени: " mask; } || mask="$2"
        clean_by_mask "$mask"
        ;;
    *)
        echo "Неверный метод. Используйте 1, 2 или 3."
        exit 1
        ;;
esac