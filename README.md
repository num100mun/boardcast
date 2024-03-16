broadcat
git init
git remote add origin git@xxx.git //建立关联 ->git remote remove xxx 清除连接-> git remote -v 查看remote
git ssh -keygen -t rsa -b 4096 -C "xxx@qq.com" //创建shh公钥
cat ~/.ssh/id_rsa.pub //查看公钥->回去密钥
ssh -T git@github.com //测试连接
git remote set-url origin git@xxx.git //设置上传路径
git branch -M main
git push -u origin main
