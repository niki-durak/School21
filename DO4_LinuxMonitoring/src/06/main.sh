#!/bin/bash

source ./goaccess.sh

if ! ls $LOG_FILES >/dev/null 2>&1; then
  echo "Ошибка: Логи не найдены по пути: $LOG_FILES"
  echo "Убедитесь, что файлы существуют и путь указан верно"
  exit 1
fi

goaccess $LOG_FILES \
  --config-file=$CONFIG_FILE \
  --log-format=$LOG_FORMAT \
  --output=$OUTPUT_FILE \
  --port=$PORT \
  --real-time-html

echo -e "\nОтчёт доступен:"
echo "1. HTML-файл: $OUTPUT_FILE"
echo "2. Веб-интерфейс: http://localhost:$PORT"
echo "3. Для остановки: Ctrl+C"