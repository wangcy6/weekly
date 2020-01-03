



# 基础知识

# day1

## 资料

- HTTP权威指南（中文版） 1 ，3，15章节 

- http://www.ruanyifeng.com/blog/2011/09/curl.html

- Hypertext Transfer Protocol (HTTP/1.1): Semantics and Content

  https://tools.ietf.org/html/rfc7231#page-25

- https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods/PUT

- 

## 输出



### 请求类型

[HTTP request methods](https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods)

- get 

- head
- post
- put 

~~~shell
curl -v --head  https://wangcy6.github.io/ 	 
//请求和响应的包只有head，没有body

curl -v -X GET  https://wangcy6.github.io/  
//请求只有head.
curl -v -X POST  https://wangcy6.github.io/ 
405 Not Allowed
出现405错误的原因是nginx不允许post静态页
~~~



![image.png](../images/b2CYVcQHJEMZfpm.png)

![image.png](../images/qnLsFU4jSV3fIxJ.png)

~~~shell
Content-Length: 13238 确定主题长度的规则
Content-Type: text/html; charset=utf-8
~~~

![image-20200101141512951](../images/image-20200101141512951.png)

![image.png](../images/86lt4WvK9FCrdya.png)



### 区别

![image-20200101142314339](../images/image-20200101142314339.png)

The **HTTP `GET` method** requests a representation of the specified resource. Requests using `GET` should only retrieve data.

| Request has body                                             | No   |
| :----------------------------------------------------------- | ---- |
| Successful response has body                                 | Yes  |
| [Safe](https://developer.mozilla.org/en-US/docs/Glossary/Safe) | Yes  |
| [Idempotent](https://developer.mozilla.org/en-US/docs/Glossary/Idempotent) | Yes  |
| [Cacheable](https://developer.mozilla.org/en-US/docs/Glossary/Cacheable) | Yes  |
| Allowed in HTML forms                                        | Yes  |

The **HTTP `HEAD` method** requests the headers that are returned if the specified resource would be requested with an HTTP [`GET`](https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods/GET) method. Such a request can be done before deciding to download a large resource to save bandwidt

| Request has body                                             | No   |
| :----------------------------------------------------------- | ---- |
| Successful response has body                                 | No   |
| [Safe](https://developer.mozilla.org/en-US/docs/Glossary/Safe) | Yes  |
| [Idempotent](https://developer.mozilla.org/en-US/docs/Glossary/Idempotent) | Yes  |
| [Cacheable](https://developer.mozilla.org/en-US/docs/Glossary/Cacheable) | Yes  |
| Allowed in [HTML forms](https://developer.mozilla.org/en-US/docs/Web/Guide/HTML/Forms) | No   |

The **HTTP PUT request method** creates a new resource or replaces a representation of the target resource with the request payload.

| Request has body                                             | Yes  |
| :----------------------------------------------------------- | ---- |
| Successful response has body                                 | No   |
| [Safe](https://developer.mozilla.org/en-US/docs/Glossary/Safe) | No   |
| [Idempotent](https://developer.mozilla.org/en-US/docs/Glossary/Idempotent) | Yes  |
| [Cacheable](https://developer.mozilla.org/en-US/docs/Glossary/Cacheable) | No   |
| Allowed in [HTML forms](https://developer.mozilla.org/en-US/docs/Web/Guide/HTML/Forms) | No   |