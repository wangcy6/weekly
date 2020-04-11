create table promise_day(
   id int auto_increment,
   note VARCHAR(1000) NOT NULL,
   create_time    timestamp default CURRENT_TIMESTAMP ,
   PRIMARY KEY ( id )
);
ALTER TABLE promise_day CONVERT TO CHARACTER SET utf8mb4;

insert into promise_day (note) values ('创建mysql表');
select * from dream.promise_day;

select * from dream.bug;

insert into bug(problem,tag,failed,try,fix) values('9个因素一起来 a手机有百度网盘，b在周末时候，c有热门电影，综艺节目，d在吃饭时候，e 在床上，f未来不控制，g微信有资源，h手机解锁 i 地铁 让思想开始堕落。不停看手机很忙碌','自己放弃的后果',1000,0,0);


