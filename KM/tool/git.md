# git 教程





### git 如何update  fork别人的项目

1.合并本地冲突，或者提交本地代码 
git reset --hard FETCH_HEAD

2.添加远程仓库
 git remote add upstream https://github.com/azl397985856/leetcode.git
 git remote -v

3. 拉取源仓库的代码到本地
   git fetch upstream
4. 合并源仓库的 master 分支代码到本地

  git merge upstream/master





