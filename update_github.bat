@echo off

cd /d F:\coding\weekly
git pull
git add -A .
git commit -m "update"

echo "commit weekly ok"

cd /d F:\coding\leetcode
git pull
git add -A .
git commit -m "update"
echo "leetcodeok"

cd /d F:\coding\reading_code_note
git pull
git add -A .
git commit -m "update"
echo "reading_code_note ok"


cd /d G:\money\eye
git pull
git add -A .
git commit -m "update"
echo "eye ok"


cd /d G:\code\TryEverything
git pull
git add -A .
git commit -m "update"
echo "TryEverything ok"

cd /d F:\coding\leetcode
git pull
git add -A .
git commit -m "update"
echo "TryEverything ok"


