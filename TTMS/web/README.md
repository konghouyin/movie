# TTMS后台开发文档

## 一、概述

本后台是为剧院票务管理系统开发的web应用后台，为剧院票务管理系统web应用及微信小程序提供数据查询，存储的支持。整个后台使用微服务架构，并配置nginx做静态资源管理和均衡负载。

## 二、应用技术

- 开发语言：node.JS
- 系统数据数据库：MySQL 8.0

## 三、开发规范

### 1.命名规范

- 公共：public
- 登录注册：login

### 2.已安装的工具

- express
- express-static
- mysql
- cookie-paser
- cookie-session
- crypto（加密函数）
- request（本地爬虫）

### 3.项目目录

```mariadb
|server #后台根目录
├── README.md
├── node_module #安装工具
├── public #公共模块
├── xxx_server.js #服务后台
├── package.json #项目配置文件
└── package-lock.json #模块配置文件
```

## 四、开发记录

### 公共模块

#### 1.数据库模块

**模块名称：sql.js**

主要提供连接数据库，便捷调用服务，sql语句拼接（mysql模块的再次封装）。

---

1. 创建mysql数据库连接池

```js
var sql = require('./server/public_sql');
var pool  = sql.createPool({
  connectionLimit : 10,
  host            : '132.232.169.227',
  user            : 'admin',
  password        : 'xxx',
  database        : 'recruitment'
});
```

使用createPool方法进行数据库连接池创建，通过数据库连接池，提高与mysql之间交互效率。

---

2. 通过连接池进行数据库操作

```js
sql.sever(pool, sqlString);

async function(){
    try {
		var selectRepeat = await sql.sever(pool, sqlString);
        //同步返回数据内容
	} catch (err) {
		throw err;
	}
}
```

​     封装sql数据库命令sever，通过获取sql命令以及回调函数，实现包括从连接池获取连接，使用完释放连接的完整SQL查询。本功能返回promise，可以结合是有async将异步转换成同步代码。

**参数说明：** 

- pool：<Object> 连接池

- SQLString：<String> sql语句


**提示：** 可以将SQLString生成函数，最后的回调函数，提取出来，优化代码。

**注意：** 输入的SQLString要求要进行转义，防止SQL注入。

---

3. sql语句转换

```js
sql.escape(name);
```

不同类型的值转义的方式是有区别的，其区别如下：

- 数字不会被转义
- 布尔值会被转移成 true / false
- Date 对象会被转义成形如 'YYYY-mm-dd HH:ii:ss' 的字符串
- Buffer 会被转义成十六进制字符串，如： X'0fa5'
- 字符串会被安全地转义
- 数组会被转义成列表，例如： ['a', 'b'] 会被转义成 'a', 'b'
- 嵌套数组会被转义成多个列表（在大规模插入时），如： [['a', 'b'], ['c', 'd']] 会被转义成 ('a', 'b'), ('c', 'd')
- 对象的所有可遍历属性会被转义成键值对。如果属性的值是函数，则会被忽略；如果属性值是对象，则会使用其 toString() 方法的返回值。
- undefined / null 会被转义成 NULL
- NaN / Infinity 将会被原样传入。由于MySQL 并不支持这些值，在它们得到支持之前，插入这些值将会导致MySQL报错。

**注意：** 所有从前端获取的内容，不能直接拼接进入sql语句，必须转换后再使用。

---

4. SELECT语句拼接

```js
sql.select（type，tablename[，where]）;
```

数据库查询命令拼接select，通过输入对应参数，返回拼接好的sql查询语句。

**参数说明：** 

- type：<Array> 查询的字段
- tablename：<String> 查询的表
- where：<String> where过滤语句（参数可选）

**注意：** 当有多条Where过滤条件时，注意拼接时的空格。

**示例：** 

```js
obj={
	name:"樊宗渤",
	password:"04173167"
}

let sqlString = sql.select(['user_name', 'user_password'], 'user',
		`user_name=${sql.escape(obj.name)} AND user_password=${sql.escape(obj.password)}`);
```

---
5. INSERT语句拼接

```js
sql.insert(tablename,type,value,ignore);
sql.insert("registryinformation",["password","phoneNum"],["asd",13345]);
```

数据库插入命令拼接insert，通过输入对应参数，返回拼接好的sql插入语句。

**参数说明：** 

- tablename：<String> 查询的表
- type：<Array> 插入的字段
- valuse：<Array> 插入的值
- ignore：<Boole> 筛选防止多重添加（可选参数）

**注意：** 插入字段与插入值的个数应该相同。

**提示：**参数ignore为true表示，如果数据库中已经存在相同的记录，则忽略当前新数据；

---

6. UPDATE语句拼接

```js
sql.update(tablename, type, value[,where]);
sql.update("registryinformation",["password","phoneNum"],["123",123],"name='樊宗渤'");
```

**参数说明：** 

- tablename：<String> 查询的表
- type：<Array> 插入的字段
- valuse：<Array> 插入的值
- where：<String> where过滤语句（参数可选）

**注意：** 当有多条Where过滤条件时，注意拼接时的空格。修改字段与修改值的个数应该相同。

---

7. DELETE语句拼接

```js
sql.del(tablename[,where]);
sql.del("registryinformation","name='樊宗渤'");
```

**参数说明：** 

- tablename：<String> 查询的表
- where：<String> where过滤语句（参数可选）

**注意：** 当有多条Where过滤条件时，注意拼接时的空格。

**警告：** 此接口不使用where参数会导致删除数据表，请谨慎使用。



#### 2.项目配置文件

**模块名称：system_config.js**

将数据库登录信息为配置文件进行编写。便于后期更改和维护。

```json
{
    sql: {
		connectionLimit: 10,
		host: 'localhost',
		user: 'root',
		password: '3832414122',
		database: 'ttms'
	},url:"http://localhost:529"
}
```



#### 3.封装网络请求

**模块名称：http.js**

实现功能：

- express框架，建立server服务
- 设置cookie，session中间件
- header处理跨域
- 数据解析-中间件
- 更新session过期时间
- 封装res数据发送
- 封装session安全验证
- 封装退出登录函数

```js
module.exports = {
	send: send,//发送数据
	server: server,//建立server服务
	sessionStart:sessionStart,//session安全验证
    exit:exit,//退出登录
    judge:judge//判读参数是否合法
    path:path//内网爬虫
}
//函数原型
function send(res, obj){};
const server = express()；
function sessionStart(){}；
function exit(){}；
function judge(obj){};
function path(add,qs)；
```

注意：

1. sessionStart安全验证依据为session.style是否为1
2. 退出登录，将session.style设置为0，同时cookie-style也设置为0



#### 4.跨站cookie

**模块名称：cookie_step.js**

这个模块使用的目的是，下发跨站验证登录cookie。对外暴露cookieStep，translateCookie，sessionStep函数

```js
cookieStep(obj，res)
cookieStep({
    name:"xxx",
    password:"xxx"
},res)
```

**参数说明：** 

- obj：<Object> 验证对象（对象中应包括name和password属性）
- res：<httpResponse> 验证下发目标

- 加密拼接规则：name+password+time

---

```js
var obj = translateCookie(req)
```

**参数说明：** 

- obj：<Object> 验证对象（对象中包括name和password和style值）
- req：<httpRequest> 请求来源对象
- obj.style(1正常，-1解析错误，-2解析超时)

---

```js
sessionStep(req)
```

**参数说明：** 

- req：<httpRequest> 请求来源对象
- 下发对应session.style=1

**注意：** 

1. 通过cookie登录保持，绑定cookie--style，有效时长1天cookie-style存储内容为obj.name

2. 通过cookie跨页跳转验证，绑定cookie--pbl，有效时长15秒



### 业务模块

#### 1.login部分

注册：判断传入参数是否正确---->校验用户名唯一性---->数据写入数据库---->下发cookie---->url跳转

登录：判断传入参数是否正确---->校验用户名密码正确性---->下发cookie---->url跳转

登录保持：判断cookie-style值---->校验用户名---->下发cookie---->url跳转

  

#### 2.operation部分

跳转验证：解析cookie---->数据库再次确认---->下发session

一下所有功能，都要首先进行session安全验证

url解析基础信息：验证url合法性---->本地798爬虫---->发送

添加剧目：验证参数完整性和合法性---->加入数据库




## 五、线上部署及接口文档

目前后台已经部署在腾讯云服务器上

- 服务器ip：132.232.169.227
- 服务器带宽：1Mpbs

后台应用由forever进行管理，如果出现后台崩溃等异常退出，后台将会自动重启，保证服务正常运行。

### 登录注册部分

#### 1.新用户注册接口

- url：/reg
- 端口：517
- 方法：POST
- 参数：{”name”:“用户名“，”password”:“密码“}
- 注意：
     - 提交用户名字符长度不得超过32个，密码字符使用MD5加密。
- 返回

```json
{
	"msg": "注册成功",
	"url": "需要跳转的url",
	"style": 1
}

{
	"msg": "注册失败--用户名重复",
	"style": 0
}

{
    "msg": "参数错误！",
    "style": -1
}

{
    "msg": err,
    "style": -2
}
//数据库异常
```

注意：首次注册后，状态值为0，默认没有任何权限，需要联系系统管理员进行权限添加。



#### 2.新用户登录接口

- url：/login
- 端口：517
- 方法：POST
- 参数：{”name”:“用户名“，”password”:“密码“}
- 注意：
     - 提交用户名字符长度不得超过32个，密码字符使用MD5加密。
- 返回

```json
{
	"msg": "登录成功！",
	"url": "需要跳转的url",
	"style": 1
}

{
	"msg": "用户名或密码错误！",
	"style": 0
}

{
    "msg": "参数错误！",
    "style": -1
}

{
    "msg": err,
    "style": -2
}
//数据库异常
```

#### 3.登录保持接口

- url：/step
- 端口：517
- 方法：GET
- 参数：无
- 注意：
     - 通过cookie-style验证登录状态
- 返回

```json
{
	"msg": "登录成功！",
	"url": "需要跳转的url",
	"style": 1
}

{
	"msg": "登录状态没有保持",
	"style": 0
}

{
    "msg": err,
    "style": -2
}
//数据库异常
```



### 运营管理部分

#### 1.跳转登录验证

- url：/new
- 端口：510
- 方法：GET
- 参数：无
- 注意：
     - 通过cookie-pbl验证登录状态，验证有效时间15秒
- 返回

```json
{
    "msg": "session已下发，登录状态安全",
    "name":obj.name,
    "style": 1
}

{
    msg: "cookie解析错误",
    style: 0
}

{
    msg: "cookie解析超时",
    style: -1
}
			
{
    "msg": err,
    "style": -2
}
//数据库异常

{
    msg: "cookie解析style异常",
    style: -10
}
```

#### 2.通过豆瓣url解析主要信息

- url：/query
- 端口：510
- 方法：GET
- 参数：{url:“xxx”}
- 注意：
     - 此处需要发送豆瓣电影详情主页
     - 由于此项操作需要多次转发，和解析数据，数据返回会有一定延迟（1-2s）
- 返回

```
{
    "msg": "解析成功！",
    "data": back.index.base,
    "style": 1
}

{
    "msg": "错误原因",
    "style": 0
}

{
    "msg": "参数错误！",
    "style": -1
}
```

#### 3.添加电影信息

- url：/playAdd

- 端口：510

- 方法：POST

- 参数：{name:“xxx”,director:“xxx”,…}

- 注意：
     - 姓名【必选】（name）参数的长度小于64
     - 导演（director）参数长度32
     - 演员（actor）参数长度128，多个演员使用“/”隔开
     - 类型（type）参数长度32，多种类型使用“/”隔开
     - 片长【必选】（timelong），int类型数值
     - 国家（country），参数长度32位
     - 语言（language），参数长度32位
     - 状态【必选】（status），参数只能是“已上映”，“即将上映”，“已下线”
     - 海报（pic），参数长度为70，需要填入竖版小图片的url
     - 推广链接（link），参数长度70，需要填入横版小图的url，作为客户端轮播推广
     - 爬虫（url），表示爬取网页详细信息

- 返回

     ```json
     {
         "msg": "电影信息添加成功！",
         "waring":waring,
         "style": 1
     }
     		
     {
         "msg": "timelong参数格式不对",
         "style": -1
     }
     
     {
         "msg": err,
         "style": -2
     }
     //数据库异常
     ```

- 注意：

     - 由于此项操作需要多次转发，和解析数据，数据返回会有一定延迟（1-2s）
     - 注意waring，正常情况下是null，在url详细信息解读时出现异常，基础数据会添加成功，详细信息将无法填充。waring中会提示问题原因。
     - 由于数据中存在emoji，后台将会报所有emoji表情过滤掉，然后进行存储

#### 4.查询所有剧目的基础信息

- url：/playAll

- 端口：510

- 方法：GET

- 参数：无

- 返回：

     ```json
     {
         "msg": "查询成功！",
         "data": [
             {
                 "play_id":5,
                 "play_name": "xxxx",
                 "play_director": "xxx",
                 "play_performer": "xxxxxxxx",
                 "play_type": "xxx",
                 "play_length": "90",
                 "play_country": "xxx",
                 "play_language": "xxx",
                 "play_status": "已上映",
                 "play_pic": "xxx",
                 "play_link": "xxx",
                 "play_path":"xxx"
             }
         ],
         "style": 1
     }
     
     {
         "msg": err,
         "style": -2
     }
     //数据库异常
     ```

     注意：返回剧目信息按照id逆序排列

     #### 5.查询具体剧目

     - url：/palyMain
     - 端口：510
     - 方法：GET
     - 参数：{id:“xxx”}
     - 返回

     ```json
     {
         "msg": "查询成功！",
         "data": {
             "play_id": 1,
             "play_name": "xxxx",
             "play_director": "xxx",
             "play_performer": "xxxxxxxx",
             "play_type": "xxx",
             "play_length": "90",
             "play_country": "xxx",
             "play_language": "xxx",
             "play_status": "已上映",
             "play_pic": "xxx",
             "play_link": "xxx",
             "play_message": "xxx",//页面详细详细
             "play_path": "https://movie.douban.com/subject/26891256/?from=showing"
         },
         "style": 1
     }
     
     {
         "msg": "没有查询到该id对应的电影！",
         "style": 0
     }
     
     {
         "msg": err,
         "style": -2
     }
     //数据库异常
     ```

     #### 6.删除剧目

     - url：/palyDel

     - 端口：510

     - 方法：POST

     - 参数：{id:“xxx”}

     - 返回

     ```json
     {
         "msg": "删除成功！",
         "style": 1
     }
     
     {
         "msg": "没有查询到要修改的id",
         "style": 0
     }
     
     {
         "msg": err,
         "style": -2
     }
     //数据库异常
     ```

     #### 7.编辑剧目

- url：/playEdit

- 端口：510

- 方法：POST

- 参数：{id:”2”,name:“xxx”,director:“xxx”,…}

- 注意：

     - 编号 【必选】电影id号

     - 姓名【必选】（name）参数的长度小于64
     - 导演（director）参数长度32
     - 演员（actor）参数长度128，多个演员使用“/”隔开
     - 类型（type）参数长度32，多种类型使用“/”隔开
     - 片长【必选】（timelong），int类型数值
     - 国家（country），参数长度32位
     - 语言（language），参数长度32位
     - 状态【必选】（status），参数只能是“已上映”，“即将上映”，“已下线”
     - 海报（pic），参数长度为70，需要填入竖版小图片的url
     - 推广链接（link），参数长度70，需要填入横版小图的url，作为客户端轮播推广
     - 爬虫（url），表示爬取网页详细信息

- 返回

     ```json
     {
         "msg": "编辑成功！",
         "style": 1
     }
     
     {
         "msg": "没有查询到要修改的id",
         "style": 0
     }
     
     {
         "msg": err,
         "style": -2
     }
     //数据库异常
     ```

     