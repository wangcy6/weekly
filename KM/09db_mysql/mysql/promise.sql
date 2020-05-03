create table promise_day(
   id int auto_increment,
   note VARCHAR(1000) NOT NULL,
   create_time    timestamp default CURRENT_TIMESTAMP ,
   PRIMARY KEY ( id )
);
ALTER TABLE promise_day CONVERT TO CHARACTER SET utf8mb4;

insert into promise_day (note) values ('创建mysql表');
select * from dream.promise_day;