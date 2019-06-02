const sql = require('./public/sql.js');
const {
	sql: sqlConfig,
	url: urlConfig
} = require('./public/system_config.js');
const pool = sql.createPool(sqlConfig);
//创建数据库连接池
const {
	cookieStep,
	translateCookie,
	sessionStep
} = require('./public/cookie_step.js');
//解析cookie，下发session
const {
	send,
	server,
	sessionStart,
	exit,
	judge,
	path
} = require('./public/http.js'); //解析网络请求
server.listen(510);



server.get('/new', async function(req, res) {
	var obj = ranslateCookie(req);
	if (obj.style == 1) {
		let sqlString = sql.select(['user_name', 'user_password', 'user_status'], 'user',
			`user_name=${sql.escape(obj.name)} AND user_password=${sql.escape(obj.password)}`);
		try {
			var selectAns = await sql.sever(pool, sqlString);
		} catch (err) {
			send(res, {
				"msg": err,
				"style": -2
			});
			return;
		}
		if (selectAns.length == 1) {
			sessionStep(req); //合法登录下发session
			send(res, {
				"msg": "session已下发，登录状态安全",
				"name": obj.name,
				"style": 1
			})
		} else {
			send(res, {
				"msg": "数据库查询异常",
				"style": -10
			})
		}
	} else if (obj.style == -1) {
		send(res, {
			msg: "cookie解析错误",
			style: 0
		})
	} else if (obj.style == -2) {
		send(res, {
			msg: "cookie解析超时",
			style: -1
		})
	} else {
		send(res, {
			msg: "cookie解析style异常",
			style: -10
		})
	}
})
//跳转登录验证


server.get('/query', async function(req, res) {
	let obj = req.obj;
	let judgeOptions = {
		url: {
			length: 500
		}
	}
	let judgeCtrl = judge(judgeOptions, obj);
	if (judgeCtrl.style == 0) {
		send(res, {
			"msg": judgeCtrl.message,
			"style": -1
		})
	} else {
		let pathCtrl = await path("http://localhost:798/index", {
			url: obj.url
		});
		if (pathCtrl.style == 1) {
			let back = JSON.parse(pathCtrl.message);
			send(res, {
				"msg": "解析成功！",
				"data": back.index.base,
				"style": 1
			})
		} else {
			send(res, {
				"msg": pathCtrl.message,
				"style": 0
			})
		}
	}
})
//通过豆瓣url解析主要信息


server.post('/playAdd', async function(req, res) {
	let obj = req.obj;
	let judgeOptions = {
		name: {
			length: 64
		},
		director: {
			length: 32
		},
		actor: {
			length: 128
		},
		type: {
			length: 32
		},
		timelong: {
			type: "int",
			length: 32
		},
		country: {
			length: 32
		},
		language: {
			length: 32
		},
		status: {
			type: "only",
			main: ["已上映", "即将上映", "已下线"],
			length: 32
		},
		pic: {
			length: 200
		},
		link: {
			length: 200
		},
		url: {
			length: 200
		}
	}
	let judgeCtrl = judge(judgeOptions, obj);
	if (judgeCtrl.style == 0) {
		send(res, {
			"msg": judgeCtrl.message,
			"style": -1
		})
	} else {
		let waring = "null";
		obj.main = "";
		if (obj.url != "") {
			let pathCtrl = await path("http://localhost:798/index", {
				url: obj.url
			});
			if (pathCtrl.style == 1) {
				let ranges = [
					'\ud83c[\udf00-\udfff]',
					'\ud83d[\udc00-\ude4f]',
					'\ud83d[\ude80-\udeff]'
				];
				obj.main = pathCtrl.message.replace(new RegExp(ranges.join('|'), 'g'), '');
			} else {
				waring = "电影详情页爬取失败，失败原因：" + pathCtrl.message;
			}
		}else{
			waring = "没有爬取电影详细数据";
		}
		let sqlString = sql.insert('play', ['play_name', 'play_director', 'play_performer', 'play_type', 'play_length',
				'play_country', 'play_language', 'play_status', 'play_pic', 'play_message', 'play_link', 'play_path'
			],
			[sql.escape(obj.name), sql.escape(obj.director), sql.escape(obj.actor), sql.escape(obj.type), sql.escape(obj.timelong),
				sql.escape(obj.country), sql.escape(obj.language), sql.escape(obj.status), sql.escape(obj.pic), sql.escape(obj.main),
				sql.escape(obj.link), sql.escape(obj.url)
			]);
		try {
			var insertAns = await sql.sever(pool, sqlString);
		} catch (err) {
			send(res, {
				"msg": err,
				"style": -2
			});
			return;
		}
		send(res, {
			"msg": "电影信息添加成功！",
			"waring": waring,
			"style": 1
		});
	}
})
//添加剧目


server.get("/playAll", async function(req, res) {
	let sqlString = sql.select(['play_id', 'play_name', 'play_director', 'play_performer', 'play_type', 'play_length',
		'play_country', 'play_language', 'play_status', 'play_pic', 'play_link','play_path'
	], 'play') + ' ORDER BY play_id DESC';
	try {
		var selectAns = await sql.sever(pool, sqlString);
	} catch (err) {
		send(res, {
			"msg": err,
			"style": -2
		});
		return;
	}
	send(res, {
		"msg": "查询成功！",
		"data": selectAns,
		"style": 1
	});
})
//查询全部剧目


server.get("/playMain", async function(req, res) {
	let obj = req.obj;
	let sqlString = sql.select(['play_id', 'play_name', 'play_director', 'play_performer', 'play_type', 'play_length',
		'play_country', 'play_language', 'play_status', 'play_pic', 'play_link', 'play_message', 'play_path'
	], 'play', 'play_id=' + sql.escape(obj.id));
	try {
		var selectAns = await sql.sever(pool, sqlString);
	} catch (err) {
		send(res, {
			"msg": err,
			"style": -2
		});
		return;
	}
	if (selectAns.length == 1) {
		send(res, {
			"msg": "查询成功！",
			"data": selectAns[0],
			"style": 1
		});
	} else {
		send(res, {
			"msg": "没有查询到该id对应的电影！",
			"style": 0
		});
	}
})
//查询具体剧目


server.post("/playDel", async function(req, res) {
	let obj = req.obj;
	let sqlStringSelect = sql.select(['play_path'], 'play', 'play_id=' + sql.escape(obj.id));
	try {
		var selectAns = await sql.sever(pool, sqlStringSelect);
	} catch (err) {
		send(res, {
			"msg": err,
			"style": -2
		});
		return;
	}
	if (selectAns.length != 1) {
		send(res, {
			"msg": "没有查询到要修改的id",
			"style": 0
		});
		return;
	}

	let sqlString = sql.del('play', 'play_id=' + sql.escape(obj.id));
	try {
		var selectAns = await sql.sever(pool, sqlString);
	} catch (err) {
		send(res, {
			"msg": err,
			"style": -2
		});
		return;
	}

	send(res, {
		"msg": "删除成功！",
		"style": 1
	});
})
//删除剧目


server.post("/playEdit", async function(req, res) {
	let obj = req.obj;
	let judgeOptions = {
		id: {
			type: "int",
			length: 32
		},
		name: {
			length: 64
		},
		director: {
			length: 32
		},
		actor: {
			length: 128
		},
		type: {
			length: 32
		},
		timelong: {
			type: "int",
			length: 32
		},
		country: {
			length: 32
		},
		language: {
			length: 32
		},
		status: {
			type: "only",
			main: ["已上映", "即将上映", "已下线"],
			length: 32
		},
		pic: {
			length: 200
		},
		link: {
			length: 200
		},
		url: {
			length: 200
		}
	}
	let judgeCtrl = judge(judgeOptions, obj);
	if (judgeCtrl.style == 0) {
		send(res, {
			"msg": judgeCtrl.message,
			"style": -1
		})
		return;
	}
	let sqlStringSelect = sql.select(['play_path'], 'play', 'play_id=' + sql.escape(obj.id));
	try {
		var selectAns = await sql.sever(pool, sqlStringSelect);
	} catch (err) {
		send(res, {
			"msg": err,
			"style": -2
		});
		return;
	}
	if (selectAns.length != 1) {
		send(res, {
			"msg": "没有查询到要修改的id",
			"style": 0
		});
		return;
	}
	let waring = "null";
	obj.main = "";
	if (obj.url != "") {
		let pathCtrl = await path("http://localhost:798/index", {
			url: obj.url
		});
		if (pathCtrl.style == 1) {
			let ranges = [
				'\ud83c[\udf00-\udfff]',
				'\ud83d[\udc00-\ude4f]',
				'\ud83d[\ude80-\udeff]'
			];
			obj.main = pathCtrl.message.replace(new RegExp(ranges.join('|'), 'g'), '');
		} else {
			waring = "电影详情页爬取失败，失败原因：" + pathCtrl.message;
		}
	}else{
		waring = "没有爬取电影详细数据";
	}
	let sqlString = sql.update('play', ['play_name', 'play_director', 'play_performer', 'play_type', 'play_length',
			'play_country', 'play_language', 'play_status', 'play_pic', 'play_message', 'play_link', 'play_path'
		],
		[sql.escape(obj.name), sql.escape(obj.director), sql.escape(obj.actor), sql.escape(obj.type), sql.escape(obj.timelong),
			sql.escape(obj.country), sql.escape(obj.language), sql.escape(obj.status), sql.escape(obj.pic), sql.escape(obj.main),
			sql.escape(obj.link), sql.escape(obj.url)
		], 'play_id=' + sql.escape(obj.id));
	try {
		var selectAns = await sql.sever(pool, sqlString);
	} catch (err) {
		send(res, {
			"msg": err,
			"style": -2
		});
		return;
	}

	send(res, {
		"msg": "编辑成功！",
		"waring":waring,
		"style": 1
	});
})
//编辑剧目
