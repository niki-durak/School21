#!/bin/bash

LOG_FILES="../04/nginx_access_*.log"
CONFIG_FILE="goaccess.conf"
OUTPUT_FILE="report.html"

LOG_FORMAT="COMBINED"
PORT=7890

TIME_FORMAT="%H:%M:%S"
DATE_FORMAT="%d/%b/%Y"
LOG_PATTERN='%h %^[%d:%t %^] "%r" %s %b "%R" "%u"'

if [ ! -f "$CONFIG_FILE" ]; then
  cat > "$CONFIG_FILE" <<EOF
time-format $TIME_FORMAT
date-format $DATE_FORMAT
log-format $LOG_PATTERN
EOF
fi