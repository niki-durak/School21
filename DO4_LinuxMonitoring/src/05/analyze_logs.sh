#!/bin/bash

show_usage() {
    echo "Использование: $0 <режим>"
    echo "Режимы:"
    echo "1 - Все записи, отсортированные по коду ответа"
    echo "2 - Все уникальные IP-адреса"
    echo "3 - Все запросы с ошибками (4xx или 5xx)"
    echo "4 - Уникальные IP с ошибочными запросами"
}

sort_by_response_code() {
    echo "Все записи, отсортированные по коду ответа:"
    awk '{print $9, $0}' $LOG_FILES | sort -n | cut -d' ' -f2-
}

show_unique_ips() {
    echo "Все уникальные IP-адреса:"
    awk '{print $1}' $LOG_FILES | sort -u
}

show_error_requests() {
    echo "Все запросы с ошибками (4xx или 5xx):"
    awk '$9 ~ /^[45][0-9][0-9]$/' $LOG_FILES
}

show_error_ips() {
    echo "Уникальные IP с ошибочными запросами:"
    awk '$9 ~ /^[45][0-9][0-9]$/ {print $1}' $LOG_FILES | sort -u
}

