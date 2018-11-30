"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const path = require("path");
const bodyParser = require("body-parser");
const express = require("express");
class Server {
    constructor(port) {
        const assetsPath = path.join(__dirname, '..', 'assets');
        this._port = port;
        this._server = express();
        this._server.set('views', path.join(__dirname, 'views'));
        const engine = this._server.set('view engine', 'pug');
        engine.locals.pretty = true;
        this._server.use('/', express.static(assetsPath));
        this._server.use(bodyParser.json());
        this._server.use(bodyParser.urlencoded());
        this._server.post('/login.html', (req, res, next) => this.handlePostLogin(req, res, next));
        this._server.get('/liste', (req, res, next) => this.handleGetListe(req, res, next));
    }
    start() {
        this._server.listen(this._port);
        console.log('HTTP server gestartet auf port ' + this._port);
    }
    get port() {
        return this._port;
    }
    handlePostLogin(req, res, next) {
        if (req.body.email === 'test@text.at' && req.body.password === 'geheim') {
            res.render('welcome.pug', { anrede: 'Herr', name: 'Rüsselputzer' });
        }
        else {
            res.status(404).send('404 NOT AUTHORIZED');
        }
        next();
    }
    handleGetListe(req, res, next) {
        const filePath = path.join(__dirname, '..', 'assets', 'liste.html');
        console.log(filePath);
        res.sendFile(filePath);
    }
}
exports.Server = Server;

//# sourceMappingURL=server.js.map
