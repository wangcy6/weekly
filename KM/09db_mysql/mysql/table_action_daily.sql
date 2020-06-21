create table dream.task_action_daily(
   id int auto_increment,
   task VARCHAR(1000) NOT NULL,
   days int,
   weekly int,
   months int,
   years int,
   sums  int,
  create_time timestamp default CURRENT_TIMESTAMP ,
   PRIMARY KEY ( id )
);

ALTER TABLE task_action_daily CONVERT TO CHARACTER SET utf8mb4;

insert into dream.task_action_daily(task,days,weekly,months,years,sums) values(
'战拖第一步,你花钱买手机初衷，绝不是为了失去考研，失去工作，失去未来的，失去健康未来，但是遇到腾讯视频就会，
因为综艺节目，动漫
电视剧，都是小时候美好渴望。但是现在成为别人欺骗人手段。
不要说没什么，看1秒而已，一个动漫一个电视剧累计几十亿观看，60分钟，累计下来消耗上百万一辈子生命什么。比什么病毒武器还厉害
这不是图财害命吗？
腾讯小程序视频，成功是虚假成功，
腾讯小程序视频，美女诱惑虚假虚假化。
腾讯小程序视频，娱乐放松虚假放松。
这样千万人什么没有来哦。

你意思到这一点，原来可以不看的，他每天更新宣传真是盈利手段，他们不用他们你无法呼吸不会，
你意思到这一点，原来可以不看的，他每天更新宣传真是盈利手段。他们不用他们你无法呼吸吃饭。
你意思到这一点，原来可以不看的，他每天更新宣传真是盈利手段。他们不用他们你无走路。
是想到--打开--观看--1分钟 30分钟60分钟一天一夜，然后一个月，一年
无论自己学习疲劳，工作不顺还是未来压迫，不会帮助解决任何问题，绝不上面
浪费每个晚上，每个周末，每个上下班时间，每次吃饭。真正下定决心。
真正下定决心 2020-8-20',1,48,48,480,86400);

select * from dream.task_action_daily where id=1;
//2020年累计看多少次，累计看多少周，全年累计xx次，耗时
update task_action_daily set days=days+1,weekly=weekly+1,years=years+1,sums=sums+180  where id=1;

update task_action_daily set days=172 where id=1;
update task_action_daily set weekly=25 where id=1;

更新一个观念：你原来可以选择不看腾讯视频，不是他每次更新动漫，综艺节目，电视剧，你必须去看。
这个不是法律规定，这个也不是工作要求，跟不上社会习俗，对手不希望你看。
你可以选择
痛苦绝望疲累时候，调整好状态，继续战斗。
拒绝美杜莎的诱惑这里搞笑，成功，美v不是你的。
战拖，自控从自我救赎-远离腾讯视频开始 一次一秒也不行，培养重视态度。

select days,weekly,years, sums from dream.task_action_daily where id=1;

insert into dream.task_action_daily(task,days,weekly,months,years,sums) values('一周三次跑步',0,0,0,0,0);

//本周累计 本月累计 ，全年累计 

update task_action_daily set weekly=weekly+1,months=months+1,years=years+1 where id=2;
