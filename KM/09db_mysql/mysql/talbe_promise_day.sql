create table promise_day(
   id int auto_increment,
   note VARCHAR(1000) NOT NULL,
   create_time    timestamp default CURRENT_TIMESTAMP ,
   PRIMARY KEY ( id )
)ENGINE=InnoDB DEFAULT CHARSET=utf8;


insert into promise_day (note) values ('创建mysql表');
select * from dream.promise_day;

select * from dream.bug;



mysql> desc project;
+---------------+--------------+------+-----+-------------------+----------------+
| Field         | Type         | Null | Key | Default           | Extra          |
+---------------+--------------+------+-----+-------------------+----------------+
| id            | int(11)      | NO   | PRI | NULL              | auto_increment |
| name          | varchar(300) | YES  |     | NULL              |                |
| step          | varchar(300) | YES  |     | NULL              |                |
| days          | int(11)      | YES  |     | NULL              |                |
| result        | int(11)      | YES  |     | NULL              |                |
| creation_time | datetime     | YES  |     | CURRENT_TIMESTAMP |                |
+---------------+--------------+------+-----+-------------------+----------------+
6 rows in set (0.00 sec)



insert into dream.project(name,step,days,result) values('开启小盘茄，滴滴声音，除非你静音，他们永远都在','从耳朵拒绝听他们声音，吃饭看腾讯视频等声音就像希腊神话塞壬女妖迷惑船员的歌声 ,奥德修斯遵循女神喀耳刻的忠告。为了对付塞壬姐妹，他采取了谨慎的防备措施。船只还没驶到能听到歌声的地方，奥德修斯就令人把他拴在桅杆上，并吩咐手下用蜡把他们的耳朵塞住。他还告诫他们通过死亡岛时不要理会他的命令和手',30,0);

select * from dream.project;

explain select * from dream.project order by name;