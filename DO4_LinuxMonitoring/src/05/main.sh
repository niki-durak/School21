#!/bin/bash

source ./analyze_logs.sh

if [ "$#" -ne 1 ] || ! [[ "$1" =~ ^[1-4]$ ]]; then
    show_usage
    exit 1
fi

LOG_DIR="../04"
LOG_FILES="$LOG_DIR/nginx_access_*.log"

if ! ls $LOG_FILES >/dev/null 2>&1; then
    echo "Ошибка: Логи не найдены в $LOG_DIR"
    echo "Убедитесь, что файлы nginx_access_*.log существуют"
    exit 1
fi

case $1 in
    1) sort_by_response_code ;;
    2) show_unique_ips ;;
    3) show_error_requests ;;
    4) show_error_ips ;;
esac