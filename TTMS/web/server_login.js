var sql = require('./public/sql.js');
var cookieParser = require('cookie-parser');
var cookieSession = require('cookie-session');
var cookieStep = require('./public/cookie_step.js').cookieStep;
var express = require('express');


var server = express(); //使用express框架
let pool = sql.createPool({
	connectionLimit: 10,
	host: 'localhost',
	user: 'root',
	password: '3832414122',
	database: 'ttms'
});
//创建数据库连接池

server.use(cookieParser('sadssdasdasdasd'));
//为cookie添加签名，防篡改

var arr = [];
for (var i = 0; i < 10000; i++) {
	arr.push(Math.random() * 9999999 + "");
}
//生成加密数组作为秘钥
server.use(cookieSession({
	name: 'sess', //session名称
	keys: arr, //手动设置session密钥.这个秘钥必须是字符串数组
	maxAge: 5 * 60 * 1000 //手动设置session过期时间，单位为毫秒

}));
//设置session


server.all('*', function(req, res, next) {
	res.header("Access-Control-Allow-Origin", req.headers.origin); //需要显示设置来源
	res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
	res.header("Access-Control-Allow-Methods", "PUT,POST,GET,DELETE,OPTIONS");
	res.header("Access-Control-Allow-Credentials", true); //带cookies7     res.header("Content-Type", "application/json;charset=utf-8");
	next();
});
//处理跨域



server.post('/reg', function(req, res) {
	var obj = {};
	var message = '';
	req.on('data', function(data) {
		message += data;
	})
	req.on('end', function() {
		obj = JSON.parse(message);

		var sqlString = sql.select(['user_id'], 'user', "user_name=" + sql.escape(obj.name));
		sql.sever(pool, sqlString, selectEnd); //数据库用户名查重

		function selectEnd(data) {
			if (data.length == 0) {
				var sqlString = sql.insert('user', ['user_status', 'user_name', 'user_password', 'user_time'], [0, sql.escape(
						obj.name),
					sql.escape(obj.password), 'NOW()'
				]);
				sql.sever(pool, sqlString, end); //数据库存入注册的用户
			} else {
				res.write(JSON.stringify({
					msg: "注册失败--用户名重复",
					style: 0
				}));
				res.end();
			}
		}
	})

	function end(data) {
		cookieStep(obj, res);
		res.write(JSON.stringify({
			msg: "注册成功",
			url: "需要跳转的url",
			style: 1
		}));
		res.end();
	}
})
//请求--注册信息

server.post('/login', function(req, res) {
	var obj = {};
	var message = '';
	req.on('data', function(data) {
		message += data;
	})
	req.on('end', function() {
		obj = JSON.parse(message);
		var sqlString = sql.select(['user_id'], 'user',
			"user_name=" + sql.escape(obj.name) +
			" and user_password=" + sql.escape(obj.password));
		sql.sever(pool, sqlString, end); //验证用户名和密码
	})

	function end(data) {
		if (data.length == 1) {
			cookieStep(obj, res);
			res.write(JSON.stringify({
				msg: "登录成功！",
				url: "需要跳转的url",
				style: 1
			}));
			res.end();

		} else {
			res.write(JSON.stringify({
				msg: "用户名或密码错误！",
				style: 0
			}));
			res.end();
		}
	}
})
//请求--登录



server.listen(517);
