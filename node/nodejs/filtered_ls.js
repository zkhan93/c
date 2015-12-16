var fs=require('fs');
var path=require('path');
//console.log(process.argv);
fs.readdir(process.argv[2],function callback(err,list){
//	console.log(list);
//	console.log(err);
	if(err==null){
//		console.log(list);
		for(var i=0;i<list.length;i++){
			if(path.extname(list[i])=='.'+process.argv[3]){
				console.log(list[i]);
			}
		}
	}
});
