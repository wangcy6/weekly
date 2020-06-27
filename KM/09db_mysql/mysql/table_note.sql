//格言
create table dream.note(
   id int auto_increment,
   note VARCHAR(1000) NOT NULL,
   author VARCHAR(100) NOT NULL,
   create_time    timestamp default CURRENT_TIMESTAMP ,
   PRIMARY KEY ( id )
);
ALTER TABLE dream.note CONVERT TO CHARACTER SET utf8mb4;

insert into note(note,author) value('选择正确的“难受”','通往财富自由之路');
select * from note; 