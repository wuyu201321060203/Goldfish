#!/bin/sh

mysql -e "create database DM"

mysql -e "create table IMCONFIG_INFO(id int not null auto_increment , domainName varchar(50) not null , raIP varchar(30) not null , primary key(id));"

mysql -e "create table DOMAIN_INFO(id INT NOT NULL AUTO_INCREMENT , name varchar(100) not null , description varchar(300) null , corenum int default 1, memsize int default 2 , exefilePath varchar(500) not null , IP varchar(30) , Port int , primary key(id))engine = innodb;"

mysql -e "create table GROUP_INFO(id int not null auto_increment , name varchar(100) not null , description varchar(300) null , belong2Domain int not null, primary key(id) , foreign key(belong2Domain) references DOMAIN_INFO(id) on delete cascade on update cascade)engine = innodb;"

mysql -e "create table USER_INFO(id int not null auto_increment , name varchar(50) not null , passwd varchar(50) not null , belong2Domain int not null , belong2Group int not null , identity int not null , primary key(id) , foreign key(belong2Group) references GROUP_INFO(id) on delete cascade on update cascade)engine = innodb;"