var module_ls=require('./module_ls.js');
module_ls(process.argv[2],process.argv[3],function(err,data){
	if(err)
		console.error(err);
	else{
		data.forEach(function(item){
			console.log(item);
			});
	}
});
