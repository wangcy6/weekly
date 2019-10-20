## 基本概念

>什么是TSL

http://www.ruanyifeng.com/blog/2014/02/ssl_tls.html
SSL/TLS协议的基本思路是采用公钥加密法，也就是说，客户端先向服务器端索要公钥，然后用公钥加密信息，服务器收到密文后，用自己的私钥解密。


>什么是数字证书认证机构CA？

Certificate Authority，缩写为CA，
是负责发放和管理数字证书的权威机构，并作为电子商务交易中受信任的第三方，承担公钥体系中公钥的合法性检验的责任。CA 机构是独立的，没有相互关系，这些机构都是在webtrust认证审核下成立的。
签发主流机构：Symantec、Comodo、GeoTrust、DigiCert、GlobalSign 等。


C  => Country
ST => State
L  => City
O  => Organization
OU => Organization Unit
CN => Common Name (证书所请求的域名)
emailAddress => main administrative point of contact for the certificate




- 什么是根证书 (ROOT CA)
https://zh.wikipedia.org/wiki/%E6%A0%B9%E8%AF%81%E4%B9%A6

>在密码学和计算机安全领域，根证书（root certificate）是属于根证书颁发机构（CA）的公钥证书，是在公开密钥基础建设中，信任链的起点[

根证书没有上层机构再为其本身作数字签名，所以都是自签证书。
许多应用软件（例如操作系统、网页浏览器）会预先安装可被信任的根证书

OpenSSL 是一个免费开源的库，它提供了构建数字证书的命令行工具，其中一些可以用来自建 Root CA。


- SSL 证书验证级别

https://www.barretlee.com/blog/2016/04/24/detail-about-ca-and-certs/
单域名版：只保护一个域名，例如 www.abc.com 或者 login.abc.com 之类的单个域名
多域名版：一张证书可以保护多个域名，例如同时保护 www.abc.com , www.bcd.com, pay.efg.com 等
通配符版：一张证书保护同一个主域名下同一级的所有子域名，不限个数，形如 *.abc.com 。注意，通配符版只有 DVSSL 和 OVSSL 具有， EVSSL 不具有通配符版本

单向认证 SSL 协议不需要客户拥有CA证
一般Web应用都是采用SSL单向认证的

> 什么是 SAN?
SAN(Subject Alternative Name) 是 SSL 标准 x509 中定义的一个扩展。使用了 SAN 字段的 SSL 证书，
可以扩展此证书支持的域名，使得一个证书可以支持多个不同域名的解析。
http://liaoph.com/openssl-san/


https://github.com/barretlee/autocreate-ca
https://www.barretlee.com/blog/2016/04/24/detail-about-ca-and-certs/


-- 证书怎么被签名

它包含了 root key（ca.key.pen）和 root certificate（ca.cert.pem）

通常情况下，root CA 不会直接为服务器或者客户端签证，它们会先为自己生成几个中间 CA（intermediate CAs），这几个中间 CA 作为 root CA 的代表为服务器和客户端签证。


相关视频教程

https://www.youtube.com/watch?v=qXLD2UHq2vk
https://www.youtube.com/watch?v=heacxYUnFHA
# ssl流程 

~~~

由CA签发证书认证网站的过程

CA机构生成密钥对: 公钥 ca.cer 和 私钥 ca.key
浏览器/操作系统携带证书ca.cer
网站生成私钥 cert.key
网站将公钥及网站信息(域名/组织等),提交给CA机构
CA机构使用私钥ca.key签发网站证书cert.cer
网站运营商通过cert.key和 cert.cer运行https
用户访问网站,获得cert.cer,由于该证书使用CA机构的私钥签发,因此可以通过保存在本地的公钥ca.cer验证
验证通过并得到了公钥-> 显示绿色https标志; 否则,提示用户风险信息
用户通过公钥与网站服务器交换对称加密密钥,进行正式的SSL会话

~~~

# ssl证书证书方式

- 一键生成ssl证书 
  https://www.barretlee.com/blog/2016/04/24/detail-about-ca-and-certs/
  https://github.com/barretlee/autocreate-ca/

### 准备工作

1. centos 配置
~~~
mkdir ssl
cd ssl

/etc/pki/tls/openssl.cnf，将这个文件复制到 ssl目录下

或者添加 openssl.cnf

[req]
default_bits            = 2018
default_md              = sha256
prompt                  = no
req_extensions          = v3_req
distinguished_name      = req_distinguished_name


[req_distinguished_name]
countryName            = CN
stateOrProvinceName    = Beijing
localityName           = Beijing
postalCode             = 100022
streetAddress          = gm 
organizationName       = gm
organizationalUnitName = gm
emailAddress           = http.bj@qq.com  
commonName           = gomeeting-pre.gomedc.com 

[v3_req]
basicConstraints = critical,CA:true
subjectKeyIdentifier    = hash
authorityKeyIdentifier = keyid:always,issuer
keyUsage =critical,digitalSignature,keyCertSign,cRLSign
extendedKeyUsage  = critical,serverAuth #, clientAuth
subjectAltName = @alt_names
[alt_names]
IP = 10.115.37.45
DNS= gomeeting-pre.gomedc.com


[server_cert]
basicConstraints = critical,CA:FALSE
subjectKeyIdentifier    = hash
authorityKeyIdentifier = keyid:always,issuer
keyUsage =critical,digitalSignature,keyCertSign,cRLSign
extendedKeyUsage  = critical,serverAuth #, clientAuth
subjectAltName = @alt_names
[alt_names]
IP = 10.115.37.45
DNS= gomeeting-pre.gomedc.com

sudo vim /etc/hosts
10.115.37.45 gomeeting-pre.gomedc.com
127.0.0.1 gomeeting-pre.gomedc.com 

export DOMAIN=gomeeting-pre.gomedc.com
export SUBJECT="/C=CN/ST=Beijing/L=Beijing/O=iTranswarp/OU=iTranswarp/CN=$DOMAIN"

~~~
- window 

C:\Windows\System32\drivers\etc 
gomeeting-pre.gomedc.com

### 创建一个自当前日期起为期十年的根证书 root.crt
### 输入域名：url
read -p "Enter your domain [www.example.com]: " DOMAIN
echo "Create server key..."
### 创建根证书密钥文件(自己做CA) ---genrsa ---私钥
openssl genrsa -des3 -out $DOMAIN.key 2048

echo "Create server certificate signing request..."
SUBJECT="/C=CN/ST=Beijing/L=Beijing/O=iTranswarp/OU=iTranswarp/CN=CA "

### 创建根证书的申请文件url.crs  ---req-申请证书

openssl req -new   -sha256   -key $DOMAIN.key -out $DOMAIN.csr  -config ./openssl.cnf
查看证书请求文件的内容：

 openssl req -text -noout -in gomeeting-pre.gomedc.com.csr



echo "Remove password..."
### Remove password..
mv $DOMAIN.key $DOMAIN.origin.key
openssl rsa -in $DOMAIN.origin.key -out $DOMAIN.key

echo "Sign SSL certificate..."
## 签署上面生成的证书：
## 创建一个自当前日期起为期十年的根证书 urt.crt ---x509 --签发证书


openssl x509 -req -days 3650 -in $DOMAIN.csr -signkey $DOMAIN.key -out $DOMAIN.crt -extensions v3_req   -extfile ./server.cnf 



查看证书内容：

openssl x509 -text -noout -in $DOMAIN.crt

### 制作service服务器端证书--nginx


export SUBJECT="/C=CN/ST=Beijing/L=Beijing/O=iTranswarp/OU=iTranswarp/CN=$DOMAIN"

1.创建服务器证书密钥 server.key
openssl genrsa -out server.key 2048 
openssl rsa -in server.key -out server.key
2.创建服务器证书的申请文件 server.csr
openssl req -config server.cnf -new -key server.key -out server.csr

查看证书内容：
openssl req -text -noout -verify -in server.csr


3.创建自当前日期起有效期为期十年的服务器证书 server.crt

openssl x509 -req -days 3650 -sha256 -extfile server.cnf -extensions v3_req -CA $DOMAIN.crt -CAkey $DOMAIN.key -CAcreateserial -in server.csr -out server.crt

查看证书内容：
openssl x509 -text -noout -in server.crt

### tomcat专有的 制作service服务器端证书--tomcat

4.导出.p12文件 server.p12

openssl pkcs12 -export -in /root/ca/intermediate/certs/www.barretlee.com.cert.pem \
-inkey /root/ca/intermediate/private/www.barretlee.com.key.pem  \
-out mycert.p12 -name "tomcat"  \
-CAfile /root/ca/intermediate/certs/ca-chain.cert.pem  \
-caname root -chain

根据命令提示，输入server.key密码，创建p12密码。



>关键步骤: 

>根据ca证书和服务器的证书来产生tomcat的key




5.将.p12 文件导入到keystore JKS文件 server.keystore


keytool -importkeystore -v  -srckeystore mycert.p12 -srcstoretype pkcs12 -srcstorepass 123456 -destkeystore tomcat.keystore -deststoretype jks -deststorepass 123456 







### 添加信任 CA 

将证书安装到系统中，目的是让本机信任这个 CA，将其当作一个权威 CA，


### 证书的调试 



- 遇到的错误1
如果不执行这一步，浏览器依然会提示 net:ERR_CERT_AUTHORITY_INVALID

![ERR_CERT_AUTHORITY_INVALID](https://upload-images.jianshu.io/upload_images/1837968-25b7851d1cd72993.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

遇到的错误2
>由于CA 根证书不在“受信任的根证书颁发机构”存储区中

![由于CA 根证书不在“受信任的根证书颁发机构”存储区中](https://upload-images.jianshu.io/upload_images/1837968-253af818f9ef2336.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

解决办法：
~~~
NET::ERR_CERT_AUTHORITY_INVALID
1 Windows-Chrome
    将server-cert.pem下载到客户电脑上, 改名为server-cert.cer且双击此文件
    点击安装证书->当前用户->将所有的证书放入下列存储->浏览->受信任的根证书颁发机构->确定->下一步->完成->确定->确定
    重启Chrome浏览器, 再次访问即可, 也可以直接在浏览器中输入chrome://restart来重启Chrome浏览器

2 macOS-Chrome
   将server-cert.pem下载到客户电脑上, 改名为server-cert.cer
   参考Windows方式自行谷歌百度, 关键词: macOS 导入cer证书
3  Firefox
   在警告页，点击高级->添加例外->确认安全例外
~~~



- 错误3  NET::ERR_CERT_COMMON_NAME_INVALID
https://codeday.me/bug/20181124/407114.html


解决办法：
~~~
Chrome已经不再支持证书中的commonName匹配，\
 实际上，自2017年1月起需要subjectAltName
~~~


- 错误4 ERR_CERT_INVALID
  
  
https://stackoverflow.com/questions/46743472/invalid-self-signed-certificate

https://stackoverflow.com/questions/21297139/how-do-you-sign-a-certificate-signing-request-with-your-certification-authority/21340898#21340898



解决办法：
~~~
1
 使用openssl req命令来生成server.csr文件的时没配置openssl.cnf文件且没有带上-config openssl.cnf

2 openssl.cnf中指定了keyUsage但是没带keyCertSign
~~~

## 3 参考

第一次：都有错误

http://wiki.cacert.org/FAQ/subjectAltName



https://www.jianshu.com/p/045f95c008a0
https://github.com/eagleoflqj/Experience/blob/master/openssl.md#?tdsourcetag=s_pctim_aiomsg
https://www.jianshu.com/p/71ce5e6eb6a7
https://github.com/michaelliao/itranswarp.js/blob/master/conf/ssl/gencert.sh
https://github.com/eagleoflqj/Experience/blob/master/openssl.md#?tdsourcetag=s_pctim_aiomsg

https://www.jianshu.com/p/c5c88b6bf2e4

第二次网络查询 不正确

https://github.com/barretlee/autocreate-ca



https://www.fullstackmemo.com/2018/05/10/openssl-gen-https-self-signed-cer/

https://www.openssl.org/docs/manmaster/man5/x509v3_config.html


https://superuser.com/questions/738612/openssl-ca-keyusage-extension

第三次尝试:解决
1 tomcat专属命令有问题
2 导入ca证书方式有问题
https://www.oschina.net/question/2266279_221175