Page({

    /**
     * 页面的初始数据
     */
    data: {
        movieList:[{
            pic:"https://img1.doubanio.com/view/photo/m/public/p2555859678.webp",
            name:"一条狗的使命",
            time:120,
            actor:"丹尼斯·奎德 / 凯瑟琳·普雷斯科特 / 刘宪华 / 玛格·海根柏格 / 贝蒂·吉尔平 ",
            type:"剧情 / 喜剧 / 家庭"
        }, {
                pic: "https://img1.doubanio.com/view/photo/m/public/p2555859678.webp",
                name: "一条狗的使命",
                time: 120,
                actor: "丹尼斯·奎德 / 凯瑟琳·普雷斯科特 / 刘宪华 / 玛格·海根柏格 / 贝蒂·吉尔平 ",
                type: "剧情 / 喜剧 / 家庭"
            }, {
                pic: "https://img1.doubanio.com/view/photo/m/public/p2555859678.webp",
                name: "一条狗的使命",
                time: 120,
                actor: "丹尼斯·奎德 / 凯瑟琳·普雷斯科特 / 刘宪华 / 玛格·海根柏格 / 贝蒂·吉尔平 ",
                type: "剧情 / 喜剧 / 家庭"
            }, {
                pic: "https://img1.doubanio.com/view/photo/m/public/p2555859678.webp",
                name: "一条狗的使命",
                time: 120,
                actor: "丹尼斯·奎德 / 凯瑟琳·普雷斯科特 / 刘宪华 / 玛格·海根柏格 / 贝蒂·吉尔平 ",
                type: "剧情 / 喜剧 / 家庭"
            }, {
                pic: "https://img1.doubanio.com/view/photo/m/public/p2555859678.webp",
                name: "一条狗的使命",
                time: 120,
                actor: "丹尼斯·奎德 / 凯瑟琳·普雷斯科特 / 刘宪华 / 玛格·海根柏格 / 贝蒂·吉尔平 ",
                type: "剧情 / 喜剧 / 家庭"
            }

        ]

    },

    /**
     * 生命周期函数--监听页面加载
     */
    onLoad: function(options) {

    },

    /**
     * 生命周期函数--监听页面初次渲染完成
     */
    onReady: function() {

    },

    /**
     * 生命周期函数--监听页面显示
     */
    onShow: function() {

    },

    /**
     * 生命周期函数--监听页面隐藏
     */
    onHide: function() {


    },

    /**
     * 生命周期函数--监听页面卸载
     */
    onUnload: function() {

    },

    /**
     * 页面相关事件处理函数--监听用户下拉动作
     */
    onPullDownRefresh: function() {

    },

    /**
     * 页面上拉触底事件的处理函数
     */
    onReachBottom: function() {

    },

    /**
     * 用户点击右上角分享
     */
    onShareAppMessage: function() {

    },
    searchbtn() {
        wx.navigateTo({
            url: '/pages/search/search'
        })
    },
})