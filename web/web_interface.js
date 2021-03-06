const http = require('http');
const fs   = require('fs');
const ejs  = require('ejs');
const url  = require('url');
const qs   = require('querystring');

const inde_page = fs.readFileSync('./index.ejs', 'utf-8');

var server = http.createServer(getFromClient);
server.listen(8080);
console.log('Server Start!');

function getFromClient(request, response) {
    var url_parts = url.parse(request.url);
    switch(url_parts.pathname) {
        case '/':
            response_index(request, response);
            break;

        default:
            response.writeHead(200, {'Content-Type': 'text/html'});
            response.end('no page...');
            break;
  }
}

function execute_command(request, response) {
    const command = '../build/client ';
    if (request.method == 'POST') {
        var body = '';

        request.on('data', function (data) {
            body += data;
        });

        request.on('end', function () {
            var post_data = qs.parse(body);
            console.log(post_data);
            var x = post_data.x;
            var y = post_data.y;
            const exec = require('child_process').execSync(command + x + ' ' + y);
        });
    }
}

function response_index(request, response) {
    execute_command(request, response);
    fs.readFile('../build/board.txt', 'utf-8',
        (error, data) => {
            var content = ejs.render(inde_page, {
                board_status: data,
                grid_size: 9,
            });
            response.writeHead(200, {'Content-Type': 'text/html'});
            response.write(content);
            response.end();
        }
    );
}
