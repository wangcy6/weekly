## python调用shell命令
lsof -n | awk '{print $2}' | sort | uniq -c | sort -nr | more
from subprocess import call
call(['ls','-l','/boot','/sys'])    #
call('ls -a /',shell=True)