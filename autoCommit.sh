#--------------------------------------------
# 这是一个定时提交代码的脚本
# 
# 功能：定时提交代码
# 特色：依赖 linux 让 crontab 
# 0 18 * * * /home/testuser/test.sh
#--------------------------------------------
cd /d D:\github\weekly
git pull
cd /d D:\github\weekly
git add -A .
git commit -m "update"
git push origin master
echo "weekly ok "