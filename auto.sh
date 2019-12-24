#--------------------------------------------
# 这是一个定时提交代码的脚本
# 
# 功能：定时提交代码
# 特色：依赖 linux 让 crontab 
# crontab -e 
# 0 18 * * * /home/code/weekly/autoCommit.sh
#--------------------------------------------
cd  /home/code/weekly
git pull
git add -A .
git commit -m "update"
git push origin master