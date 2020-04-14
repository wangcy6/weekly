create table qiji_task(
   id int auto_increment,
   ask VARCHAR(1000) NOT NULL,
   finshed int,
   create_time    timestamp default CURRENT_TIMESTAMP ,
   PRIMARY KEY ( id )
);

ALTER TABLE qiji_task CONVERT TO CHARACTER SET utf8mb4;

insert into qiji_task(ask,finshed) values('成为一个架构师,你必须掌握draw.io,绘制流程图，请问你一天, 一天，一周，一个月，绘制多少个？你卡在心里很找之前知道，但是根本不实践，害怕绘制太丑，太差和没有能力,学它，练她','0');

insert into qiji_task(ask,finshed) values('想成为领导，你说话别人必须请清楚，首先不指望你夸夸其谈，你是否克服你的自卑，你焦虑，担心，面对失败,你尝试几次，采用什么方法，请问你一天, 一天，一周，一个月， 你说几次，别人听明白几次？什么原因导致的，还是架构，业务，职位导致眼界导致的','0');

select * from qiji_task;