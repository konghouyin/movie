// pages/play/play.js
Page({

    changeDay(event){
        var num = event.target.dataset.id;
        var arr = this.data.dayList;
        arr[this.data.timeNow].style = "";
        arr[num].style = "active";
        this.setData({
            timeNow:num,
            dayList:arr
        })

    },

    /**
     * 页面的初始数据
     */
    data: {
        item: {
            pic: "https://img1.doubanio.com/view/photo/m/public/p2555859678.webp",
            name: "一条狗的使命",
            time: 120,
            country:'美国',
            actor: "丹尼斯·奎德 / 凯瑟琳·普雷斯科特 / 刘宪华 / 玛格·海根柏格 / 贝蒂·吉尔平 ",
            type: "剧情 / 喜剧 / 家庭",
			style:"已上映"
        },
		dayList:[],
        timeNow:0,
        //当前查看的选择时间
        playList:[{
            timestart:"20:45",
            place:"全景声MAX厅",
            language:"国语",
            money:26.9
        }, {
                timestart: "20:45",
                place: "全景声MAX厅",
                language: "国语",
                money: 26.9
            }, {
                timestart: "20:45",
                place: "全景声MAX厅",
                language: "国语",
                money: 26.9
            }, {
                timestart: "20:45",
                place: "全景声MAX厅",
                language: "国语",
                money: 26.9
            }, {
                timestart: "20:45",
                place: "全景声MAX厅",
                language: "国语",
                money: 26.9
            }, {
                timestart: "20:45",
                place: "全景声MAX厅",
                language: "国语",
                money: 26.9
            }, {
                timestart: "20:45",
                place: "全景声MAX厅",
                language: "国语",
                money: 26.9
            }, {
                timestart: "20:45",
                place: "全景声MAX厅",
                language: "国语",
                money: 26.9
            }, {
                timestart: "20:45",
                place: "全景声MAX厅",
                language: "国语",
                money: 26.9
            },{
                timestart: "20:45",
                place: "全景声MAX厅",
                language: "国语",
                money: 26.9
            }]
    },

    /**
     * 生命周期函数--监听页面加载
     */
    onLoad: function (options) {
		this.setData({
			dayList:initDay()
		});
        wx.setNavigationBarTitle({
            title: '修改姓名',
            success: function (res) {
                // success
            }
        })
		
    },

    /**
     * 生命周期函数--监听页面初次渲染完成
     */
    onReady: function () {

    },

    /**
     * 生命周期函数--监听页面显示
     */
    onShow: function () {

    },

    /**
     * 生命周期函数--监听页面隐藏
     */
    onHide: function () {

    },

    /**
     * 生命周期函数--监听页面卸载
     */
    onUnload: function () {

    },

    /**
     * 页面相关事件处理函数--监听用户下拉动作
     */
    onPullDownRefresh: function () {

    },

    /**
     * 页面上拉触底事件的处理函数
     */
    onReachBottom: function () {

    },

    /**
     * 用户点击右上角分享
     */
    onShareAppMessage: function () {

    }
})



function initDay(){
	var now = new Date();
	var arr=[{},{},{},{},{}];
	arr[0].message="今天";
	arr[1].message="明天";
	arr[2].message="后天";
	arr[3].message="";
	arr[4].message="";
	
	for(var i=0;i<5;i++){
		arr[i].day = now.format("MM月dd日");
        arr[i].style="";
		now.setDate(now.getDate()+1);
	}
    arr[0].style="active"
	return arr;
}



Date.prototype.format = function(fmt) { 
     var o = { 
        "M+" : this.getMonth()+1,                 //月份 
        "d+" : this.getDate(),                    //日 
        "h+" : this.getHours(),                   //小时 
        "m+" : this.getMinutes(),                 //分 
        "s+" : this.getSeconds(),                 //秒 
        "q+" : Math.floor((this.getMonth()+3)/3), //季度 
        "S"  : this.getMilliseconds()             //毫秒 
    }; 
    if(/(y+)/.test(fmt)) {
            fmt=fmt.replace(RegExp.$1, (this.getFullYear()+"").substr(4 - RegExp.$1.length)); 
    }
     for(var k in o) {
        if(new RegExp("("+ k +")").test(fmt)){
             fmt = fmt.replace(RegExp.$1, (RegExp.$1.length==1) ? (o[k]) : (("00"+ o[k]).substr((""+ o[k]).length)));
         }
     }
    return fmt; 
}
//data格式化