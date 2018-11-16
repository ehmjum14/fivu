
// Node.js Modul

import * as http from 'http';

import * as path from 'path';

import * as express from 'express';


export class Server {

    private _port: number;
    private _server: express.Express;

    public constructor (port: number) {
        const assetsPath = path.join(__dirname, '..', 'assets');
        this._port = port;
        this._server = express();
        this._server.use('/', express.static(assetsPath));
        this._server.get('/liste',
        (req, resp, next) => this.handleGetListe(req, resp, next));

        this._server.get('/image.png',
        (req, resp, next) => this.sendImage(resp));
    }

    public start () {
        this._server.listen(this._port);
        console.log('HTTP server gestartet auf Port ' + this._port);
    }


    public get port() {
        return this._port;
    }

    private handleGetListe (reg: express.Request, resp: express.Response
        , next: express.NextFunction) {
        const filePath = path.join(__dirname, '..' , 'assets', 'liste.html');
        console.log(filePath);
        resp.sendFile(filePath);
    }

    private sendImage (resp: express.Response) {
        const filePath = path.join(__dirname, '..', 'assets', 'image.png');
        resp.sendfile(filePath);
    }
}
