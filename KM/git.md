<<<<<<< HEAD
###  git 教程
- https://www.atlassian.com/git/tutorials/learn-git-with-bitbucket-cloud
- https://backlog.com/git-tutorial/cn/
- https://happygitwithr.com/big-picture.html
- https://www.youtube.com/watch?v=Qw-DD7-Xk98&list=PLliocbKHJNwvDp464ktZCsj8h7rXFBE8r&index=2
## 协作
### 创建工程
- fork别的项目
  https://github.com/azl397985856/leetcode
- 下载fork之后的自己的项目：
  git clone https://github.com/wangcy6/leetcode-1.git

说明：
1. 不同用户下工程
2. fork的代码更新，我clone代码不会自动更新。

### 同步更新

  
git remote -v

git remote add upstream https://github.com/azl397985856/leetcode.git

git fetch upstream
git merge upstream/master
git push --提交代码到到自己分支


### 合并代码

https://backlog.com/git-tutorial/cn/stepup/stepup2_7.html
https://happygitwithr.com/pull-tricky.html




**Merging is not possible because you have unmerged files**
你代码不是最新的，别人已经更新该文件，你当前文件是old的。你当前版本002 ，别人更新008
 团队中两人同时fetch了一个分支。 第一个人修改后提交，第二个人提交就失败

1. 查看冲突 
 - git diff 
  
 -  git status 可以用来查看仓库的状态。
   撤销本地修改
  有三个状态，三个出来方案
  git checkout  --2019-06-14.md
  git reset HEAD 2019-06-14.md
  
2. 修改冲突

   
### 提交代码
https://www.atlassian.com/git/tutorials/making-a-pull-request#how-it-works

Pull Request 是什么

>Pull Request 是一种通知机制。你修改了他人的代码，将你的修改通知原来的作者，希望他合并你的修
>Pull requests let you tell others about changes you've pushed to a branch in a repository on GitHub.

Pull Request 的流程:

- 切换分支
  git checkout -b daily-branch
  git branch
- 添加代码 
  git add 2019-06-14.md 
  git commit  -am "#add"
- 提交代码
  git push --set-upstream origin daily-branch
- 重新登录GitHub并切换到work分支，点击compare&Pull Request

#### 报错1 git push
fatal: The current branch daily-branch has no upstream branch.
To push the current branch and set the remote as upstream, use

    git push --set-upstream origin daily-branch
    git push origin some-branch



### 日志
 git log  --oneline -3
=======
# git 教程

## pull 



git remote -v

git remote add upstream https://github.com/azl397985856/leetcode.git

git fetch upstream

 git merge upstream/master



 **Merging is not possible because you have unmerged files**

你代码不是最新的，别人已经更新该文件，你当前文件是old的。你当前版本002 ，别人更新008

 团队中两人同时fetch了一个分支。 第一个人修改后提交，第二个人提交就失败

 

​    git diff

   git status 



>>>>>>> 92a8dc8bf32902f07728f3a2be9ee959bf33a5e4


