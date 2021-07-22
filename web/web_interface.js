var http = require('http');
var html = require('fs').readFileSync('index.html');
var fs   = require('fs');

http.createServer(function (req, res) {
  res.writeHead(200, {'Content-Type': 'text/html'});

  try {
      const board = fs.readFileSync('../build/board.txt', 'utf8');
      res.write(board);
  } catch (err) {
      console.error(err);
  }

  var data = '';
  const command = '../build/client '
  if (req.method == 'POST') {
    req.on('data', function(chunk) {data += chunk})
       .on('end', function() {
           console.log(data);

           var x = data.split('&')[0].split('=')[1]
           var y = data.split('&')[1].split('=')[1]
           res.end(html);
           const { exec } = require('child_process');
           exec(command + x + ' ' + y);
       })
  }
  res.end(html);
}).listen(8080); 
