
// Node.js Modul
// import * as http from 'http';
import * as path from 'path';
import * as bodyParser from 'body-parser';


// Externes Modul (via npm instaliieren)
import * as express from 'express';

export class Server {

    private _port: number;
    private _server: express.Express;

    public constructor (port: number) {
        const assetsPath = path.join(__dirname, '..', 'assets');
        this._port = port;
        this._server = express();

        this._server.set('views', path.join(__dirname, 'views'));
        const engine = this._server.set('view engine', 'pug');
        engine.locals.pretty = true;

        this._server.use('/', express.static(assetsPath));
        this._server.use(bodyParser.json());
        this._server.use(bodyParser.urlencoded());
        this._server.post('/login.html',
            (req, res, next) => this.handlePostLogin(req, res, next)
        );
        this._server.get('/liste',
          (req, res, next) => this.handleGetListe(req, res, next)
        );
        this._server.get('/welcome',
          (req, res) => this.handleGetWelcome(req, res)
        );
    }

    public start () {
        this._server.listen(this._port);
        console.log('HTTP server gestartet auf port ' + this._port);
    }

    public get port () {
        return this._port;
    }

    private handlePostLogin (req: express.Request, res: express.Response,
        next: express.NextFunction) {
            if (req.body.email === 'test@text.at' && req.body.password === 'geheim') {
                // res.render('welcome.pug',{ anrede: 'Herr', name: 'Rüsselputzer'});
                res.redirect('/welcome');
            } else {
                    res.status(404).send('404 NOT AUTHORIZED');
            }
        next();
    }


    private handleGetListe (req: express.Request, res: express.Response,
                            next: express.NextFunction) {
        // res.send('Guten Morgen, Herr Muri');
        const filePath = path.join(__dirname, '..', 'assets', 'liste.html');
        console.log(filePath);
        res.sendFile(filePath);
    }

    private handleGetWelcome(req: express.Request, res: express.Response) {
        res.render('welcome.pug', {anrede: 'Herr', name: 'Rossi'});
    }
}
