const net = require("net");
const fs = require("fs");
const path = require("path");
const express = require("express");

const app = express();
const router = express.Router();

const PORT = 8080;

app.use(express.json());
app.use(express.urlencoded());
app.use("/",express.static(__dirname));
app.set("port",PORT);

const client = net.createConnection({ port: 8009 }, () => {
  try{
  // 'connect' listener.
  console.log('connected to server!');
  client.write('world!\r\n');
  }catch(e){
    console.log(e)
  }
});
client.on('data',(d)=>{
  console.log(d.toString("utf-8"));
})

router.get("/", (req,res,next)=>{
    console.log("adsf");
    res.sendFile(path.join(__dirname,"index.html"));
})

router.post("/send",async (req,res,next)=>{
  console.log(req.body); 
  const data  = await client.write(req.body.data+"\r\n");
  console.log(data);
  res.send("ok")

});

app.use("/",router);


// client.on('data',(data)=>{
//     console.log(data.toString('utf-8'));
// })
app.listen(app.get("port"),()=>{
  console.log("server is open ",PORT);
  
})