const nodemailer = require('nodemailer');
const fetch = require('node-fetch');
const express = require('express')
const path = require('path')
const port = process.env.PORT || 3000
const app = express();


// serve static assets normally
app.use(express.static(__dirname + '/public'))

// api for js to consume 
app.get('/getData', function (req, res) {
    var roomStatus = ReadAPIData(res);
    console.log("/get");
 })

app.listen(port)
console.log("server started on port " + port)

// function to send mail to users to free rooms
function sendMail() {
nodemailer.createTestAccount((err, account) => {
    // create reusable transporter object using the default SMTP transport
    const transporter = nodemailer.createTransport({
        service: 'gmail',
        auth: {
               user: 'circuit.breakers.akqa@gmail.com',
               pass: 'hack@0712'
           }
       });

    // setup email data 
    let mailOptions = {
        from: '"Circuit Breakers👻" <circuit.breakers.akqa@gmail.com>', // sender address
        to: 'bhupendra1011@gmail.com,bhupendra.negi@akqa.com,Neetesh.Keshari@akqa.com', // list of receivers
        subject: 'Reg: Room is Unoccupied ! Action Needed', // Subject line
        text: 'Hello world?', // plain text body
        html: '<!DOCTYPE html><title>Text Example</title><style>div.container{background-color: #ffffff;}div.container p{font-family: Arial;font-size: 14px;font-style: normal;font-weight: bold;text-decoration: none;text-transform: none;color: #000000;background-color: #ffffff;}</style><div class="container"><p>Hello Sir/Madam,</p><p></p><p>You have blocked the meeting room , but room is not occupied right now .</p><p>Either update your meeting request or cancel your room booking, so that others can book the room.</p><p></p><p>Thanks,</p><p>Team Circuit Breakers</p></div>' // html body
    };

    // send mail with defined transport object
    transporter.sendMail(mailOptions, (error, info) => {
        if (error) {
            return console.log(error);
        }   

    });
});
};

// fetch data  from thinkapp api IOT :
function ReadAPIData(callback) {
    var status = 0;
    fetch('https://api.thingspeak.com/channels/403274/fields/1.json?results=30')
    .then(function(res) {
        return res.text();
    }).then(function(body) {
       // console.log(body);
        var i, x ="";
        var myObj = JSON.parse(body);
        for (i in myObj.feeds) 
        {
            x += myObj.feeds[i].field1; 
        }
        console.log(x);
        //x = "111101"; // for testing feeds
        var totalLength = x.length;
        var oneCount = x.match(/1/g).length; // find count of 1 in strings 0 & 1's
        var oneCountpercentage = (oneCount*100)/totalLength;
        console.log("percentage of 1 : "+oneCountpercentage);
        if (oneCountpercentage <  40 ) {
            // room is free , send notification to user ;
            sendMail(); // assuming that room was blocked by user so asking him to release as no movement
            status = 1;
            callback.send("1");
        }
        else {
            callback.send("0");
        }                      
    });
   
}


