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

#### 1.自定义后端模块sql.js

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
function out1(data){
	return "SELECT * FROM registryinformation WHERE xuehao='"+data[0].xuehao+"'"
}
function out2(data){
	return "SELECT * FROM registryinformation WHERE xuehao='"+data[0].xuehao+"'"
}
function end(data){
	console.log(data);
}

sql.sever(pool,SQLString,function(data){
	sql.sever(pool,out1(data),function(data){
		sql.sever(pool,out2(data),function(data){
			end(data);
		});
	});
});
```

​     封装sql数据库命令sever，通过获取sql命令以及回调函数，实现包括从连接池获取连接，使用完释放连接的完整SQL查询。

**参数说明：** 

- pool：<Object> 连接池

- SQLString：<String> sql语句

- fn：<Function> 回调函数（传入参数是查询结果的数组）

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
	xuehao:"04173167"
}

function out1(){
	var where ="xingming="+sql.escape(obj.name)+" and xuehao="+sql.escape(obj.xuehao);
	return sql.select(["xuehao","xingming"],"studentinformation",where);
}
function out2(data){
	return sql.select(["*"],"registryinformation","name='"+data[0].xingming+"'");
}
function end(data){
	console.log(data);
}

sql.sever(pool,out1(),function(data){
	sql.sever(pool,out2(data),function(data){
			end(data);
	});
});
```

---
5. INSERT语句拼接

```js
sql.insert(tablename,type,value,ignore);
return sql.insert("registryinformation",["password","phoneNum"],["asd",13345]);
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



#### 2.自定义后端模块cookie_step.js

这个模块使用的目的是，下发跨站验证登录cookie。对外暴露cookieStep函数

```js
cookieStep(obj，res)
cookieStep({
    name:"xxx",
    password:"xxx"
})
```

**参数说明：** 

- obj：<Object> 验证对象
- res：<httpResponse> 验证下发目标

**注意：** 对象中应包括name和password属性

**加密拼接规则：**name+password+time



#### 3.login部分

- 通过cookie登录保持，绑定cookie--style，有效时长1天

- 通过cookie跨页跳转验证，绑定cookie--pbl，有效时长5秒

     

## 五、线上部署及接口文档

目前后台已经部署在腾讯云服务器上

- 服务器ip：132.232.169.227
- 服务器带宽：1Mpbs

后台应用由forever进行管理，如果出现后台崩溃等异常退出，后台将会自动重启，保证服务正常运行。

### 1.新用户注册接口

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
```

### 2.新用户登录接口

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

```

