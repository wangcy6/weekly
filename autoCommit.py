import os
os.chdir("/home/code/weekly")
git pull
git add -A .
git commit -m "update"
git push origin master


#!/usr/bin/env python
import os
import subprocess
import sys
import time
gitconfig = {
    'cwd': './blog/public',
    'git': {
        'github': ['git@github.com:akkuman/akkuman.github.io.git', 'master'],
        'coding': ['git@git.coding.net:Akkuman/Akkuman.git', 'coding-pages'],
    }
}
def main():
    global gitconfig
    # change working directory
    os.chdir(gitconfig.get('cwd', '.'))
    # check if git init
    if '.git' not in os.listdir():
        subprocess.check_call(['git', 'init'])
    # check if remote in config, if not, add the remote
    git_remotes = subprocess.check_output(['git', 'remote', '-v'])
    git_remotes_str = bytes.decode(git_remotes).strip()
    git_remotes_list = [line.split()[0] for line in git_remotes_str.split('\n')]
    for k,v in gitconfig['git'].items():
        if k not in git_remotes_list:
            subprocess.check_call(['git', 'remote', 'add', k, v[0]])
    # add . & commit with message
    subprocess.check_call(['git', 'add', '.'])
    commit_message = 'Site updated: %s' % time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    if len(sys.argv) == 2:
        commit_message = sys.argv[1]
    subprocess.call(['git', 'commit', '-m', commit_message])
    # push to every remote repo
    for k,v in gitconfig['git'].items():
        subprocess.check_call(['git', 'push', k, 'master:%s' % v[1]])
if __name__ == '__main__':
    if len(sys.argv) == 2:
        if sys.argv[1] == '-h':
            print('Usage:\n\t%s [commit_message]' % sys.argv[0])
    main()