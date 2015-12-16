var sum=0;
for(var x=2; x<process.argv.length;x++){
	sum+=Number(process.argv[x]);
}
console.log(sum);

