/*
  Folder 'pic' need create "without" 'sudo'
  Because need permission to write on this folder.
*/

const express = require('express');
const app = express();
var port = 6464;

var multer = require('multer'); //--> This module use for upload from front-end

var mongojs = require('mongojs');
var imgdata64db = mongojs('imgdata64');
var Promise = require('promise');

var moment = require('moment');

var path = require('path');
app.use(express.static(path.join(__dirname, 'html')));

const fileUpload = require('express-fileupload');
app.use(fileUpload());

app.get('/', function (req, res) {
  res.send("Base64 image upload protocol ready !");
});

app.get('/displayimage', function(req, res){
  res.sendFile(path.join(__dirname + '/html/index.html'));
});

app.post('/upload', function(req, res) {

  //console.log(req);
  //console.log(req.files.image.name);
  //console.log(req.files.image.data);
  //console.log(req.body.message);

  if (!req.files)
    return console.log('No file upload');

  var sampleFile = req.files.image;

  sampleFile.mv('/home/isaranu/base64_img_protocol/uploaded_pic/capture.jpg', function(err) {
    if(err) return console.log(err);

      /* Insert data in mongo */
      /*
      var insertimg64_col = imgdata64db.collection('imgdata');
          insertimg64_col.insert({

            imgfilename: String(req.files.image.name),
            data64: req.files.image.data

          }, function(err){
              if(err) return console.log(err);

              console.log('File uploaded !');
              res.send('File uploaded !\r');

          });
      */
      console.log('File uploaded : ' + moment(new Date()).format('MMMM Do YYYY, h:mm:ss a'));
      res.send('File uploaded !\r');

  });
});

app.listen(port, function () {
  var nodeStartTime = new Date();
  console.log('Base64 image upload start on port ' + port + ' start at ' + nodeStartTime);
});
