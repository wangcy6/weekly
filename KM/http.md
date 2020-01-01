



# 基础知识

# day1

## 资料

- HTTP权威指南（中文版） 1 ，3章节
- http://www.ruanyifeng.com/blog/2011/09/curl.html

## 输出



### 协议格式

![image-20191105194051987](../../images/image-20191105194051987.png)

![image-20191105200334270](../../images/image-20191105200334270.png)

常见的状态码有如下几种：

- `200 OK` 客户端请求成功
- `301 Moved Permanently` 请求永久重定向
- `302 Moved Temporarily` 请求临时重定向
- `304 Not Modified` 文件未修改，可以直接使用缓存的文件。（**get 告诉浏览器请求的资源在浏览器上没有更新，可以使用已缓存的上次获取的文件**）
- `400 Bad Request` 由于客户端请求有语法错误，不能被服务器所理解。
- `401 Unauthorized` 请求未经授权。这个状态代码必须和WWW-Authenticate报头域一起使用
- `403 Forbidden` 服务器收到请求，但是拒绝提供服务。服务器通常会在响应正文中给出不提供服务的原因
- `404 Not Found` 请求的资源不存在，例如，输入了错误的URL
- `500 Internal Server Error` 服务器发生不可预期的错误，导致无法完成客户端的请求。
- `503 Service Unavailable` 服务器当前不能够处理客户端的请求，在一段时间之后，服务器可能会恢复正常。

`-i`参数可以显示http response的头信息，连同网页代码一起。

curl -v  https://wangcy6.github.io/