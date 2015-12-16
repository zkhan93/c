module.exports=function(dir_name,extension,callback){
	var fs=require('fs');
	var path=require('path');
	fs.readdir(dir_name,function(err,data){
		if(err)
			return callback(err);
		else{
			filelist=[];
			data.forEach(function(file){
				if(path.extname(file)=='.'+extension){
					filelist.push(file);
				}
			});
			callback(null,filelist);
		}
	});
}
