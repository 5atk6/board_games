const http = require('http');
const fs   = require('fs');
const ejs = require('ejs');

const inde_page = fs.readFileSync('./index.ejs', 'utf-8');

var server = http.createServer(getFromClient);
server.listen(8080);
console.log('Server Start!');

function getFromClient(request, response) {
  response.writeHead(200, {'Content-Type': 'text/html'});

  try {
      var content = ejs.render(inde_page);
      response.write(content);
  } catch (err) {
      console.error(err);
  }

  var data = '';
  const command = '../build/client '
  if (request.method == 'POST') {
    request.on('data', function(chunk) {data += chunk})
       .on('end', function() {
           console.log(data);

           var x = data.split('&')[0].split('=')[1]
           var y = data.split('&')[1].split('=')[1]
           const { exec } = require('child_process');
           exec(command + x + ' ' + y);
       })
  }
  response.end();
}
