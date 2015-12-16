var http=require('http');
http.get(process.argv[2],function(response){
	response.on('data',function(data){
		console.log(data.toString());
	});
	response.on('error',function(error){
		console.error('error occured:',error);
	});
	response.on('end',function(end){
		//console.log(end);
	});	
});

