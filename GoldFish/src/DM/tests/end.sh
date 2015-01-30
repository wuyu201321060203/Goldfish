#!/bin/sh

HOSTNAME="127.0.0.1"
PORT="3306"
USERNAME="root"
PASSWORD="123"
DBNAME="DM"
TABLENAME="USER_INFo"
trail1="update USER_INFO set passwd = 'ddcnmb' where name = 'ddcnmb'"
mysql -h${HOSTNAME} -P${PORT} -u${USERNAME} -p${PASSWORD} ${DBNAME} -e "${trail1}"