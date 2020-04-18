//格言
create table note(
   id int auto_increment,
   note VARCHAR(1000) NOT NULL,
   author VARCHAR(100) NOT NULL,
   create_time    timestamp default CURRENT_TIMESTAMP ,
   PRIMARY KEY ( id )
);
ALTER TABLE note CONVERT TO CHARACTER SET utf8mb4;