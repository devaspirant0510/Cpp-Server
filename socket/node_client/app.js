const net = require("net");
const client = net.createConnection({ port: 1234 }, () => {
  // 'connect' listener.
  console.log('connected to server!');
  client.write('world!\r\n');
});

client.on('data',(data)=>{
    console.log(data.toString('utf-8'));
})