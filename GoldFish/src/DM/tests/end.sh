#!/bin/sh

HOSTNAME="127.0.0.1"
PORT="3306"
USERNAME="root"
PASSWORD="123"
DBNAME="DM"
TABLENAME="USER_INFo"
trail1="update USER_INFO set passwd = 'ddcnmb' where name = 'ddcnmb'"
trail2="delete from USER_INFO where id != 1"
mysql -h${HOSTNAME} -P${PORT} -u${USERNAME} -p${PASSWORD} ${DBNAME} -e "${trail1}"
mysql -h${HOSTNAME} -P${PORT} -u${USERNAME} -p${PASSWORD} ${DBNAME} -e "${trail2}"