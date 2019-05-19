var crypto = require('crypto');

module.exports={
	cookieStep:cookieStep
}

function cookieStep(obj,res){
	var cookieSend = "" + obj.name + "~" + obj.password + "~" + new Date().getTime(); //保存cookie验证，防止跨站session失效
	
	var str = JSON.stringify(cookieSend); //明文
	var secret = 'niyidingjiebuchulai'; //密钥--可以随便写
	var cipher = crypto.createCipher('aes192', secret);
	var enc = cipher.update(str, 'utf8', 'hex'); //编码方式从utf-8转为hex;
	enc += cipher.final('hex'); //编码方式从转为hex;
	
	res.cookie('pbl', enc, {
		path: '/',
		maxAge: 5 * 1000,
		signed: true
	});
	res.cookie('style', obj.name, {
		path: '/',
		maxAge: 24 * 3600 * 1000,
		signed: true
	});
}


